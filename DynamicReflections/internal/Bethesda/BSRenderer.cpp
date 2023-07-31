#include "BSRenderer.hpp"
#include "NiDX9Renderer.hpp"

// 0xB6B6C0
bool BSRenderer::ReleaseUnusedRenderTargetsAndEndUsage() {
	return CdeclCall<bool>(0xB6B6C0);
}

// 0xB6B050
void BSRenderer::SetRenderTargetGroup(NiRenderTargetGroup* apTarget) {
	CdeclCall(0xB6B050, apTarget);
}