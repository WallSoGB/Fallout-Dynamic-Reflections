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
bool CubemapRenderer::bEnabled;
bool CubemapRenderer::bOverride;
bool CubemapRenderer::bOverrideBrightness;
bool CubemapRenderer::bHighQuality;
bool CubemapRenderer::bLowQuality;
bool CubemapRenderer::bRenderObjectLOD;
bool CubemapRenderer::bRenderLandLOD;
bool CubemapRenderer::bIsInterior = false;

static NiTPointerListBase<NiAVObject*> kSceneNodes;

static bool bInUse_Player = false;
static bool bInUse_World = false;
static NiNode* pWeaponNode = nullptr;
static NiNode* pCameraNode = nullptr;
static TESObjectCELL* pLastCell = nullptr;

#define bDumpNextFrame *(bool*)0x11F5AF1

static UInt32 uiFrameCount = 0;

static BSRenderedTexturePtr spScreenCrop = nullptr;

static const float fWeaponHeightOffset = 107.0f;
static const float fPlayerEyeHeightOffset = 43.0f;

void SetCubemapFlag(NiNode* pObject) {
	UInt32 uiChildCount = pObject->m_kChildren.GetSize();
	if (!uiChildCount)
		return;

	for (UInt32 i = 0; i < uiChildCount; i++) {
		NiAVObject* pChild = pObject->m_kChildren.Get(i);
		BSShaderPPLightingProperty* pShadeProp = nullptr;
		if (pChild) [[likely]] {
			if (pChild->m_kPropertyList.m_uiCount && pChild->IsGeometry()) {
				pShadeProp = static_cast<BSShaderPPLightingProperty*>(pChild->GetProperty(NiProperty::SHADE));
				
				// Mark shader property as player's
				if (pShadeProp && (pShadeProp->uiFlags & 1) == 0 && pShadeProp->m_eShaderType == NiShadeProperty::kType_PPLighting && pShadeProp->HasEnvironmentMap()) {
					pShadeProp->uiFlags |= 1;
				}
			}

			if (pChild->IsNiNode()) {
				SetCubemapFlag(static_cast<NiNode*>(pChild));
			}
		}
	}
}

void CubemapRenderer::InitHooks() {
	if (uiPlayerCubemapSize % 2 != 0) {
		uiPlayerCubemapSize = 256;
	}
	if (uiWorldCubemapSize % 2 != 0) {
		uiWorldCubemapSize = 256;
	}
	uiPlayerUpdateRate = max(0, min(uiPlayerUpdateRate, 6));
	uiWorldUpdateRate = max(0, min(uiWorldUpdateRate, 6));

	ReplaceCall(0xB7C2AA, GetTexture_Hook);

	ReplaceCall(0x870C29, Render_Hook);
	ReplaceCall(0x870F46, SetOffScreenRTGroup_Hook);
	if (CubemapRenderer::bOverride)
		ReplaceCall(0xB68DCC, BSShaderProperty_LoadBinary_Hook);

	if (CubemapRenderer::bOverrideBrightness)
		ReplaceCall(0xB7DC5B, UpdateToggles_Hook);
	
	// Fix water flow speed
	ReplaceCall(0x559450, TESWater::RenderSurface_Hook);

	// Fix water reflection toggles
	ReplaceCall(0x4E2B8D, (UInt32)TESWater::ReflectionFix_Hook);
	ReplaceCall(0x4E28A9, (UInt32)TESWater::ReflectionFix_Hook2);
}

static float fOrgEnd;
static float fOrgStart;

void CubemapRenderer::UpdateFog(ShadowSceneNode* apScene, float afViewDistance) {
	fOrgEnd = apScene->spFog->fEndDistance;
	fOrgStart = apScene->spFog->fStartDistance;

	float fNewEnd = afViewDistance * 0.9f;
	float fNewStart = afViewDistance * 0.8f;

	if (fNewEnd < fOrgEnd)
		apScene->spFog->fEndDistance = fNewEnd;

	if (fNewStart < fOrgStart)
		apScene->spFog->fStartDistance = fNewStart;
}

void CubemapRenderer::RestoreFog(ShadowSceneNode* apScene) {
	apScene->spFog->fEndDistance = fOrgEnd;
	apScene->spFog->fStartDistance = fOrgStart;
}

