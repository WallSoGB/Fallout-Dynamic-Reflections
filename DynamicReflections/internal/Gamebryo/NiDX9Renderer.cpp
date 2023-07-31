#include "NiDX9Renderer.hpp"
#include "NiTriStrips.hpp"
#include "NiTriStripsData.hpp"
#include "NiTriShape.hpp"
#include "NiTriShapeData.hpp"

UInt32 NiDX9Renderer::uiIndexedPrimitiveCount = 0;
UInt32 NiDX9Renderer::uiPrimitiveCount = 0;
UInt32 NiDX9Renderer::uiTotalStripCount = 0;
UInt32 NiDX9Renderer::uiTotalVertCount = 0;
UInt32 NiDX9Renderer::uiTotalTriCount = 0;

NiDX9Renderer* NiDX9Renderer::GetSingleton() {
	return *(NiDX9Renderer**)0x11C73B4;
}
LPDIRECT3D9 NiDX9Renderer::GetD3D9() {
	return *(LPDIRECT3D9*)0x126F0D8;
}

LPDIRECT3DDEVICE9 NiDX9Renderer::GetD3DDevice() {
	return m_pkD3DDevice9;
}

bool NiDX9Renderer::IsFrameStateOutsideFrame() {
	return NiDX9Renderer::GetSingleton()->m_eFrameState == FRAMESTATE_OUTSIDE_FRAME;
}

void NiDX9Renderer::ClearBuffer(const NiRect<float>* pkR, ClearFlags uiMode) {
	if (NiRenderer::Check_RenderTargetGroupActive(true))
		Do_ClearBuffer(pkR, uiMode);
}

UInt32 NiDX9Renderer::GetScreenWidth() {
	NiRenderTargetGroup* pRTGroup = GetDefaultRenderTargetGroup();
	if (pRTGroup) {
		Ni2DBuffer* pBuffer = pRTGroup->GetBuffer(0);
		return pBuffer ? pBuffer->m_uiWidth : 0;
	}
	return 0;
}

UInt32 NiDX9Renderer::GetScreenHeight() {
	NiRenderTargetGroup* pRTGroup = GetDefaultRenderTargetGroup();
	if (pRTGroup) {
		Ni2DBuffer* pBuffer = pRTGroup->GetBuffer(0);
		return pBuffer ? pBuffer->m_uiHeight : 0;
	}
	return 0;
}

bool NiDX9Renderer::BeginUsingRenderTargetGroup(NiRenderTargetGroup* apTarget, NiRenderer::ClearFlags uiClearMode) {
	if (!Check_RenderTargetGroupActive(false))
		return false;

	if (!apTarget) {
		_MESSAGE("[ NiDX9Renderer::BeginUsingRenderTargetGroup ]"
			"Failed - NULL pointer for render target. "
			"Call BeginUsingDefaultRenderTargetGroup if you intended to use the backbuffer instead.");
		return false;
	}

	LockRenderer();

	bool bSuccess = Do_BeginUsingRenderTargetGroup(apTarget, uiClearMode);

	if (bSuccess)
		m_bRenderTargetGroupActive = true;
	else
		UnlockRenderer();

	return bSuccess;
}

// 0xE72C20
bool NiDX9Renderer::IsHardwareSkinned(const NiGeometry* pkGeometry, NiD3DShaderInterface* pkShader) {
	if (pkGeometry->GetModelData()->m_pkBuffData) {
		return false;
	}
	NiSkinInstance* pkSkinInstance = pkGeometry->GetSkinInstance();
	if (!pkSkinInstance) {
		return false;
	}
	NiSkinPartition* pkPartition = pkSkinInstance->GetSkinPartition();
	if (!pkPartition) {
		return false;
	}
	if (pkPartition->m_pkPartitions->m_pkBuffData || (m_uiRendFlags & 2) != 0) {
		return true;
	}
	if (!pkShader) {
		pkShader = reinterpret_cast<NiD3DShaderInterface*>(pkGeometry->GetShader());
	}
	if (!pkShader) {
		return false;
	}
	if (m_uiMaxVertexShaderVersion > 0xFFFE0000 && pkShader && ((NiD3DShaderInterface*)pkShader)->GetVSPresentAllPasses() != 0) {
		return true;
	}

	NiDX9ShaderDeclaration * pkShaderDecl = static_cast<NiDX9ShaderDeclaration*>(reinterpret_cast<NiD3DShader*>(pkShader)->GetShaderDecl());
	if (!m_bSWVertexSwitchable || !pkShaderDecl || !pkShaderDecl->m_bSoftwareVB) {
		return false;
	}
	return true;
}

D3DMULTISAMPLE_TYPE NiDX9Renderer::GetMultiSampleType(UInt32 auiMode) {
	return CdeclCall<D3DMULTISAMPLE_TYPE>(0xB6C200, auiMode);
}

bool __fastcall NiDX9Renderer::IsHardwareSkinnedEx(NiDX9Renderer* apThis, void*, const NiGeometry* pkGeometry, NiD3DShaderInterface* pkShader) {
	return apThis->IsHardwareSkinned(pkGeometry, pkShader);
}

