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

#include <SafeWrite.h>
#include <format>
#include <ScriptUtils.h>

NiRenderedCubeMapPtr CubemapRenderer::spRenderedCubemapPlayer = nullptr;
NiRenderedCubeMapPtr CubemapRenderer::spRenderedCubemapWorld = nullptr;
BSRenderedTexturePtr spFakeCubemap = nullptr;
NiTexture* CubemapRenderer::pSourceEyeCubeMap = nullptr;;
BSCubeMapCameraPtr CubemapRenderer::spPlayerCubeCam = nullptr;
BSCubeMapCameraPtr CubemapRenderer::spWorldCubeCam = nullptr;

UInt32 CubemapRenderer::uiPlayerCubemapSize;
UInt32 CubemapRenderer::uiWorldCubemapSize;
UInt32 CubemapRenderer::uiPlayerUpdateRate;
UInt32 CubemapRenderer::uiWorldUpdateRate;
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
bool CubemapRenderer::bRenderLandLOD;

bool CubemapRenderer::bRendering = false;

static NiTPointerListBase<NiAVObject*> kSceneNodes;

static bool bInUse_Player = false;
static bool bInUse_World = false;
static NiNode* pWeaponNode = nullptr;
static NiNode* pCameraNode = nullptr;
static TESObjectCELL* pLastCell = nullptr;

#define bDumpNextFrame *(bool*)0x11F5AF1

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

void SetCubemapFlag(NiNode* pObject) {
	UInt32 uiChildCount = pObject->m_kChildren.GetSize();
	if (!uiChildCount)
		return;

	for (UInt32 i = 0; i < uiChildCount; i++) {
		NiAVObject* pChild = pObject->GetAt(i);
		BSShaderPPLightingProperty* pShadeProp = nullptr;
		if (pChild) [[likely]] {
			if (pChild->m_kPropertyList.m_uiCount && pChild->IsGeometry()) {
				pShadeProp = static_cast<BSShaderPPLightingProperty*>(pChild->GetProperty(NiProperty::SHADE));
				
				// Mark shader property as player's
				if (pShadeProp && (pShadeProp->uiExtraFlags & 1) == 0 && pShadeProp->m_eShaderType == NiShadeProperty::kType_PPLighting && pShadeProp->HasEnvironmentMap()) {
					pShadeProp->uiExtraFlags |= 1;
				}
			}

			if (pChild->IsNiNode()) {
				SetCubemapFlag(static_cast<NiNode*>(pChild));
			}
		}
	}
}

void CubemapRenderer::InitHooks() {
	if (uiPlayerCubemapSize % 2 != 0)
		uiPlayerCubemapSize = 256;

	if (uiWorldCubemapSize % 2 != 0)
		uiWorldCubemapSize = 256;

	uiPlayerUpdateRate = max(0, min(uiPlayerUpdateRate, 6));
	uiWorldUpdateRate = max(0, min(uiWorldUpdateRate, 6));

	ReplaceCall(0xB7C2AA, SLS_GetCubeMap_Hook);
	ReplaceCall(0xC0D088, Shader30_SetCubeMap_Hook);

	ReplaceCall(0x8727DE, Render_Hook);
	ReplaceCall(0x870F46, SetOffScreenRTGroup_Hook);

	if (CubemapRenderer::bOverride)
		ReplaceCall(0xB68DCC, BSShaderProperty_LoadBinary_Hook);

	ReplaceCall(0xB7DC5B, UpdateToggles_Hook);
	
	// Fix water flow speed
	ReplaceCall(0x559450, TESWater::RenderSurface_Hook);

	// Fix water reflection toggles
	ReplaceCall(0x4E2B8D, (UInt32)TESWater::ReflectionFix_Hook);
	ReplaceCall(0x4E28A9, (UInt32)TESWater::ReflectionFix_Hook2);

	// Disables RefID writes into the shader property. Should be safe.
	PatchMemoryNop(0x4B6E0E, 5);

	// Removes the mipmap check for rendered textures
	PatchMemoryNop(0xE7EA9F, 0x21);

	// Replaces cubemap creator with a modified version allowing for mipmaps
	ReplaceCall(0xE901D5, NiDX9RenderedCubeMapData::CreateSurf);
	
	// Replace ShadowLightShader pixel shader create func
	ReplaceCall(0xB78907, BSShader::CreatePixelShader);
}