void CubemapRenderer::RenderCubemap() {
	if (!bEnabled)
		return;

	NiDX9Renderer* pRenderer = NiDX9Renderer::GetSingleton();
	PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
	TESObjectCELL* pCurrCell = pPlayer->GetParentCell();

	if (pCurrCell)
		bIsInterior = pCurrCell->IsInterior();

	bool bCellChanged = false;
	bool bThirdPerson = pPlayer->IsThirdPerson();

	if (!pLastCell || pLastCell != pCurrCell) {
		if (pCurrCell) {
			pCameraNode = nullptr;
			bCellChanged = true;
			pLastCell = pCurrCell;
			spRenderedCubemapWorld = nullptr;
		}
	}

	kSceneNodes.RemoveAll();

	if (uiFrameCount > 15) {
		if (bOverride)
			SetCubemapFlag(PlayerCharacter::GetSingleton()->Get3D());

		uiFrameCount = 0;
	}
	if (bCellChanged) {
		if (TES::IsCellLoaded(pCurrCell, true)) {
			NiNode* pStaticsNode = pCurrCell->GetChildNode(TESObjectCELL::CN_STATIC);
			pCameraNode = static_cast<NiNode*>(pStaticsNode->GetObjectByNameEx("CellCamera"));
			if (!pCameraNode) {
				for (UInt32 i = 0; i < TESObjectCELL::CN_MAX; i++) {
					NiNode* pStaticsNode = pCurrCell->GetChildNode(static_cast<TESObjectCELL::CELLNODE>(i));
					if (pStaticsNode) {
						pCameraNode = static_cast<NiNode*>(pStaticsNode->GetObjectByNameEx("CellCamera"));
						if (pCameraNode) {
							break;
						}
					}
					else {
						pCameraNode = nullptr;
					}
				}
			}
		}
	}

	bool bUseCellCamera = bInUse_World && pCameraNode;
	SkipMode eShouldSkip = SKIP_NONE;

	if (bScreenSpaceInterior && bIsInterior)
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
		ShadowSceneNode* pShadowSceneNode = BSShaderManager::GetShadowSceneNode(BSSM_SSN_WORLD);

		NiNode* pPlayerNode1 = pPlayer->GetNode(true);
		NiNode* pPlayerNode2 = pPlayer->GetNode(false);
		NiPoint3 playerPos = pPlayerNode1->GetWorldTranslate();


		// Adjust camera position average weapon height
		playerPos.z += fWeaponHeightOffset;

		bool bLightProcessing = pShadowSceneNode->bDisableLightUpdate;
		pShadowSceneNode->bDisableLightUpdate = true;

		bool bWorldOverride = bInUse_World && bHighQuality;
		bool bInteriorOverride = bInUse_World && bIsInterior;
		bool bLQInteriorOverride = bIsInterior && bLowQuality;

		// Check player's visibility
		bool bPlayerVisible1 = pPlayerNode1->GetAppCulled();
		bool bPlayerVisible2 = pPlayerNode2->GetAppCulled();

		// Cull player before rendering
		pPlayerNode1->SetAppCulled(true);
		pPlayerNode2->SetAppCulled(true);


		// Player cubemap
		if (eShouldSkip != SKIP_PLAYER && (bInUse_Player && !bLowQuality || bWorldOverride || bInteriorOverride || bDumpNextFrame)) {
			if (!spPlayerCubeCam.m_pObject) {
				_MESSAGE("[ CubemapRenderer::RenderCubemap ] Creating player cubemap");
				spPlayerCubeCam = BSCubeMapCamera::Create(pSceneGraph, CubemapRenderer::fPlayerViewDistance, uiPlayerCubemapSize, D3DFMT_A16B16G16R16F);
				spPlayerCubeCam->SetName("Player Reflections");
			}

			BSCubeMapCamera* pPlayerCubeCam = spPlayerCubeCam;

			if (!pWeaponNode)
				pWeaponNode = static_cast<NiNode*>(pPlayerNode1->GetObjectByNameEx("Weapon"));

			NiPoint3 weaponPos = pWeaponNode->GetWorldTranslate();
			if (pPlayer->IsWeaponOut() && !bIsInterior && !bHighQuality)
				pPlayerCubeCam->SetLocalTranslate(bThirdPerson ? &playerPos : &weaponPos);
			else
				pPlayerCubeCam->SetLocalTranslate(&playerPos);

			UInt32 uiUpdateRate = bIsInterior ? min(uiPlayerUpdateRate + 1, 6) : uiPlayerUpdateRate;
			if (bDumpNextFrame)
				uiUpdateRate = 6;

			UpdateFog(pShadowSceneNode, CubemapRenderer::fPlayerViewDistance);
			pPlayerCubeCam->RenderCubeMap(0, uiUpdateRate, bDumpNextFrame ? BSCullingProcess::BSCP_CULL_ALLPASS : BSCullingProcess::BSCP_CULL_FORCEMULTIBOUNDSNOUPDATE, true);
			RestoreFog(pShadowSceneNode);

			// Setting player cube map
			spRenderedCubemapPlayer = static_cast<NiRenderedCubeMap*>(pPlayerCubeCam->spTexture->spRenderedTextures[0].m_pObject);

			if (bInUse_World && (bHighQuality || bIsInterior)) {
				spRenderedCubemapWorld = spRenderedCubemapPlayer;
			}
			else {
				spRenderedCubemapWorld = nullptr;
			}
		}

		// Restore player visibility
		pPlayerNode1->SetAppCulled(bPlayerVisible1);
		pPlayerNode2->SetAppCulled(bPlayerVisible2);

		// World cubemap
		if (!bUseCellCamera && (bNoWorldInInteriors && bIsInterior || bNoWorldInExteriors)) {
			spRenderedCubemapWorld = nullptr;
		}
		else {
			if (bUseCellCamera || (!bHighQuality && (bInUse_World || bLowQuality))) {
				if (!spWorldCubeCam.m_pObject) {
					_MESSAGE("[ CubemapRenderer::RenderCubemap ] Creating world cubemap");
					spWorldCubeCam = BSCubeMapCamera::Create(nullptr, CubemapRenderer::fWorldViewDistance, uiWorldCubemapSize, D3DFMT_A16B16G16R16F);
					spWorldCubeCam->SetName("World Reflections");
				}

				BSCubeMapCamera* pWorldCubeCam = spWorldCubeCam;

				if (pCameraNode) {
					pWorldCubeCam->SetLocalTranslate(pCameraNode->GetWorldTranslate());
				}

				if (bUseCellCamera || (!bIsInterior && !bHighQuality)) {
					if (!pCameraNode) {
						// Adjust camera position to use eye height
						playerPos.z += fPlayerEyeHeightOffset;
						pWorldCubeCam->SetLocalTranslate(playerPos);
					}

					NiNode* pSkyRoot = TESMain::GetSkyRoot();
					NiPoint3 skyPos = pSkyRoot->GetWorldTranslate();
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

					UpdateFog(pShadowSceneNode, CubemapRenderer::fWorldViewDistance);
					pWorldCubeCam->RenderCubeMap(&kSceneNodes, uiWorldUpdateRate, BSCullingProcess::BSCP_CULL_FORCEMULTIBOUNDSNOUPDATE, bRenderLandLOD);
					RestoreFog(pShadowSceneNode);

					// Restore original sky position
					pSkyRoot->SetLocalTranslate(skyPos);
					pSkyRoot->Update(g_defaultUpdateData);

					spRenderedCubemapWorld = static_cast<NiRenderedCubeMap*>(pWorldCubeCam->spTexture->spRenderedTextures[0].m_pObject);

					if (bLowQuality) {
						spRenderedCubemapPlayer = spRenderedCubemapWorld;
					}
				}
			}
		}


		// Set eye reflection cubemap
		BSShaderManager::SetEyeReflectionCubeMap(spRenderedCubemapPlayer);

		// Restore original player visibility, again
		pPlayerNode1->SetAppCulled(bPlayerVisible1);
		pPlayerNode2->SetAppCulled(bPlayerVisible2);

		pShadowSceneNode->bDisableLightUpdate = bLightProcessing;
	}

	if (bDumpNextFrame) {
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

	bInUse_World = false;
	if (eShouldSkip == SKIP_NONE)
		bInUse_Player = false;
	uiFrameCount++;
}

