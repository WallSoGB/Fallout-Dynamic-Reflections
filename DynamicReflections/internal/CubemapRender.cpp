#include "CubemapRender.hpp"
#include "TESMain.hpp"
#include "PlayerCharacter.hpp"
#include "BSCullingProcess.hpp"
#include "NiDX9Renderer.hpp"
#include "NiTPointerListBase.hpp"
#include "ImageSpaceManager.hpp"
#include "BSShaderPPLightingProperty.hpp"
#include "BSTextureManager.hpp"
#include "ImageSpaceEffectBlur.hpp"
#include "BGSTerrainManager.hpp"
#include "NiCloningProcess.hpp"
#include "BGSDistantObjectBlock.hpp"
#include "NiFloatExtraData.hpp"

#include <SafeWrite.h>
#include <format>
#include <ScriptUtils.h>

NiRenderedCubeMapPtr CubemapRenderer::spRenderedCubemapPlayer = nullptr;
NiRenderedCubeMapPtr CubemapRenderer::spRenderedCubemapWorld = nullptr;
BSRenderedTexturePtr spFakeCubemap = nullptr;
NiTexture* CubemapRenderer::pSourceEyeCubeMap = nullptr;;
BSCubeMapCameraPtr CubemapRenderer::spPlayerCubeCam = nullptr;
BSCubeMapCameraPtr CubemapRenderer::spWorldCubeCam = nullptr;

UInt32 CubemapRenderer::uiPlayerUpdateRate;
UInt32 CubemapRenderer::uiWorldUpdateRate;

UInt32 CubemapRenderer::uiCubemapSize = 512;
UInt32 CubemapRenderer::uiScreenSpaceCubemapSize;
UInt32 CubemapRenderer::uiScreenSpaceBlurRadius;

float CubemapRenderer::fPlayerViewDistance;
float CubemapRenderer::fWorldViewDistance;
float CubemapRenderer::fInteriorBrightnessMult;
float CubemapRenderer::fExteriorBrightnessMult;

bool CubemapRenderer::bScreenSpaceInterior;
bool CubemapRenderer::bNoWorldInInteriors;
bool CubemapRenderer::bNoWorldInExteriors;
bool CubemapRenderer::bUseAmbient;
bool CubemapRenderer::bEnabled;
bool CubemapRenderer::bOverride;
bool CubemapRenderer::bOverrideBrightness;
bool CubemapRenderer::bHighQuality;
bool CubemapRenderer::bLowQuality;
bool CubemapRenderer::bRenderObjectLOD;
bool CubemapRenderer::bRenderCloseObjectLOD;
bool CubemapRenderer::bRenderLandLOD;
bool CubemapRenderer::bRendering = false;
bool CubemapRenderer::bRefreshCell = false;
bool CubemapRenderer::bDumpToFile = false;

static NiTPointerListBase<NiAVObject*> kSceneNodes;

static bool bInUse_Player = false;
static bool bInUse_World = false;
static NiNodePtr spWeaponNode = nullptr;
static NiNodePtr spCameraNode = nullptr;
static TESObjectCELL* pLastCell = nullptr;

#define bDebugLog false

static UInt32 uiFrameCount = 0;

static BSRenderedTexturePtr spScreenCrop = nullptr;

static const float fWeaponHeightOffset = 107.0f;
static const float fPlayerEyeHeightOffset = 43.0f;

static const UInt32 uiMaxCubemapUseTime = 500; // In frames
static UInt32 uiWorldCubemapUnuseTimer = 0;
static UInt32 uiPlayerCubemapUnuseTimer = 0;
static UInt32 uiPlayerInteriorCubemapUnuseTimer = 0;
static bool bThirdPerson = false;

static bool bILSPresent = false;

static UInt32 uiILSAmbientColorAddr;

namespace LODController {
	static float fOrgLODDrop = 0.f;
	static std::vector<BSSegmentedTriShape*> kShapesToRestore;

	static void ToggleLODRecurse(NiAVObject* apObject, bool abIgnore) {
		if (!apObject)
			return;

		if (apObject->IsNiNode()) {
			NiNode* pNode = (NiNode*)apObject;
			for (UInt32 i = 0; i < pNode->GetArrayCount(); i++)
				ToggleLODRecurse(pNode->GetAt(i), abIgnore);
		}
		else if (apObject->IsSegmentedTriShape()) {
			BSSegmentedTriShape* pSegTriShape = (BSSegmentedTriShape*)apObject;
			pSegTriShape->bIgnoreSegments = abIgnore;
			if (abIgnore) {
				if (!pSegTriShape->pSegments[0].bVisible) {
					kShapesToRestore.push_back(pSegTriShape);
				}
				pSegTriShape->pSegments[0].bVisible = true;
			}
		}
	}

	static void ShowLOD(bool abObjects) {
		fOrgLODDrop = *BSShaderManager::fLODLandDrop;
		*BSShaderManager::fLODLandDrop = 0.f;

		if (abObjects) {
			NiNode* pRoot = *(NiNode**)0x11D8690;
			ToggleLODRecurse(pRoot, true);
		}
	}

	static void HideLOD(bool abObjects) {
		*BSShaderManager::fLODLandDrop = fOrgLODDrop;
		if (abObjects) {
			NiNode* pRoot = *(NiNode**)0x11D8690;
			ToggleLODRecurse(pRoot, false);
			for (BSSegmentedTriShape* pShape : kShapesToRestore) {
				pShape->pSegments[0].bVisible = false;
			}
			kShapesToRestore.clear();
		}
	}
}

