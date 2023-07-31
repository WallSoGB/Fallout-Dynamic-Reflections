#include "TESMain.hpp"
#include "NiDX9Renderer.hpp"

// 0x874B50
void TESMain::SetOffScreenRTGroup(BSRenderedTexture* apTexture, UInt32 auiClearMode) {
	if (NiDX9Renderer::IsFrameStateOutsideFrame())
		apTexture->SetOffScreenRenderTargetGroup(auiClearMode);
}