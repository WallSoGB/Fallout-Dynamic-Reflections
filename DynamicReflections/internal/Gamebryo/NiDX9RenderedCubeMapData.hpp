#pragma once

#include "NiDX9RenderedTextureData.hpp"
#include "NiRenderedCubeMap.hpp"

class NiDX9RenderedCubeMapData : public NiDX9RenderedTextureData {
public:
	static NiPixelFormat* __fastcall CreateSurf(NiDX9RenderedCubeMapData* apThis, void*, NiRenderedCubeMap* apTexture);
};