static void SetCubemapFlag(NiNode* pObject) {
	UInt32 uiChildCount = pObject->m_kChildren.GetSize();

	if (!uiChildCount)
		return;

	for (UInt32 i = 0; i < uiChildCount; i++) {
		NiAVObject* pChild = pObject->GetAt(i);

		if (!pChild)
			continue;

		BSShaderPPLightingProperty* pShadeProp = nullptr;

		if (pChild->m_kPropertyList.m_uiCount && pChild->IsGeometry()) {
			pShadeProp = static_cast<BSShaderPPLightingProperty*>(pChild->GetProperty(NiProperty::SHADE));

			// Mark shader property as player's
			if (pShadeProp && (pShadeProp->uiExtraFlags & BSShaderLightingProperty::EF_IsPlayer) == 0 && pShadeProp->HasEnvironmentMap())
				pShadeProp->uiExtraFlags |= BSShaderLightingProperty::EF_IsPlayer;
		}

		if (pChild->IsNiNode())
			SetCubemapFlag(static_cast<NiNode*>(pChild));
	}
}

void CubemapRenderer::InitHooks() {
	uiPlayerUpdateRate = max(0, min(uiPlayerUpdateRate, 6));
	uiWorldUpdateRate = max(0, min(uiWorldUpdateRate, 6));

	ReplaceCall(0xB7D374, SLS_SetCubeMap_Hook);
	ReplaceCall(0xC0D088, Shader30_SetCubeMap_Hook);

	// Normal cubemap
	ReplaceCall(0x8727DE, Render_Hook);
	// Pre-hands hook for the screenspace interior cubemap
	ReplaceCall(0x870F46, SetOffScreenRTGroup_Hook);

	if (CubemapRenderer::bOverride)
		ReplaceCall(0xB68DCC, BSShaderProperty_LoadBinary_Hook);

	ReplaceCall(0xB7DC5B, SLS_UpdateToggles_Hook);
	ReplaceCall(0xBBF166, Shader30_UpdateToggles_Hook);
	
	// Fix water flow speed
	// Water surface updates every time its renderd, and we don't want water to run 6x its speed if cubemaps are active
	ReplaceCall(0x4E4027, TESWater::RenderSurface_Hook);

	// Disables RefID writes into the shader property. Should be safe.
	PatchMemoryNop(0x4B6E0E, 5);

	// Removes the mipmap check for rendered textures
	PatchMemoryNop(0xE7EA9F, 0x21);

	// Replaces cubemap creator with a modified version allowing for mipmaps
	ReplaceCall(0xE901D5, NiDX9RenderedCubeMapData::CreateSurf);
}

typedef NiD3DPixelShader* (__cdecl pfn_CreatePixelShader)(const char* apFilename);
typedef NiD3DVertexShader* (__cdecl pfn_CreateVertexShader)(const char* apFilename);
typedef bool* (__cdecl pfn_NVSEPlugin_Query)(const NVSEInterface* nvse, PluginInfo* info);

static pfn_CreatePixelShader* pLoadPixelShader = nullptr;
static pfn_CreateVertexShader* pLoadVertexShader = nullptr;

