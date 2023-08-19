#include "BSCubeMapCamera.hpp"
#include "BSCullingProcess.hpp"
#include "BSShaderAccumulator.hpp"
#include "BSShaderManager.hpp"
#include "BSShaderUtil.hpp"
#include "NiMemory.hpp"
#include "BSFadeNode.hpp"
#include "TESMain.hpp"
#include "CubemapRender.hpp"
#include "BSTextureManager.hpp"
#include <MTRenderingSystem.hpp>
#include <CubemapRender.hpp>
#include <TESWater.hpp>
#include <GameSettings.h>

BSCubeMapCamera* BSCubeMapCamera::CreateObject() {
	BSCubeMapCamera* pCamera = (BSCubeMapCamera*)NiNew(sizeof(BSCubeMapCamera));
	if (pCamera) {
		return ThisStdCall<BSCubeMapCamera*>(0xBD8290, pCamera, 0);
	}
	return nullptr;
}

BSCubeMapCamera* BSCubeMapCamera::Create(NiNode* apSceneNonde, float afViewDistance, UInt32 auiTextureSize, D3DFORMAT aeFormat) {
	BSCubeMapCamera* pCamera = BSCubeMapCamera::CreateObject();
	if (pCamera) {
		pCamera->pSceneNode = apSceneNonde;
		pCamera->spAccumulator->pActiveShadowSceneNode = BSShaderManager::GetShadowSceneNode(BSSM_SSN_WORLD);
		pCamera->m_kViewFrustum.m_fFar = afViewDistance;
		pCamera->m_kViewFrustum.m_fNear = 5.0f;
		pCamera->IncRefCount();

		if (auiTextureSize && aeFormat)
			pCamera->spTexture = BSTextureManager::NewRenderedCubemap(auiTextureSize, 0, aeFormat, 0);
		
		return pCamera;
	}
	return nullptr;
}

void BSCubeMapCamera::SetupTransformation(UInt32 auiFace) {
#if 0
	ThisStdCall(0xBD7200, this, auiFace);
#else
	NiMatrix3* kMat = &m_kLocal.m_Rotate;
	switch (auiFace) {
	case NiRenderedCubeMap::FACE_POS_X: // Red | East
		kMat->SetRow(0, 1.0f, 0.0f, 0.0f);
		kMat->SetRow(1, 0.0f, 1.0f, 0.0f);
		kMat->SetRow(2, 0.0f, 0.0f, 1.0f);
		break;
	case NiRenderedCubeMap::FACE_NEG_X: // Green | West
		kMat->SetRow(0, -1.0f, 0.0f, 0.0f);
		kMat->SetRow(1, 0.0f, 1.0f, 0.0f);
		kMat->SetRow(2, 0.0f, 0.0f, -1.0f);
		break;
	case NiRenderedCubeMap::FACE_POS_Y: // Blue | North
		kMat->SetRow(0, 0.0f, 0.0f, -1.0f);
		kMat->SetRow(1, 1.0f, 0.0f, 0.0f);
		kMat->SetRow(2, 0.0f, -1.0f, 0.0f);
		break;
	case NiRenderedCubeMap::FACE_NEG_Y: // Yellow | South
		kMat->SetRow(0, 0.0f, 0.0f, -1.0f);
		kMat->SetRow(1, -1.0f, 0.0f, 0.0f);
		kMat->SetRow(2, 0.0f, 1.0f, 0.0f);
		break;
	case NiRenderedCubeMap::FACE_POS_Z: // Cyan | Top
		kMat->SetRow(0, 0.0f, 0.0f, -1.0f);
		kMat->SetRow(1, 0.0f, 1.0f, 0.0f);
		kMat->SetRow(2, 1.0f, 0.0f, 0.0f);
		break;
	case NiRenderedCubeMap::FACE_NEG_Z: // Magenta | Bottom
		kMat->SetRow(0, 0.0f, 0.0f, 1.0f);
		kMat->SetRow(1, 0.0f, 1.0f, 0.0f);
		kMat->SetRow(2, -1.0f, 0.0f, 0.0f);
		break;
	case NiRenderedCubeMap::FACE_NUM:
		break;
	}
#endif
}

