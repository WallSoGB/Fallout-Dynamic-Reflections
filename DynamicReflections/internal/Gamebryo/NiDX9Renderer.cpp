#include "NiDX9Renderer.hpp"
#include "NiTriStrips.hpp"
#include "NiTriStripsData.hpp"
#include "NiTriShape.hpp"
#include "NiTriShapeData.hpp"

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

D3DMULTISAMPLE_TYPE NiDX9Renderer::GetMultiSampleType(UInt32 auiMode) {
	return CdeclCall<D3DMULTISAMPLE_TYPE>(0xB6C200, auiMode);
}

// 0xE6FBB0
void NiDX9Renderer::SetModelTransform(const NiTransform& kXform, bool bPushToDevice) {
	ThisStdCall(0xE6FBB0, this, kXform, bPushToDevice);
}

void NiDX9Renderer::SetScreenSpaceCameraData(NiRect<float>* pkPort) {
	if (Check_RenderTargetGroupActive(true))
		Do_SetScreenSpaceCameraData(pkPort);
}

void NiDX9Renderer::SetCameraData(NiPoint3* kWorldLoc, NiPoint3* kWorldDir, NiPoint3* kWorldUp, NiPoint3* kWorldRight, NiFrustum* kFrustum, NiRect<float>* kPort) {
	if (Check_RenderTargetGroupActive(true))
		Do_SetCameraData(kWorldLoc, kWorldDir, kWorldUp, kWorldRight, kFrustum, kPort);
}