// oh god oh god it's so wrong
void CubemapRenderer::RenderSceenSpaceCubemap() {
	if (!bEnabled || !bScreenSpaceInterior)
		return;

	PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();

	if (bIsInterior && bInUse_Player && !pPlayer->bThirdPerson) {
		BSRenderedTexture* apTexture = TESMain::GetMainISTexture();
		NiDX9Renderer* pRenderer = NiDX9Renderer::GetSingleton();

		static bool bResSet = false;
		static NiRect<UInt32> rect;
		static NiRect<UInt32> rect2;

		// Get source buffer
		Ni2DBuffer* pSourceBuffer = apTexture->GetTexture(0)->GetBuffer();

		if (!bResSet) {
			UInt32 uiFullHeight = pSourceBuffer->GetHeight();
			UInt32 uiFullWidth = pSourceBuffer->GetWidth();

			UInt32 uiCubeSize = uiScreenSpaceCubemapSize;

			// Create the texture that will be used
			if (!spScreenCrop.m_pObject) {
				_MESSAGE("[ CubemapRenderer::RenderSceenSpaceCubemap ] Creating a crop texture %i x %i", uiCubeSize, uiCubeSize);
				spScreenCrop = BSTextureManager::NewRenderedTexture(uiCubeSize, uiCubeSize, BSTM_CF_NO_DEPTH | BSTM_CF_NO_STENCIL, D3DFMT_A16B16G16R16F, 0);
				spScreenCrop->IncRefCount();
			}

			if (!spFakeCubemap.m_pObject) {
				_MESSAGE("[ CubemapRenderer::RenderSceenSpaceCubemap ] Creating a fake cubemap texture %i x %i", uiCubeSize, uiCubeSize);
				spFakeCubemap = BSTextureManager::NewRenderedCubemap(uiCubeSize, BSTM_CF_NO_DEPTH | BSTM_CF_NO_STENCIL, D3DFMT_A16B16G16R16F, 0);
				spFakeCubemap->IncRefCount();
			}

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
		spRenderedCubemapWorld = nullptr;
		BSShaderManager::SetEyeReflectionCubeMap(pSourceEyeCubeMap);
		bInUse_Player = false;
	}
}

const NiTexture* __fastcall CubemapRenderer::GetTexture_Hook(ShadowLightShader* apThis, void*, BSShaderPPLightingProperty* apShaderProp, UInt32 auiTextureNumber) {
	if (apShaderProp->ulFlags[1] & BSShaderProperty::Wall_RealTimeEnv || bOverride) {
		// Check if we should use the player cubemap
		if (apShaderProp->uiFlags & 1) {
			bInUse_Player = true;
			if (spRenderedCubemapPlayer.m_pObject)
				return spRenderedCubemapPlayer;
		}
		else {
			bInUse_World = true;
			if (spRenderedCubemapWorld.m_pObject)
				return spRenderedCubemapWorld;
		}
	}
	NiTexture* pTexture = apShaderProp->ppTextures[BSTextureSet::BSSM_CubeMap][auiTextureNumber];
	if(!pTexture)
		return BSShaderManager::GetArmorReflectionCubeMap();
	return pTexture;
}

void __fastcall CubemapRenderer::BSShaderProperty_LoadBinary_Hook(BSShaderProperty* apThis, void*, DWORD* kStream) {
	ThisStdCall(0xBA92C0, apThis, kStream);
	if (apThis->HasEnvironmentMap()) {
		apThis->ulFlags[0] &= ~BSShaderProperty::Window_Environment_Mapping;
		apThis->ulFlags[1] &= ~BSShaderProperty::Envmap_Light_Fade;
		apThis->ulFlags[1] &= ~BSShaderProperty::Billboard_and_Envmap_Light_Fade;
	}
}

const void __fastcall CubemapRenderer::Render_Hook(TESMain* apThis) {
	RenderCubemap();
	ThisStdCall(0x8727D0, apThis);
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
				if (bIsInterior && bScreenSpaceInterior && !spRenderedCubemapWorld.m_pObject || bNoWorldInExteriors || bNoWorldInInteriors) {
					// Make sure we are applying to player's shaders
					if (apShaderProp->uiFlags & 1) {
						ShadowLightShaderManager::PixelConstants::GetToggles()->fSpecularity = apShaderProp->fEnvMapScale * bIsInterior ? fInteriorBrightnessMult : fExteriorBrightnessMult;
					}
				}
				else {
					ShadowLightShaderManager::PixelConstants::GetToggles()->fSpecularity = apShaderProp->fEnvMapScale * bIsInterior ? fInteriorBrightnessMult : fExteriorBrightnessMult;
				}
			}
		}
	}
}