// 0xE6FBB0
void NiDX9Renderer::SetModelTransform(const NiTransform& kXform, bool bPushToDevice) {
#if 1
	ThisStdCall(0xE6FBB0, this, kXform, bPushToDevice);

#else
	NiD3DUtility_GetD3DFromNi(m_kD3DMat, kXform.m_Rotate, kXform.m_Translate, kXform.m_fScale);

	if (bPushToDevice)
		m_pkD3DDevice9->SetTransform(D3DTS_WORLD, &m_kD3DMat);

	m_pkRenderState->SetModelTransform(kXform);

	NiMatrix3 kRotScale = kXform.m_Rotate * kXform.m_fScale;
	m_kModelCamRight = m_kCamRight * kRotScale;
	m_kModelCamUp = m_kCamUp * kRotScale;
#endif
}

void NiDX9Renderer::SetScreenSpaceCameraData(NiRect<float>* pkPort) {
	if (Check_RenderTargetGroupActive(true))
		Do_SetScreenSpaceCameraData(pkPort);
}

void NiDX9Renderer::SetCameraData(NiPoint3* kWorldLoc, NiPoint3* kWorldDir, NiPoint3* kWorldUp, NiPoint3* kWorldRight, NiFrustum* kFrustum, NiRect<float>* kPort) {
	if (Check_RenderTargetGroupActive(true))
		Do_SetCameraData(kWorldLoc, kWorldDir, kWorldUp, kWorldRight, kFrustum, kPort);
}

void __fastcall NiDX9Renderer::Do_RenderTristripsAltEx(NiDX9Renderer* apThis, void*, NiTriStrips* apStrip) {
		NiTriStripsData* pModelData = static_cast<NiTriStripsData*>(apStrip->GetModelData());

		if (apThis->m_bDeviceLost || !pModelData->m_usVertices)
			return;
		
		NiGeometryBufferData* pBuffData = pModelData->m_pkBuffData;
		UInt32 uiStartPrimitiveIndex = 0;
		UInt32 uiTriCount = pBuffData->m_uiTriCount;
		UInt32 uiVertCount = pBuffData->m_uiVertCount;

		uiTotalTriCount += uiTriCount;
		uiTotalVertCount += uiVertCount;
		uiTotalStripCount += pModelData->m_usStrips;

		// Set world bound and shader
		apThis->m_kWorldBound = *apStrip->GetWorldBound();
		reinterpret_cast<NiD3DShader*>(apStrip->GetShader())->FirstPass();

		if (pBuffData->m_pkIB) {
			const UInt16* indexArray = pBuffData->m_pusIndexArray;
			for (UInt32 i = 0; i < pBuffData->m_uiNumArrays; ++i) {
				uiTriCount = indexArray ? indexArray[i] - 2 : uiTriCount;
				apThis->m_pkD3DDevice9->DrawIndexedPrimitive(pBuffData->m_eType, pBuffData->m_uiBaseVertexIndex, 0, uiVertCount, uiStartPrimitiveIndex, uiTriCount);
				uiIndexedPrimitiveCount++;
				uiStartPrimitiveIndex += uiTriCount + 2;
			}
		}
		else {
			apThis->m_pkD3DDevice9->DrawPrimitive(pBuffData->m_eType, pBuffData->m_uiBaseVertexIndex, uiTriCount);
			uiPrimitiveCount++;
		}
		pModelData->m_usDirtyFlags &= 0xF000u;
}

void __fastcall NiDX9Renderer::Do_RenderShapeAltEx(NiDX9Renderer* apThis, void*, NiTriShape* apShape) {
	NiTriShapeData* pModelData = static_cast<NiTriShapeData*>(apShape->GetModelData());

	if (apThis->m_bDeviceLost || !pModelData->m_usVertices)
		return;

	NiGeometryBufferData* pBuffData = pModelData->m_pkBuffData;
	NiSkinInstance* pSkinInstance = apShape->m_spSkinInstance;

	UInt32 uiTriCount = pBuffData->m_uiTriCount;
	UInt32 uiVertCount = pBuffData->m_uiVertCount;
	uiTotalTriCount += uiTriCount;
	uiTotalVertCount += uiVertCount;
#if 1
	ThisStdCall(0xE745A0, apThis, apShape);
#else
	UInt32 uiStartPrimitiveIndex = 0;

	uiTotalTriCount += uiTriCount;
	uiTotalVertCount += uiVertCount;


	bool bHWSkinned = apThis->IsHardwareSkinned(apShape, nullptr);
	apShape->GetShader()->FirstPass();

	if (bHWSkinned) {

	}

	if (pBuffData->m_pkIB) {
		const UInt16* indexArray = pBuffData->m_pusIndexArray;
		for (UInt32 i = 0; i < pBuffData->m_uiNumArrays; ++i) {
			uiTriCount = indexArray ? indexArray[i] - 2 : uiTriCount;
			apThis->m_pkD3DDevice9->DrawIndexedPrimitive(pBuffData->m_eType, pBuffData->m_uiBaseVertexIndex, 0, uiVertCount, uiStartPrimitiveIndex, uiTriCount);
			uiIndexedPrimitiveCount++;
			uiStartPrimitiveIndex += uiTriCount + 2;
		}
	}
	else {
		apThis->m_pkD3DDevice9->DrawPrimitive(pBuffData->m_eType, pBuffData->m_uiBaseVertexIndex, uiTriCount);
		uiPrimitiveCount++;
	}
	pModelData->m_usDirtyFlags &= 0xF000u;
#endif
}