bool CubemapRenderer::SearchCamera(TESObjectCELL* apCell)
{
	NiNode* pStaticsNode = apCell->GetChildNode(TESObjectCELL::CN_STATIC);
	pCameraNode = static_cast<NiNode*>(pStaticsNode->GetObjectByNameEx("CellCamera"));

	if (pCameraNode) {
#if bDebugLog
		_MESSAGE("[ CubemapRenderer::RenderCubemap ] CellCamera found");
#endif
		return true;
	}

	for (UInt32 i = 0; i < TESObjectCELL::CN_MAX; i++) {
		NiNode* pCellNode = apCell->GetChildNode(static_cast<TESObjectCELL::CELLNODE>(i));
		if (pCellNode) {
			pCameraNode = static_cast<NiNode*>(pCellNode->GetObjectByNameEx("CellCamera"));
			if (pCameraNode) {
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
			pCameraNode = nullptr;
		}
	}

	return false;
}

static float fOrgEnd;
static float fOrgStart;

void CubemapRenderer::UpdateFog(ShadowSceneNode* apScene, float afViewDistance) {
	fOrgEnd = apScene->spFog->fEndDistance;
	fOrgStart = apScene->spFog->fStartDistance;

	apScene->spFog->fEndDistance = afViewDistance * 0.8f;
	apScene->spFog->fStartDistance = afViewDistance * 0.6f;
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
		_MESSAGE("[ CubemapRenderer::RenderCubemap ] Creating player cubemap camera");
		spPlayerCubeCam = BSCubeMapCamera::Create(TESMain::GetWorldRoot(), fPlayerViewDistance, uiPlayerCubemapSize, D3DFMT_A16B16G16R16F);
		spPlayerCubeCam->SetName("Player Reflections");
	}
	return spPlayerCubeCam;
}