void CubemapRenderer::CheckShaderLoader() {
	auto hShaderLoader = GetModuleHandle("Fallout Shader Loader.dll");
	if (!hShaderLoader) {
		MessageBox(NULL, "Fallout Shader Loader not found.\nPlease install it to use Real Time Reflections!.", "Real Time Reflections", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	auto pQuery = (pfn_NVSEPlugin_Query*)GetProcAddress(hShaderLoader, "NVSEPlugin_Query");
	PluginInfo kInfo = {};
	pQuery(nullptr, &kInfo);
	if (kInfo.version < 110) {
		MessageBox(NULL, "Fallout Shader Loader is outdated.\nPlease update it to use Real Time Reflections!.", "Real Time Reflections", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	pLoadPixelShader = (pfn_CreatePixelShader*)GetProcAddress(hShaderLoader, "CreatePixelShader");

	if (!pLoadPixelShader) {
		MessageBox(NULL, "Failed to load shader loader functions. How?", "Real Time Reflections", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
}

void CubemapRenderer::LoadShaders() {	
	bool bFailed = false;
	for (UInt32 i = 0; i < 2; i++) {
		char cBuffer[32];
		UInt32 uiShaderID = i + 57;
		sprintf_s(cBuffer, "RTR\\SLS20%i.pso", uiShaderID);
		NiD3DPixelShader* pShader = pLoadPixelShader(cBuffer);
		if (pShader)
			ShadowLightShader::SetPixelShader(uiShaderID + 48, pShader);
		else {
			_MESSAGE("[ CubemapRenderer::LoadShaders ] Failed to load pixel shader %s", cBuffer);
			bFailed = true;
			break;
		}
	}

	for (UInt32 i = 0; i < 2; i++) {
		char cBuffer[32];
		UInt32 uiShaderID = i + 24;
		sprintf_s(cBuffer, "RTR\\SM30%i.pso", uiShaderID);
		NiD3DPixelShader* pShader = pLoadPixelShader(cBuffer);
		if (pShader)
			Lighting30Shader::SetPixelShader(uiShaderID, pShader);
		else {
			_MESSAGE("[ CubemapRenderer::LoadShaders ] Failed to load pixel shader %s", cBuffer);
			bFailed = true;
			break;
		}
	}

	if (!bFailed) {
		ShadowLightShader::InitPasses_2xEnvMap();
		Lighting30Shader::GetShader()->InitPasses();
		_MESSAGE("[ CubemapRenderer::LoadShaders ] Shaders loaded successfully");
	}
	else {
		MessageBox(NULL, "Failed to load shaders. Please check your installation.", "Real Time Reflections", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
}

void CubemapRenderer::CheckILSStatus() {
	UInt32 uiILSBase = (UInt32)GetModuleHandle("ImprovedLightingShaders.dll");

	if (uiILSBase != 0) {
		bool* bIncreaseLightBuffers = (bool*)(uiILSBase + 0x2240D);
		if (*bIncreaseLightBuffers) {
			uiILSAmbientColorAddr = uiILSBase + 0x22638;
			_MESSAGE("[ CubemapRenderer::CheckILSStatus ] ILS detected. Ambient color should be at %x", uiILSAmbientColorAddr);
			bILSPresent = true;
		}
		else {
			_MESSAGE("[ CubemapRenderer::CheckILSStatus ] ILS detected, but the bIncreaseLightBuffers is off");
		}
	}
}

static __forceinline NiColorA* GetAmbientColorILS() {
	return (NiColorA*)uiILSAmbientColorAddr;
}


bool CubemapRenderer::SearchCamera(TESObjectCELL* apCell)
{
	NiNode* pStaticsNode = apCell->GetChildNode(TESObjectCELL::CN_STATIC);
	spCameraNode = static_cast<NiNode*>(pStaticsNode->GetObjectByNameEx("CellCamera"));

	if (spCameraNode.m_pObject) {
#if bDebugLog
		_MESSAGE("[ CubemapRenderer::RenderCubemap ] CellCamera found");
#endif
		return true;
	}

	for (UInt32 i = 0; i < TESObjectCELL::CN_MAX; i++) {
		NiNode* pCellNode = apCell->GetChildNode(static_cast<TESObjectCELL::CELLNODE>(i));
		if (pCellNode) {
			spCameraNode = static_cast<NiNode*>(pCellNode->GetObjectByNameEx("CellCamera"));
			if (spCameraNode.m_pObject) {
#if bDebugLog
				_MESSAGE("[ CubemapRenderer::RenderCubemap ] CellCamera found");
#endif
				return true;
			}
		}
		else {
#if bDebugLog
			_MESSAGE("[ CubemapRenderer::RenderCubemap ] CellCamera not found");
#endif
			spCameraNode = nullptr;
		}
	}

	return false;
}

static float fOrgEnd;
static float fOrgStart;

void CubemapRenderer::UpdateFog(ShadowSceneNode* apScene, float afViewDistance, NiCamera* apCamera) {
	fOrgEnd = apScene->spFog->fEndDistance;
	fOrgStart = apScene->spFog->fStartDistance;

	float fEnd = afViewDistance * 0.8f;
	float fStart = afViewDistance * 0.6f;

	if (fEnd > fOrgEnd) {
		fEnd = fOrgEnd;
		apCamera->m_kViewFrustum.m_fFar = fEnd * 1.2f;
	}
	else {
		apCamera->m_kViewFrustum.m_fFar = afViewDistance;
	}

	if (fStart > fOrgStart)
		fStart = fOrgStart;

	apScene->spFog->fEndDistance = fEnd;
	apScene->spFog->fStartDistance = fStart;
}

void CubemapRenderer::RestoreFog(ShadowSceneNode* apScene) {
	apScene->spFog->fEndDistance = fOrgEnd;
	apScene->spFog->fStartDistance = fOrgStart;
}

void CubemapRenderer::ManageTextureResidency(UInt32 uiForcePurge) {
	bool bWorldCubemap = false;
	bool bPlayerCubemap = false;
	bool bFakeCubemap = false;

	bool bPlayerInactiveUse = false;
	bool bWorldInactiveUse = false;
	bool bInteriorInactiveUse = false;

	if (spWorldCubeCam.m_pObject)
		bWorldCubemap = spWorldCubeCam->spTexture.m_pObject && spRenderedCubemapWorld.m_pObject;

	if (spPlayerCubeCam.m_pObject)
		bPlayerCubemap = spPlayerCubeCam->spTexture.m_pObject && spRenderedCubemapPlayer.m_pObject;

	if (bScreenSpaceInterior)
		bFakeCubemap = spScreenCrop.m_pObject && spFakeCubemap.m_pObject;

	bool bPlayerMapOverride = bHighQuality && bInUse_World;
	bool bInteriorPlayerOverride = !bNoWorldInInteriors && *BSShaderManager::bIsInInterior && (bInUse_World || bInUse_Player);
	bool bInteriorCubemapAllowed = CanRenderInteriorCubemap();

	if ( (!bInUse_Player || bInteriorCubemapAllowed) && bPlayerCubemap && !bInteriorPlayerOverride && !bPlayerMapOverride) {
		if (uiPlayerCubemapUnuseTimer < uiMaxCubemapUseTime)
			uiPlayerCubemapUnuseTimer++;

		bPlayerInactiveUse = true;
	}
	else {
		uiPlayerCubemapUnuseTimer = 0;
	}

	if (!bInUse_World && bWorldCubemap) {
		if (uiWorldCubemapUnuseTimer < uiMaxCubemapUseTime)
			uiWorldCubemapUnuseTimer++;

		bWorldInactiveUse = true;
	}
	else {
		uiWorldCubemapUnuseTimer = 0;
	}


	if (bScreenSpaceInterior && bFakeCubemap && (!bInUse_Player || !*BSShaderManager::bIsInInterior)) {
		if (uiPlayerInteriorCubemapUnuseTimer < uiMaxCubemapUseTime) {
			uiPlayerInteriorCubemapUnuseTimer++;
		}

		bInteriorInactiveUse = true;
	}
	else {
		uiPlayerInteriorCubemapUnuseTimer = 0;
	}


#if bDebugLog
	_MESSAGE("Texture states: Player %i, World %i, Interior %i      |      Timers: Player %i, World %i, Interior %i      |      Usage stats: Player %i, World %i, Interior %i", 
		bPlayerCubemap, bWorldCubemap, bFakeCubemap, uiPlayerCubemapUnuseTimer, uiWorldCubemapUnuseTimer, uiPlayerInteriorCubemapUnuseTimer, bPlayerInactiveUse, bWorldInactiveUse, bInteriorInactiveUse);
#endif


	if (uiWorldCubemapUnuseTimer >= uiMaxCubemapUseTime && bWorldCubemap) {
		spWorldCubeCam->spTexture = nullptr;
		spRenderedCubemapWorld = nullptr;

		uiWorldCubemapUnuseTimer = 0;

#if bDebugLog
		_MESSAGE("[ CubemapRenderer::RenderCubemap ] Purging world cube map");
#endif
	}

	if (uiPlayerCubemapUnuseTimer >= uiMaxCubemapUseTime && bPlayerCubemap) {
		spPlayerCubeCam->spTexture = nullptr;
		spRenderedCubemapPlayer = nullptr;

		uiPlayerCubemapUnuseTimer = 0;
#if bDebugLog
		_MESSAGE("[ CubemapRenderer::RenderCubemap ] Purging player cube map");
#endif
	}

	if (uiPlayerInteriorCubemapUnuseTimer >= uiMaxCubemapUseTime && bFakeCubemap) {
		spScreenCrop = nullptr;
		spFakeCubemap = nullptr;

		uiPlayerInteriorCubemapUnuseTimer = 0;

#if bDebugLog
		_MESSAGE("[ CubemapRenderer::RenderCubemap ] Purging interior player cube map");
#endif
	}

	if (uiFrameCount > 15) {
		SetCubemapFlag(PlayerCharacter::GetSingleton()->Get3D());
		uiFrameCount = 0;
	}
}

bool CubemapRenderer::CanRenderInteriorCubemap() {
	return bScreenSpaceInterior && *BSShaderManager::bIsInInterior;
}

BSCubeMapCamera* CubemapRenderer::GetPlayerCamera() {
	if (!spPlayerCubeCam.m_pObject) {
		_MESSAGE("[ CubemapRenderer::RenderCubemap ] Creating player cubemap camera. View distance: %f", fPlayerViewDistance);
		spPlayerCubeCam = BSCubeMapCamera::Create(TESMain::GetWorldRoot(), fPlayerViewDistance, uiCubemapSize, D3DFMT_A16B16G16R16F);
		spPlayerCubeCam->SetName("Player Reflections");
	}
	return spPlayerCubeCam;
}

BSCubeMapCamera* CubemapRenderer::GetWorldCamera() {
	if (!spWorldCubeCam.m_pObject) {
		_MESSAGE("[ CubemapRenderer::RenderCubemap ] Creating world cubemap camera. View distance: %f", fWorldViewDistance);
		spWorldCubeCam = BSCubeMapCamera::Create(nullptr, fWorldViewDistance, uiCubemapSize, D3DFMT_A16B16G16R16F);
		spWorldCubeCam->SetName("World Reflections");
	}
	return spWorldCubeCam;
}

BSRenderedTexture* CubemapRenderer::GetPlayerTexture() {
	if (!spPlayerCubeCam.m_pObject)
		GetPlayerCamera();

	if (spPlayerCubeCam->spTexture.m_pObject)
		return spPlayerCubeCam->spTexture.m_pObject;

#if bDebugLog
	_MESSAGE("[ CubemapRenderer::RenderCubemap ] Creating player cubemap texture");
#endif

	spPlayerCubeCam->spTexture = BSTextureManager::NewRenderedCubemap(uiCubemapSize, 0, D3DFMT_A16B16G16R16F, 0);
	return spPlayerCubeCam->spTexture.m_pObject;
}

BSRenderedTexture* CubemapRenderer::GetWorldTexture() {
	if (!spWorldCubeCam.m_pObject)
		GetWorldCamera();

	if (spWorldCubeCam->spTexture.m_pObject)
		return spWorldCubeCam->spTexture;

#if bDebugLog
	_MESSAGE("[ CubemapRenderer::RenderCubemap ] Creating world cubemap texture");
#endif

	spWorldCubeCam->spTexture = BSTextureManager::NewRenderedCubemap(uiCubemapSize, 0, D3DFMT_A16B16G16R16F, 0);
	return spWorldCubeCam->spTexture;
}

void CubemapRenderer::CreateScreenSpaceTextures(UInt32 uiCubeSize) {
	if (!spScreenCrop.m_pObject) {
#if bDebugLog
		_MESSAGE("[ CubemapRenderer::RenderSceenSpaceCubemap ] Creating a crop texture %i x %i", uiCubeSize, uiCubeSize);
#endif
		spScreenCrop = BSTextureManager::NewRenderedTexture(uiCubeSize, uiCubeSize, BSTM_CF_NO_DEPTH | BSTM_CF_NO_STENCIL, D3DFMT_A16B16G16R16F, 0);
	}

	if (!spFakeCubemap.m_pObject) {
#if bDebugLog
		_MESSAGE("[ CubemapRenderer::RenderSceenSpaceCubemap ] Creating a fake cubemap texture %i x %i", uiCubeSize, uiCubeSize);
#endif
		spFakeCubemap = BSTextureManager::NewRenderedCubemap(uiCubeSize, BSTM_CF_NO_DEPTH | BSTM_CF_NO_STENCIL, D3DFMT_A16B16G16R16F, 0);
	}
}


// This thing is getting a massive rework in the next update
void CubemapRenderer::RenderCubemap() {
	if (!bEnabled)
		return;

	ManageTextureResidency();

	NiDX9Renderer* pRenderer = NiDX9Renderer::GetSingleton();
	PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
	TESObjectCELL* pCurrCell = pPlayer->GetParentCell();

	static bool bCheckCellAgain = false;
	bool bCellChanged = false;
	bThirdPerson = pPlayer->IsThirdPerson();

	// Remove cell camera if it has only one refence (us)
	// Normally it should have at least 2 references - one from the cell and one from us
	// This is to handle cases like Update3D where the model is being reloaded
	if (spCameraNode.m_pObject && spCameraNode->m_uiRefCount == 1) {
		spCameraNode = nullptr;
		bRefreshCell = true;
	}

	if ((!pLastCell || pLastCell != pCurrCell || bCheckCellAgain || bRefreshCell) && pCurrCell) {
		bCellChanged = true;
		pLastCell = pCurrCell;
		spCameraNode = nullptr;
		spRenderedCubemapWorld = nullptr;
		bCheckCellAgain = false;
		bRefreshCell = false;
	}

	if (bCellChanged) {
#if bDebugLog
		_MESSAGE("[ CubemapRenderer::RenderCubemap ] Cell changed");
#endif
		if (TES::IsCellLoaded(pCurrCell, true)) {
			SearchCamera(pCurrCell);
		}
		else {
#if bDebugLog
			_MESSAGE("[ CubemapRenderer::RenderCubemap ] Cell not loaded");
#endif
			bCheckCellAgain = true;
		}
	}

	bool bUseCellCamera = bInUse_World && spCameraNode.m_pObject;
	SkipMode eShouldSkip = SKIP_NONE;

	if (CanRenderInteriorCubemap())
		eShouldSkip = SKIP_ALL;

	if (eShouldSkip && bUseCellCamera)
		eShouldSkip = SKIP_PLAYER;

	if (eShouldSkip && bThirdPerson) {
		spRenderedCubemapPlayer = nullptr;
		spRenderedCubemapWorld = nullptr;
		bInUse_Player = false;
	}

	if (eShouldSkip != SKIP_ALL) {
		SceneGraph* pSceneGraph = TESMain::GetWorldRoot();
		ShadowSceneNode* pShadowSceneNode = BSShaderManager::GetShadowSceneNode(BSShaderManager::BSSM_SSN_WORLD);
		NiNode* pSkyRoot = TESMain::GetSkyRoot();
		NiPoint3 skyPos = pSkyRoot->GetWorldTranslate();

		NiNode* pPlayerNode1 = pPlayer->GetNode(true);
		NiNode* pPlayerNode2 = pPlayer->GetNode(false);
		NiPoint3 playerPos = pPlayerNode1->GetWorldTranslate();


		// Adjust camera position average weapon height
		playerPos.z += fWeaponHeightOffset;

		bool bLightProcessing = pShadowSceneNode->bDisableLightUpdate;
		pShadowSceneNode->bDisableLightUpdate = true;

		bool bWorldOverride = bInUse_World && bHighQuality;
		bool bInteriorOverride = bInUse_World && *BSShaderManager::bIsInInterior;

		// Check player's visibility
		bool bPlayerVisible1 = pPlayerNode1->GetAppCulled();
		bool bPlayerVisible2 = pPlayerNode2->GetAppCulled();

		// Cull player before rendering
		pPlayerNode1->SetAppCulled(true);
		pPlayerNode2->SetAppCulled(true);

		const UInt32 uiOrgPasses = BSShaderManager::uiEnabledPasses->Get();
		BSShaderManager::uiEnabledPasses->RawSet(BSShaderManager::AMBIENT | BSShaderManager::DIFFUSE | BSShaderManager::TEXTURE | BSShaderManager::OPT);

		// Player cubemap
		if (eShouldSkip != SKIP_PLAYER && (bInUse_Player && !bLowQuality || bWorldOverride || bInteriorOverride || bDumpToFile)) {

			BSCubeMapCamera* pPlayerCubeCam = GetPlayerCamera();
			BSRenderedTexture* pPlayerTexture = GetPlayerTexture();

			if (spWeaponNode.m_pObject && spWeaponNode->m_uiRefCount < 2)
				spWeaponNode = nullptr;

			if (!spWeaponNode.m_pObject)
				spWeaponNode = static_cast<NiNode*>(pPlayerNode1->GetObjectByNameEx("Weapon"));

			NiPoint3 weaponPos = spWeaponNode->GetWorldTranslate();
			if (pPlayer->IsWeaponOut() && !*BSShaderManager::bIsInInterior && !bHighQuality)
				pPlayerCubeCam->SetLocalTranslate(bThirdPerson ? &playerPos : &weaponPos);
			else
				pPlayerCubeCam->SetLocalTranslate(&playerPos);

			UInt32 uiUpdateRate = *BSShaderManager::bIsInInterior ? min(uiPlayerUpdateRate + 1, 6) : uiPlayerUpdateRate;
			if (bDumpToFile)
				uiUpdateRate = 6;

			pSkyRoot->SetLocalTranslate(pPlayerCubeCam->GetWorldTranslate());
			pSkyRoot->Update(g_defaultUpdateData);

			bRendering = true;

#if bDebugLog
			_MESSAGE("[ CubemapRenderer::RenderCubemap ] Rendering player cubemap");
#endif

			UpdateFog(pShadowSceneNode, CubemapRenderer::fPlayerViewDistance, pPlayerCubeCam);
			pPlayerCubeCam->RenderCubeMap(0, uiUpdateRate, bDumpToFile ? BSCullingProcess::BSCP_CULL_ALLPASS : BSCullingProcess::BSCP_CULL_FORCEMULTIBOUNDSNOUPDATE, true);
			RestoreFog(pShadowSceneNode);

			bRendering = false;

			// Setting player cube map
			spRenderedCubemapPlayer = static_cast<NiRenderedCubeMap*>(pPlayerTexture->spRenderedTextures[0].m_pObject);

			if (bInUse_World && (bHighQuality || *BSShaderManager::bIsInInterior)) {
				spRenderedCubemapWorld = spRenderedCubemapPlayer;
			}
		}

		// Restore player visibility
		pPlayerNode1->SetAppCulled(bPlayerVisible1);
		pPlayerNode2->SetAppCulled(bPlayerVisible2);

		// World cubemap
		if (bUseCellCamera || ((bInUse_World || bLowQuality) && !(*BSShaderManager::bIsInInterior || bHighQuality)) ) {

			BSCubeMapCamera* pWorldCubeCam = GetWorldCamera();
			BSRenderedTexture* pWorldTexture = GetWorldTexture();

			if (spCameraNode.m_pObject) {
				pWorldCubeCam->SetLocalTranslate(spCameraNode->GetWorldTranslate());
			}

			kSceneNodes.RemoveAll();

			if (!spCameraNode.m_pObject) {
				// Adjust camera position to use eye height
				playerPos.z += fPlayerEyeHeightOffset;
				pWorldCubeCam->SetLocalTranslate(playerPos);
			}

			BGSTerrainManager* pTerrainManager = TES::GetWorldSpace()->GetTerrainManager();


			// Add nodes to the list to be rendered
			if (spCameraNode.m_pObject) {
				kSceneNodes.AddHead(pSceneGraph);

				// Temporarily move sky to the camera position - it's normally set to player's
				pSkyRoot->SetLocalTranslate(spCameraNode->GetWorldTranslate());
				pSkyRoot->Update(g_defaultUpdateData);

				if (!bThirdPerson) {
					// Setup player nodes to be visible in mirrors
					pPlayerNode1->SetAppCulled(true);
					pPlayerNode2->SetAppCulled(false);
				}
			}
			else {
				kSceneNodes.AddHead(pSkyRoot);

				if (bRenderObjectLOD) {
					kSceneNodes.AddHead(BGSTerrainManager::GetRootObjectLODNode());
				}

				if (bRenderLandLOD) {
					kSceneNodes.AddHead(BGSTerrainManager::GetRootLandLODNode());
					kSceneNodes.AddHead(pTerrainManager->GetWaterLODNode());
				}

				LODController::ShowLOD(bRenderCloseObjectLOD);
			}

			bRendering = true;

#if bDebugLog
			_MESSAGE("[ CubemapRenderer::RenderCubemap ] Rendering world cubemap");
#endif

			UpdateFog(pShadowSceneNode, CubemapRenderer::fWorldViewDistance, pWorldCubeCam);
			pWorldCubeCam->RenderCubeMap(&kSceneNodes, uiWorldUpdateRate, BSCullingProcess::BSCP_CULL_FORCEMULTIBOUNDSNOUPDATE, bRenderLandLOD);
			RestoreFog(pShadowSceneNode);

			bRendering = false;

			if (!spCameraNode.m_pObject){
				LODController::HideLOD(bRenderCloseObjectLOD);
			}

			spRenderedCubemapWorld = static_cast<NiRenderedCubeMap*>(pWorldTexture->spRenderedTextures[0].m_pObject);

			if (bLowQuality) {
				spRenderedCubemapPlayer = spRenderedCubemapWorld;
			}
		}

		if (bNoWorldInInteriors && *BSShaderManager::bIsInInterior || bNoWorldInExteriors && !*BSShaderManager::bIsInInterior) {
			spRenderedCubemapWorld = nullptr;
		}

		// Set eye reflection cubemap
		if (spRenderedCubemapPlayer.m_pObject)
			BSShaderManager::SetEyeReflectionCubeMap(spRenderedCubemapPlayer);
		else
			BSShaderManager::SetEyeReflectionCubeMap(pSourceEyeCubeMap);

		// Restore original player visibility, again
		pPlayerNode1->SetAppCulled(bPlayerVisible1);
		pPlayerNode2->SetAppCulled(bPlayerVisible2);

		// Restore original sky position
		pSkyRoot->SetLocalTranslate(skyPos);
		pSkyRoot->Update(g_defaultUpdateData);

		pShadowSceneNode->bDisableLightUpdate = bLightProcessing;

		BSShaderManager::uiEnabledPasses->RawSet(uiOrgPasses);

		SaveCubemapToFiles();

		// Regenerate cubemap mipmaps
		if (spRenderedCubemapPlayer.m_pObject)
			spRenderedCubemapPlayer->GetDX9RendererData()->GetD3DTexture()->SetAutoGenFilterType(D3DTEXF_LINEAR);

		if (spRenderedCubemapWorld.m_pObject)
			spRenderedCubemapWorld->GetDX9RendererData()->GetD3DTexture()->SetAutoGenFilterType(D3DTEXF_LINEAR);
	}

	bInUse_World = false;

	if (eShouldSkip == SKIP_NONE)
		bInUse_Player = false;

	uiFrameCount++;
}

// oh god oh god it's so wrong
void CubemapRenderer::RenderSceenSpaceCubemap() {
	if (!bEnabled || !CanRenderInteriorCubemap())
		return;

	PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();

	if (bInUse_Player && !pPlayer->bThirdPerson) {
		BSRenderedTexture* apTexture = TESMain::GetMainISTexture();
		NiDX9Renderer* pRenderer = NiDX9Renderer::GetSingleton();

		static bool bResSet = false;
		static NiRect<UInt32> rect;
		static NiRect<UInt32> rect2;
		static UInt32 uiCubeSize = uiScreenSpaceCubemapSize;

		// Get source buffer
		Ni2DBuffer* pSourceBuffer = apTexture->GetTexture(0)->GetBuffer();

		// Create the texture that will be used
		CreateScreenSpaceTextures(uiCubeSize);

		if (!bResSet) {
			UInt32 uiFullHeight = pSourceBuffer->GetHeight();
			UInt32 uiFullWidth = pSourceBuffer->GetWidth();

			// Create a crop rectangle
			UInt32 top = 0;
			UInt32 bottom = uiFullHeight;
			UInt32 left = (uiFullWidth - uiFullHeight) / 2;
			UInt32 right = uiFullHeight + left;

			// Source
			rect = NiRect<UInt32>(left, right, top, bottom);

			// Destination
			rect2 = NiRect<UInt32>(0, uiCubeSize, 0, uiCubeSize);
			bResSet = true;
		}

		spScreenCrop->SetRenderTargetGroup(NiRenderer::CLEAR_ALL);

		// Perform the copy operation
		Ni2DBuffer* pScreenCrop = spScreenCrop->GetTexture(0)->GetBuffer();

		pRenderer->Copy(pSourceBuffer, pScreenCrop, &rect, &rect2, Ni2DBuffer::COPY_FILTER_LINEAR);

		ImageSpaceManager* pImageSpaceManager = ImageSpaceManager::GetSingleton();
		ImageSpaceTexture ISTexture = ImageSpaceTexture();
		ISTexture.SetTextureRenderTarget(spScreenCrop);

		ImageSpaceEffectBlur::SetBlurRadius(uiScreenSpaceBlurRadius);
		ImageSpaceManager::EffectID eBlurType = ImageSpaceManager::IS_EFFECT_BLUR_15;
		ImageSpaceEffect* pBlurEffect = pImageSpaceManager->GetEffect(eBlurType);

		pBlurEffect->SetTexture(2, &ISTexture, ImageSpaceTexture::TEXTURE_FILTER_MODE_NEAREST);
		pImageSpaceManager->RenderEffect(eBlurType, pRenderer, spScreenCrop, spScreenCrop, 0, true);

		for (UInt32 i = 0; i < 6; i++) {
			spScreenCrop->spRenderedTextures[0]->m_spBuffer->FastCopy(static_cast<NiRenderedCubeMap*>(spFakeCubemap->spRenderedTextures[0].m_pObject)->m_aspFaceBuffers[i], nullptr, 0, 0);
		}
		
		spRenderedCubemapPlayer = static_cast<NiRenderedCubeMap*>(spFakeCubemap->spRenderedTextures[0].m_pObject);
		BSShaderManager::SetEyeReflectionCubeMap(pSourceEyeCubeMap);

		bInUse_Player = false;
	}
}

void CubemapRenderer::SaveCubemapToFiles() {
	if (bDumpToFile) {
		D3DXSaveTextureToFile("player_cubemap.dds", D3DXIFF_DDS, spRenderedCubemapPlayer->GetDX9RendererData()->GetD3DTexture(), 0);
		bDumpToFile = false;
	}
}

// 0xB7C290
void __fastcall CubemapRenderer::SLS_SetCubeMap_Hook(ShadowLightShader* apThis, void*, BSShaderPPLightingProperty* apShaderProp, UInt32 auiTexturePass, UInt32 auiTextureNumber) {
	//apThis->SetDiffuseMap(apShaderProp, 2, 0);
	
	NiD3DTextureStage* pTexStage = NiD3DShader::GetCurrentPass()->GetStage(1);

	NiTexture* pTexture = apShaderProp->ppTextures[BSTextureSet::BSSM_CubeMap][auiTextureNumber];

	if ((apShaderProp->ulFlags[1] & BSShaderProperty::Wall_RealTimeEnv || bOverride) && !bRendering) {
		// Check if we should use the player cubemap
		if (apShaderProp->uiExtraFlags & BSShaderLightingProperty::EF_IsPlayer) {
			bInUse_Player = true;
			if (spRenderedCubemapPlayer.m_pObject)
				pTexture = spRenderedCubemapPlayer;
		}
		else {
			bInUse_World = true;
			if (spRenderedCubemapWorld.m_pObject)
				pTexture = spRenderedCubemapWorld;
		}
	}

	if(!pTexture)
		pTexture = BSShaderManager::GetArmorReflectionCubeMap();

	pTexStage->m_pkTexture = pTexture;
	pTexStage->SetClampMode(NiTexturingProperty::CLAMP_S_CLAMP_T);
}

// 0xC0BC00
void __fastcall CubemapRenderer::Shader30_SetCubeMap_Hook(Lighting30Shader* apThis, void*, NiD3DPass* apPass, BSShaderPPLightingProperty* apShaderProp, RenderPassTypes aeRenderPass) {
	NiTexture* pTexture = nullptr;

	if ((apShaderProp->ulFlags[1] & BSShaderProperty::Wall_RealTimeEnv || bOverride) && !bRendering) {
		// Check if we should use the player cubemap
		if (apShaderProp->uiExtraFlags & BSShaderLightingProperty::EF_IsPlayer) {
			bInUse_Player = true;
			if (spRenderedCubemapPlayer.m_pObject)
				pTexture = spRenderedCubemapPlayer;
		}
		else {
			bInUse_World = true;
			if (spRenderedCubemapWorld.m_pObject)
				pTexture = spRenderedCubemapWorld;
		}
	}

	if (pTexture)
		apPass->GetStage(1)->m_pkTexture = pTexture;
	else
		ThisStdCall(0xC0BC00, apThis, apPass, apShaderProp, aeRenderPass);

}

void __fastcall CubemapRenderer::BSShaderProperty_LoadBinary_Hook(BSShaderProperty* apThis, void*, DWORD* kStream) {
	ThisStdCall(0xBA92C0, apThis, kStream);
	if (apThis->HasEnvironmentMap()) {
		apThis->ulFlags[0] &= ~BSShaderProperty::Window_Environment_Mapping;
		apThis->ulFlags[1] &= ~BSShaderProperty::Envmap_Light_Fade;
		apThis->ulFlags[1] &= ~BSShaderProperty::Billboard_and_Envmap_Light_Fade;
	}
}

void* __fastcall CubemapRenderer::Render_Hook(void* apThis) {
	RenderCubemap();
	return (bool*)(0x11C7ADC+4);
}

void __fastcall CubemapRenderer::SetOffScreenRTGroup_Hook(TESMain* apThis, void*, BSRenderedTexture* pTexture, BOOL bIsMSAA, UInt32 uiClearMode) {
	CubemapRenderer::RenderSceenSpaceCubemap();
	apThis->SetOffScreenRTGroup(pTexture, uiClearMode);
}

void __fastcall CubemapRenderer::SLS_UpdateToggles_Hook(ShadowLightShader* apThis, void*, RenderPassTypes aeRenderPassType, NiGeometry* apGeo, BSShaderPPLightingProperty* apShaderProp, NiMaterialProperty* apMatProp, BSRenderPass* apRenderPass, NiAlphaProperty* apAlphaProp) {
	ThisStdCall(0xB795B0, apThis, aeRenderPassType, apGeo, apShaderProp, apMatProp, apRenderPass, apAlphaProp);
	
	// These checks are pretty much come from the original function. I hate repeating them, but oh well.
	if (!(aeRenderPassType >= BSSM_2x_ENVMAP && aeRenderPassType <= BSSM_2x_ENVMAP_EYE && (aeRenderPassType - 584) <= 3))
		return;


	NiSourceTexture* pMask = static_cast<NiSourceTexture*>(apShaderProp->GetTexture(BSTextureSet::BSSM_EnvMask, 0));
	ShadowLightShaderManager::Toggles* pToggles = ShadowLightShaderManager::PixelConstants::GetToggles();
	float fMaskPresent = 0.f;

	if (pMask) {
		fMaskPresent = 1.f;

		// Check if mask uses an alpha format; needed to enable mipmap blur
		NiPixelFormat::Format eFormat = pMask->GetDX9RendererData()->m_kPixelFormat.m_eFormat;
		if (eFormat == NiPixelFormat::FORMAT_DXT3 || eFormat == NiPixelFormat::FORMAT_DXT5 || eFormat == NiPixelFormat::FORMAT_RGBA) {
			fMaskPresent = -1.f;
		}
	}

	pToggles->fAlphaTestRef = fMaskPresent;

	// Override normal map strength used in the cubemap if requested
	float fNormalStrength = 1.0f;
	static const NiFixedString strNormalIntensity = NiFixedString("NormalIntensity");
	NiFloatExtraData* pFloatData = static_cast<NiFloatExtraData*>(apGeo->GetExtraData(strNormalIntensity));

	if (pFloatData)
		fNormalStrength = min(15, pFloatData->m_fValue);

	ShadowLightShaderManager::PixelConstants::GetToggles()->Unknown = fNormalStrength;

	bool bIsPlayer = apShaderProp->uiExtraFlags & BSShaderLightingProperty::EF_IsPlayer;
	bool bFakeInterior = CanRenderInteriorCubemap();

	if (apShaderProp->HasEnvironmentMap() && (apShaderProp->ulFlags[1] & BSShaderProperty::Wall_RealTimeEnv || bOverride)) {

		if (bOverrideBrightness) {
			float fOverrideSpec = apShaderProp->fEnvMapScale * *BSShaderManager::bIsInInterior ? fInteriorBrightnessMult : fExteriorBrightnessMult;

			if (bFakeInterior && !spRenderedCubemapWorld.m_pObject || bNoWorldInExteriors || bNoWorldInInteriors) {
				// Make sure we are applying to player's shaders
				if (bIsPlayer) {
					pToggles->fSpecularity = fOverrideSpec;
				}
			}
			else {
				pToggles->fSpecularity = fOverrideSpec;
			}
		}
	}

	// Set ambient color to prevent cubemaps unnaturally glowing in dark areas
	// Forces 1s in order to prevent color leaks from previous passes (ambient is also used for emissive color - we don't want glowing cubemaps)
	// Alpha is skipped as it's used as the fade value
	NiColorA* pAmbientConstant = bILSPresent ? GetAmbientColorILS() : ShadowLightShaderManager::PixelConstants::GetAmbientColor();

	if (bUseAmbient && bFakeInterior && (!bIsPlayer || (bIsPlayer && bThirdPerson))) {
		NiColor* pAmbient = Sky::GetInstance()->GetAmbientColor();
		pAmbientConstant->r = pAmbient->r;
		pAmbientConstant->g = pAmbient->g;
		pAmbientConstant->b = pAmbient->b;
	}
	else {
		pAmbientConstant->r = 1.0f;
		pAmbientConstant->g = 1.0f;
		pAmbientConstant->b = 1.0f;
	}
}

void __fastcall CubemapRenderer::Shader30_UpdateToggles_Hook(Lighting30Shader* apThis, void*, BSShaderPPLightingProperty* apShaderProp) {
	if (Lighting30ShaderManager::GetPixelConstantMapEntry(Lighting30Shader::kPX_EnvMapToggles)->bActive) {

		BSRenderPass* pPass = BSRenderPass::GetCurrentPass();
		NiGeometry* pGeo = pPass->pGeometry;
		Lighting30ShaderManager::EnvToggles* pToggles = Lighting30ShaderManager::PixelConstants::GetEnvToggles();

		NiSourceTexture* pMask = static_cast<NiSourceTexture*>(apShaderProp->GetTexture(BSTextureSet::BSSM_EnvMask, 0));


		float fMaskPresent = 0.f;

		if (pMask) {
			fMaskPresent = 1.f;

			// Check if mask uses an alpha format; needed to enable mipmap blur
			NiPixelFormat::Format eFormat = pMask->GetDX9RendererData()->m_kPixelFormat.m_eFormat;
			if (eFormat == NiPixelFormat::FORMAT_DXT3 || eFormat == NiPixelFormat::FORMAT_DXT5 || eFormat == NiPixelFormat::FORMAT_RGBA) {
				fMaskPresent = -1.f;
			}
		}

		pToggles->bHasMask = fMaskPresent;

		pToggles->fEnvMapScale = apShaderProp->fEnvMapScale;
	}
}
