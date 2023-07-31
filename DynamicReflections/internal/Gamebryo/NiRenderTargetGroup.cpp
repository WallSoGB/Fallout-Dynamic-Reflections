#include "NiRenderTargetGroup.hpp"
#include "NiDX9Renderer.hpp"
#include "BSRenderer.hpp"

// 0xB6B7D0
void NiRenderTargetGroup::SetRenderTargetGroup(NiRenderTargetGroup* apTarget, UInt32 uiClearMode) {
#if 0
	CdeclCall(0xB6B7D0, apTarget, uiClearMode);
#else
	NiDX9Renderer* pRenderer = NiDX9Renderer::GetSingleton();
	if (!apTarget)
		apTarget = pRenderer->GetDefaultRenderTargetGroup();
	if (pRenderer->m_bRenderTargetGroupActive)
		pRenderer->EndUsingRenderTargetGroup();
	if (!apTarget)
		apTarget = pRenderer->GetDefaultRenderTargetGroup();
	pRenderer->BeginUsingRenderTargetGroup(apTarget, (NiRenderer::ClearFlags)uiClearMode);
	BSRenderer::SetRenderTargetGroup(apTarget);
#endif
}

void NiRenderTargetGroup::SetOffScreenRenderTargetGroup(NiRenderTargetGroup* apTarget, UInt32 auiClearMode) {
	NiDX9Renderer* pRenderer = NiDX9Renderer::GetSingleton();
	NiRenderer::EFrameState* peFrameState = &pRenderer->m_eFrameState;
	if (*peFrameState == NiRenderer::FRAMESTATE_OUTSIDE_FRAME && pRenderer->Do_BeginFrame()) {
		*peFrameState = NiRenderer::FRAMESTATE_INSIDE_OFFSCREEN_FRAME;
	}
	SetRenderTargetGroup(apTarget, auiClearMode);
}

void NiRenderTargetGroup::SetOnScreenRenderTargetGroup(NiRenderTargetGroup* apTarget, UInt32 auiClearMode) {
	NiDX9Renderer* pRenderer = NiDX9Renderer::GetSingleton();
	NiRenderer::EFrameState* peFrameState = &pRenderer->m_eFrameState;
	if (*peFrameState == NiRenderer::FRAMESTATE_OUTSIDE_FRAME && pRenderer->Do_BeginFrame()) {
		*peFrameState = NiRenderer::FRAMESTATE_INSIDE_FRAME;
	}
	SetRenderTargetGroup(apTarget, auiClearMode);
}