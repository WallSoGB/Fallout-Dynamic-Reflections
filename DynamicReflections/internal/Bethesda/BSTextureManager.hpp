#pragma once

#include "ShadowSceneLight.hpp"
#include "NiDepthStencilBuffer.hpp"
#include "NiTListBase.hpp"
#include "NiDX9Renderer.hpp"

class BSRenderedTexture;

enum RenderTargetTypes {
	BSTM_RT_HDR_DOWNSAMPLE = 0x0,
	BSTM_RT_HDR_DOWNSAMPLE_ANISOINTERMEDIATE = 0x1,
	BSTM_RT_HDR_BLURSWAP = 0x2,
	BSTM_RT_IMAGESPACE_SWAP = 0x3,
	BSTM_RT_MAIN_IMAGESPACE = 0x4,
	BSTM_RT_MAIN_FIRSTPERSON = 0x5,
	BSTM_RT_MAIN_MENUBG = 0x6,
	BSTM_RT_TESWATER_FFT = 0x7,
	BSTM_RT_TESWATER_GREY = 0x8,
	BSTM_RT_TESWATER_REFLECTION = 0x9,
	BSTM_RT_TESWATER_LOD_REFLECTION = 0xA,
	BSTM_RT_TESWATER_REFRACTION = 0xB,
	BSTM_RT_TESWATER_RAIN = 0xC,
	BSTM_RT_TESWATER_SCRAMBLEMAP = 0xD,
	BSTM_RT_TESWATER_IFFT_BUTTERFLYMAP = 0xE,
	BSTM_RT_TESWATER_HIGH_W = 0xF,
	BSTM_RT_TESWATER_HIGH_AMPLITUDE = 0x10,
	BSTM_RT_TESWATER_DEPTH = 0x11,
	BSTM_RT_TESWATER_NOISE_HEIGHTMAP = 0x12,
	BSTM_RT_TESWATER_NOISE_NORMALMAP = 0x13,
	BSTM_RT_TESWATER_DISPLACEMENT = 0x14,
	BSTM_RT_TESWATER_DEBUG_DISPLAY = 0x15,
	BSTM_RT_TESWATER_BLUR = 0x16,
	BSTM_RT_TREES_CANOPYSHADOWMASK = 0x17,
	BSTM_RT_BLURFULL_BUFFER = 0x18,
	BSTM_RT_BLURFULL_SWAP = 0x19,
	BSTM_RT_BLUR20_BUFFER = 0x1A,
	BSTM_RT_GETHIT_BUFFER = 0x1B,
	BSTM_RT_LOCALMAP_FINAL = 0x1C,
	BSTM_RT_LOCALMAP_COLOR = 0x1D,
	BSTM_RT_LOCALMAP_NORMALS = 0x1E,
	BSTM_RT_REFRACTION_NORMALS = 0x1F,
	BSTM_RT_VFOG = 0x20,
	BSTM_RT_SCENE_DEPTH_BUFFER = 0x21,
	BSTM_RT_VFOG_SWAP = 0x22,
	BSTM_RT_VELOCITY = 0x23,
	BSTM_RT_VELOCITY_SWAP = 0x24,
	BSTM_RT_DOF_BLUR = 0x25,
	BSTM_RT_DOF_BLUR_SWAP = 0x26,
	BSTM_RT_DOF_MASK = 0x27,
	BSTM_RT_DEPTH_RADIALBLUR_BLUR = 0x28,
	BSTM_RT_CUBEMAP_CAMERA = 0x29,
	BSTM_RT_SHADOWS_SHADOWMAP = 0x2A,
	BSTM_RT_SHADOWS_SHADOWMAPFRUSTUM = 0x2B,
	BSTM_RT_ENVMAP_WINDOWS = 0x2C,
	BSTM_RT_INTERFACE_RENDEREDMENU = 0x2D,
	BSTM_RT_INTERFACE_RENDEREDMENU_SWAP = 0x2E,
	BSTM_RT_INTERFACE_VATS = 0x2F,
	BSTM_RT_INTERFACE_TEMP = 0x30,
	BSTM_RT_NOISE_BUFFER = 0x31,
	BSTM_RT_DECAL_OCCLUSION = 0x33,
};

enum CreationFlags {
	BSTM_CF_NONE = 0x0,
	BSTM_CF_UNK_1 = 0x1,
	BSTM_CF_UNK_2 = 0x2,
	BSTM_CF_NO_STENCIL = 0x4,
	BSTM_CF_NO_RENDER_TARGET = 0x8,
	BSTM_CF_CUBE_MAP = 0x10,
	BSTM_CF_UNK_20 = 0x20,
	BSTM_CF_USE_MSAA = 0x40,
	BSTM_CF_NO_DEPTH_DISCARD = 0x80,
	BSTM_CF_NO_DEPTH = 0x100,
	BSTM_CF_UNK_200 = 0x200,
	BSTM_CF_UNK_400 = 0x400,
};


struct BSTextureManager {
	enum eTextureType { // Is it the official name for RenderTargetTypes? Name from 0x10232BC
	};

	struct RenderedTextureData {
		NiPointer<BSRenderedTexture> spTexture;
		D3DFORMAT eFormat;
		RenderedTextureData* pNext;
		UInt32 uiFlags;
		bool byte10;
		RenderTargetTypes eRenderTargetType;
	};

	struct TextureLists {
		NiTListBase<BSRenderedTexture*> kShadowMaps;
		NiTListBase<BSRenderedTexture*> kWaterDepthMaps;
		NiTListBase<BSRenderedTexture*> kWaterReflectionMaps;
		NiTListBase<BSRenderedTexture*> kWaterBlurMaps;
		NiTListBase<BSRenderedTexture*> kWaterNoiseMaps;
	};
	

	TextureLists						kFreeTextures;
	TextureLists						kActiveTextures;
	NiTListBase<RenderedTextureData*>	lTextureLists[2]; // These two should be separate, figure out later what's the diff
	NiTListBase<BSRenderedTexture*>		ShadowMapList[2];
	NiDepthStencilBufferPtr				spDepthStencilBuffer;
	NiObject*							pUnk0AC;

	static __forceinline BSTextureManager* GetSingleton() { return *(BSTextureManager**)0x11F91A8; }

	static BSRenderedTexture* NewRenderedTexture(UInt32 uiWidth, UInt32 uiHeight, UInt32 auiFlags, D3DFORMAT eFormat, UInt32 auiMSAA);

	static BSRenderedTexture* NewRenderedCubemap(UInt32 uiSize, UInt32 auiFlags, D3DFORMAT eFormat, UInt32 auiMSAA);
};

ASSERT_SIZE(BSTextureManager, 0xB0);