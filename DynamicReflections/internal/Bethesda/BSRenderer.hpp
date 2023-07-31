#pragma once

#include "BSRenderedTexture.hpp"
#include "NiDX9Renderer.hpp"
#include "ImageSpaceManager.hpp"
#include "BSShaderManager.hpp"

class BSRenderer {
public:
	static __forceinline UInt32 GetFrameBufferMode() { return *(UInt32*)0x11C70CC; }
	static __forceinline bool IsMultisamplingEnabled() { return GetFrameBufferMode() >= 2; }
	static __forceinline bool IsTransparencyMultisamplingEnabled() { return *(bool*)0x11F9421; }
	static __forceinline bool IsSLI() { return *(bool*)0x11F9440; }
	static bool ReleaseUnusedRenderTargetsAndEndUsage();
	static void SetRenderTargetGroup(NiRenderTargetGroup* apTarget);
};