BSCubeMapCamera* CubemapRenderer::GetWorldCamera() {
	if (!spWorldCubeCam.m_pObject) {
		_MESSAGE("[ CubemapRenderer::RenderCubemap ] Creating world cubemap camera");
		spWorldCubeCam = BSCubeMapCamera::Create(nullptr, fWorldViewDistance, uiWorldCubemapSize, D3DFMT_A16B16G16R16F);
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

	spPlayerCubeCam->spTexture = BSTextureManager::NewRenderedCubemap(uiPlayerCubemapSize, 0, D3DFMT_A16B16G16R16F, 0);
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

	spWorldCubeCam->spTexture = BSTextureManager::NewRenderedCubemap(uiWorldCubemapSize, 0, D3DFMT_A16B16G16R16F, 0);
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

	if ((!pLastCell || pLastCell != pCurrCell || bCheckCellAgain) && pCurrCell) {
		bCellChanged = true;
		pLastCell = pCurrCell;
		pCameraNode = nullptr;
		spRenderedCubemapWorld = nullptr;
		bCheckCellAgain = false;
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

	bool bUseCellCamera = bInUse_World && pCameraNode;
	SkipMode eShouldSkip = SKIP_NONE;

	if (bScreenSpaceInterior && *BSShaderManager::bIsInInterior)
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


		// Player cubemap
		if (eShouldSkip != SKIP_PLAYER && (bInUse_Player && !bLowQuality || bWorldOverride || bInteriorOverride || bDumpNextFrame)) {

			BSCubeMapCamera* pPlayerCubeCam = GetPlayerCamera();
			BSRenderedTexture* pPlayerTexture = GetPlayerTexture();

			if (!pWeaponNode)
				pWeaponNode = static_cast<NiNode*>(pPlayerNode1->GetObjectByNameEx("Weapon"));

			NiPoint3 weaponPos = pWeaponNode->GetWorldTranslate();
			if (pPlayer->IsWeaponOut() && !*BSShaderManager::bIsInInterior && !bHighQuality)
				pPlayerCubeCam->SetLocalTranslate(bThirdPerson ? &playerPos : &weaponPos);
			else
				pPlayerCubeCam->SetLocalTranslate(&playerPos);

			UInt32 uiUpdateRate = *BSShaderManager::bIsInInterior ? min(uiPlayerUpdateRate + 1, 6) : uiPlayerUpdateRate;
			if (bDumpNextFrame)
				uiUpdateRate = 6;

			pSkyRoot->SetLocalTranslate(pPlayerCubeCam->GetWorldTranslate());
			pSkyRoot->Update(g_defaultUpdateData);

			bRendering = true;

#if bDebugLog
			_MESSAGE("[ CubemapRenderer::RenderCubemap ] Rendering player cubemap");
#endif

			UpdateFog(pShadowSceneNode, CubemapRenderer::fPlayerViewDistance);
			pPlayerCubeCam->RenderCubeMap(0, uiUpdateRate, bDumpNextFrame ? BSCullingProcess::BSCP_CULL_ALLPASS : BSCullingProcess::BSCP_CULL_FORCEMULTIBOUNDSNOUPDATE, true);
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

			if (pCameraNode) {
				pWorldCubeCam->SetLocalTranslate(pCameraNode->GetWorldTranslate());
			}

			kSceneNodes.RemoveAll();

			if (!pCameraNode) {
				// Adjust camera position to use eye height
				playerPos.z += fPlayerEyeHeightOffset;
				pWorldCubeCam->SetLocalTranslate(playerPos);
			}

			BGSTerrainManager* pTerrainManager = TES::GetWorldSpace()->GetTerrainManager();

			// Add nodes to the list to be rendered
			if (pCameraNode) {
				kSceneNodes.AddHead(pSceneGraph);

				// Temporarily move sky to the camera position - it's normally set to player's
				pSkyRoot->SetLocalTranslate(pCameraNode->GetWorldTranslate());
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

			}

			bRendering = true;

#if bDebugLog
			_MESSAGE("[ CubemapRenderer::RenderCubemap ] Rendering world cubemap");
#endif

			UpdateFog(pShadowSceneNode, CubemapRenderer::fWorldViewDistance);
			pWorldCubeCam->RenderCubeMap(&kSceneNodes, uiWorldUpdateRate, BSCullingProcess::BSCP_CULL_FORCEMULTIBOUNDSNOUPDATE, bRenderLandLOD);
			RestoreFog(pShadowSceneNode);

			bRendering = false;

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
	if (bDumpNextFrame) {
		NiDX9Renderer* pRenderer = NiDX9Renderer::GetSingleton();

		D3DSURFACE_DESC desc;
		for (UInt32 uiFace = 0; uiFace < 6; uiFace++) {
			LPDIRECT3DSURFACE9 pNewSurf;
			LPDIRECT3DSURFACE9 surf = reinterpret_cast<NiDX92DBufferData*>(spRenderedCubemapPlayer->GetFaceBuffer(uiFace)->m_spRendererData.m_pObject)->m_pkSurface;
			surf->GetDesc(&desc);
			pRenderer->GetD3DDevice()->CreateOffscreenPlainSurface(desc.Height, desc.Height, desc.Format, D3DPOOL_SYSTEMMEM, &pNewSurf, 0);
			pRenderer->GetD3DDevice()->GetRenderTargetData(surf, pNewSurf);
			D3DXSaveSurfaceToFile(std::format("face_{}.bmp", uiFace).c_str(), D3DXIFF_BMP, pNewSurf, 0, 0);
			pNewSurf->Release();
		}
		bDumpNextFrame = false;
	}
}

const NiTexture* __fastcall CubemapRenderer::SLS_GetCubeMap_Hook(ShadowLightShader* apThis, void*, BSShaderPPLightingProperty* apShaderProp, UInt32 auiTextureNumber) {
	NiTexture* pTexture = apShaderProp->ppTextures[BSTextureSet::BSSM_CubeMap][auiTextureNumber];

	if ((apShaderProp->ulFlags[1] & BSShaderProperty::Wall_RealTimeEnv || bOverride) && !bRendering) {
		// Check if we should use the player cubemap
		if (apShaderProp->uiExtraFlags & 1) {
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
		return BSShaderManager::GetArmorReflectionCubeMap();
	return pTexture;
}

void __fastcall CubemapRenderer::Shader30_SetCubeMap_Hook(void* apThis, void*, NiD3DPass* apPass, BSShaderPPLightingProperty* apShaderProp, RenderPassTypes aeRenderPass) {
	NiTexture* pTexture = nullptr;

	if ((apShaderProp->ulFlags[1] & BSShaderProperty::Wall_RealTimeEnv || bOverride) && !bRendering) {
		// Check if we should use the player cubemap
		if (apShaderProp->uiExtraFlags & 1) {
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

void __fastcall CubemapRenderer::UpdateToggles_Hook(ShadowLightShader* apThis, void*, RenderPassTypes aeRenderPassType, NiGeometry* apGeo, BSShaderPPLightingProperty* apShaderProp, NiMaterialProperty* apMatProp, BSRenderPass* apRenderPass, NiAlphaProperty* apAlphaProp) {
	ThisStdCall(0xB795B0, apThis, aeRenderPassType, apGeo, apShaderProp, apMatProp, apRenderPass, apAlphaProp);



	if (apShaderProp->IsLandscape() || aeRenderPassType >= BSSM_2x_ENVMAP && aeRenderPassType <= BSSM_2x_ENVMAP_EYE) {
		if ((aeRenderPassType - 584) <= 3) {
			if (apShaderProp->HasEnvironmentMap() && (apShaderProp->ulFlags[1] & BSShaderProperty::Wall_RealTimeEnv || bOverride)) {

				bool bIsPlayer = apShaderProp->uiExtraFlags & 1;
				bool bFakeInterior = (*BSShaderManager::bIsInInterior && bScreenSpaceInterior);

				if (bOverrideBrightness) {
					if (bFakeInterior && !spRenderedCubemapWorld.m_pObject || bNoWorldInExteriors || bNoWorldInInteriors) {
						// Make sure we are applying to player's shaders
						if (bIsPlayer) {
							ShadowLightShaderManager::PixelConstants::GetToggles()->fSpecularity = apShaderProp->fEnvMapScale * *BSShaderManager::bIsInInterior ? fInteriorBrightnessMult : fExteriorBrightnessMult;
						}
					}
					else {
						ShadowLightShaderManager::PixelConstants::GetToggles()->fSpecularity = apShaderProp->fEnvMapScale * *BSShaderManager::bIsInInterior ? fInteriorBrightnessMult : fExteriorBrightnessMult;
					}
				}

				NiColorA* pAmbientConstant = ShadowLightShaderManager::PixelConstants::GetAmbientColor();


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
		}
	}
}