void BSCubeMapCamera::RenderCubeMap(NiTPointerListBase<NiAVObject*>* apNodeList, UInt32 auiMaxUpdates, UInt32 auiCullMode, bool abRenderWater) {
	NiDX9Renderer* pRenderer = BSShaderManager::GetRenderer();
	NiColorA orgColor;
	pRenderer->GetBackgroundColor(&orgColor);
	pRenderer->SetBackgroundColor(&Sky::GetInstance()->pColors[Sky::SC_SKY_LOWER]);

	bool bUseReflectionsOrg = false;
	bool bUseDepthOrg = false;
	bool bUseRefractionsOrg = false;

	if (abRenderWater) {
		bUseRefractionsOrg = *eRendererSettingCollection::Water_bUseWaterRefractions;
		bUseReflectionsOrg = *eRendererSettingCollection::Water_bUseWaterReflections;
		bUseDepthOrg = *eRendererSettingCollection::Water_bUseWaterDepth;
		*eRendererSettingCollection::Water_bUseWaterRefractions = false;
		*eRendererSettingCollection::Water_bUseWaterReflections = false;
		*eRendererSettingCollection::Water_bUseWaterDepth = false;
	}

	BSFadeNode::SetFadeEnabled(false);
	TESWater::GetWadeRoot()->SetAppCulled(true);

	for (UInt32 aeFace = 0; aeFace < auiMaxUpdates; aeFace++) {
		if (uiLastUpdatedCamera > 5) {
			uiLastUpdatedCamera = 0;
		}
		SetupTransformation(uiLastUpdatedCamera);
		Update(g_defaultUpdateData);

		NiRenderedCubeMap* pRenderedCubeMap = static_cast<NiRenderedCubeMap*>(spTexture->GetTexture(0));
		NiRenderTargetGroup* pRTGroup = spTexture->spRenderTargetGroups[uiLastUpdatedCamera];
		pRenderedCubeMap->m_aspFaceBuffers[uiLastUpdatedCamera] = pRTGroup->GetBuffer(0);
		pRenderedCubeMap->SetCurrentCubeFace(uiLastUpdatedCamera);

		if (abRenderWater) {
			*TESWater::bPauseTime = true;
			TES::GetSingleton()->pWaterManager->UpdateLOD(this, false);
			TES::GetSingleton()->pWaterManager->RenderWater(this, false);
			TESWater::SetCanReflectAtCustomLvl(false);
			TESWater::SetCanReflectAtWaterLvl(false);
			*TESWater::bPauseTime = false;
		}

		bool bIsFrameEmpty = NiDX9Renderer::IsFrameStateOutsideFrame();
		if (bIsFrameEmpty)
			NiRenderTargetGroup::SetOffScreenRenderTargetGroup(pRTGroup, NiRenderer::CLEAR_ALL);
		else
			NiRenderTargetGroup::SetRenderTargetGroup(pRTGroup, NiRenderer::CLEAR_ALL);

		// Swap to mirror the reflection 
		pRenderer->SetLeftRightSwap(true);

		MTRenderManager::AddTask(this, nullptr, pSceneNode, apNodeList, nullptr, spAccumulator, nullptr, auiCullMode);


		BSShaderUtil::RenderScene(this, spAccumulator);
		pRenderer->SetLeftRightSwap(false);

		if (bIsFrameEmpty)
			NiRenderer::EndOffScreenFrame();
		else
			BSRenderedTexture::SwitchRTGroups();

		uiLastUpdatedCamera++;
	}
	BSFadeNode::SetFadeEnabled(true);
	TESWater::GetWadeRoot()->SetAppCulled(false);

	if (abRenderWater) {
		*eRendererSettingCollection::Water_bUseWaterRefractions = bUseRefractionsOrg;
		*eRendererSettingCollection::Water_bUseWaterReflections = bUseReflectionsOrg;
		*eRendererSettingCollection::Water_bUseWaterDepth = bUseDepthOrg;
	}
	pRenderer->SetBackgroundColorAlpha(&orgColor);
}