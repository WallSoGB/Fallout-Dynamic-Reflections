#include "NiRenderer.hpp"
#include "BSRenderer.hpp"

void NiRenderer::LockRenderer() {
	EnterCriticalSection(&m_kRendererLock.m_kCriticalSection);
}

void NiRenderer::UnlockRenderer() {
	LeaveCriticalSection(&m_kRendererLock.m_kCriticalSection);
}

bool NiRenderer::EndOffScreenFrame() {
	return StdCall<bool>(0xB6B790);
}

void NiRenderer::DisplayFrame() {
	NiDX9Renderer* pRenderer = NiDX9Renderer::GetSingleton();
	BSRenderer::ReleaseUnusedRenderTargetsAndEndUsage();
	if (pRenderer->m_eFrameState == FRAMESTATE_INSIDE_FRAME && pRenderer->Do_EndFrame())
		pRenderer->m_eFrameState = FRAMESTATE_WAITING_FOR_DISPLAY;

	if (pRenderer->m_eFrameState == FRAMESTATE_WAITING_FOR_DISPLAY && pRenderer->Do_DisplayFrame()) {
		++pRenderer->m_uiFrameID;
		pRenderer->m_eFrameState = FRAMESTATE_OUTSIDE_FRAME;
	}

}
