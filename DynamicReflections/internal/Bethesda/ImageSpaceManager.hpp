#pragma once

#include "ImageSpaceBaseData.hpp"
#include "ImageSpaceTexture.hpp"

#include "NiTriShape.hpp"
#include "NiViewport.hpp"

class ImageSpaceEffect;
class ImageSpaceEffectParam;

class ImageSpaceManager {
public:
	enum EffectID : UInt32 {
		IS_EFFECT_NONE = 0xFFFFFFFF,
		IS_EFFECT_BLOOM = 0x0,
		IS_EFFECT_HDR = 0x1,
		IS_EFFECT_REFRACTION = 0x2,
		IS_EFFECT_CINEMATIC = 0x3,
		IS_EFFECT_DEPTH_OF_FIELD = 0x4,
		IS_EFFECT_DEPTH_RADIAL_BLUR = 0x5,
		IS_EFFECT_RADIAL_BLUR = 0x6,
		IS_EFFECT_FULLSCREEN_BLUR = 0x7,
		IS_EFFECT_GET_HIT = 0x8,
		IS_EFFECT_SUNBEAMS = 0x9,
		IS_EFFECT_INTERFACE = 0xA,
		IS_EFFECT_VATS_SCAN = 0xB,
		IS_EFFECT_MOTION_BLUR = 0xC,
		IS_EFFECT_VOLUMETRIC_FOG = 0xD,
		IS_EFFECT_MAP = 0xE,
		IS_EFFECT_MENU_BG = 0xF,
		IS_EFFECT_BLUR_3 = 0x10,
		IS_EFFECT_BLUR_5 = 0x11,
		IS_EFFECT_BLUR_7 = 0x12,
		IS_EFFECT_BLUR_9 = 0x13,
		IS_EFFECT_BLUR_11 = 0x14,
		IS_EFFECT_BLUR_13 = 0x15,
		IS_EFFECT_BLUR_15 = 0x16,
		IS_EFFECT_BRIGHTPASS_BLUR_3 = 0x17,
		IS_EFFECT_BRIGHTPASS_BLUR_5 = 0x18,
		IS_EFFECT_BRIGHTPASS_BLUR_7 = 0x19,
		IS_EFFECT_BRIGHTPASS_BLUR_9 = 0x1A,
		IS_EFFECT_BRIGHTPASS_BLUR_11 = 0x1B,
		IS_EFFECT_BRIGHTPASS_BLUR_13 = 0x1C,
		IS_EFFECT_BRIGHTPASS_BLUR_15 = 0x1D,
		IS_EFFECT_TV = 0x1E,
		IS_EFFECT_WATER_FFT = 0x1F,
		IS_EFFECT_WATER_DISPLACEMENT = 0x20,
		IS_EFFECT_NOISE = 0x21,
		IS_SHADER_COPY = 0x22,
		IS_SHADER_COPY_RENDERTARGET1 = 0x23,
		IS_SHADER_RESTORE_EDRAM = 0x24,
		IS_SHADER_NULL = 0x25,
		IS_SHADER_COPY_ALPHA = 0x26,
		IS_SHADER_COPY_STENCIL = 0x27,
		IS_SHADER_COPY_STENCIL_NO_TEXTURE_NO_DEPTH = 0x28,
		IS_SHADER_REFRACTION = 0x29,
		IS_SHADER_VOLUMETRIC_FOG = 0x2A,
		IS_SHADER_BLUR = 0x2B,
		IS_SHADER_DOUBLE_VISION = 0x2C,
		IS_SHADER_ALPHA_MULT = 0x2D,
		IS_SHADER_BLEND = 0x2E,
		IS_SHADER_TEXTURE_MASK = 0x2F,
		IS_SHADER_MAP = 0x30,
		IS_SHADER_MENU_BG = 0x31,
		IS_SHADER_CINEMATIC = 0x32,
		IS_SHADER_DEPTH_OF_FIELD = 0x33,
		IS_SHADER_DEPTH_OF_FIELD_MASK = 0x34,
		IS_SHADER_MOTION_BLUR = 0x35,
		IS_SHADER_RADIAL_BLUR = 0x36,
		IS_SHADER_RADIAL_BLUR_MEDIUM = 0x37,
		IS_SHADER_RADIAL_BLUR_HIGH = 0x38,
		IS_SHADER_SUNBEAMS = 0x39,
		IS_SHADER_HDR_BLEND = 0x3A,
		IS_SHADER_HDR_BLEND_CINEMATIC = 0x3B,
		IS_SHADER_HDR_BLEND_CINEMATIC_ALPHA_MASK = 0x3C,
		IS_SHADER_HDR_BLUR = 0x3D,
		IS_SHADER_BRIGHTPASS_FILTER = 0x3E,
		IS_SHADER_DOWNSAMPLE_16 = 0x3F,
		IS_SHADER_DOWNSAMPLE_9 = 0x40,
		IS_SHADER_DOWNSAMPLE_4 = 0x41,
		IS_SHADER_DOWNSAMPLE_4_LUM_CLAMP = 0x42,
		IS_SHADER_DOWNSAMPLE_4_LIGHT_ADAPT = 0x43,
		IS_SHADER_DOWNSAMPLE_16_LUM_CLAMP = 0x44,
		IS_SHADER_DOWNSAMPLE_16_LIGHT_ADAPT = 0x45,
		IS_SHADER_LIGHT_ADAPT = 0x46,
		IS_SHADER_LUM_CLAMP = 0x47,
		IS_SHADER_SCANLINES_BLEND = 0x48,
		IS_SHADER_SCANLINES_BLEND_1 = 0x49,
		IS_SHADER_VATS_SCAN = 0x4B,
		IS_SHADER_MENU_UNPACK = 0x4C,
		IS_SHADER_TV = 0x4D,
		IS_SHADER_BLUR_3 = 0x4E,
		IS_SHADER_BLUR_5 = 0x4F,
		IS_SHADER_BLUR_7 = 0x50,
		IS_SHADER_BLUR_9 = 0x51,
		IS_SHADER_BLUR_11 = 0x52,
		IS_SHADER_BLUR_13 = 0x53,
		IS_SHADER_BLUR_15 = 0x54,
		IS_SHADER_BRIGHTPASS_BLUR_3 = 0x55,
		IS_SHADER_BRIGHTPASS_BLUR_5 = 0x56,
		IS_SHADER_BRIGHTPASS_BLUR_7 = 0x57,
		IS_SHADER_BRIGHTPASS_BLUR_9 = 0x58,
		IS_SHADER_BRIGHTPASS_BLUR_11 = 0x59,
		IS_SHADER_BRIGHTPASS_BLUR_13 = 0x5A,
		IS_SHADER_BRIGHTPASS_BLUR_15 = 0x5B,
		IS_SHADER_WATER_FFT_WATER_SPECTRUM = 0x5D,
		IS_SHADER_WATER_FFT_HORIZONTAL_BUTTERFLY = 0x5E,
		IS_SHADER_WATER_FFT_VERTICAL_BUTTERFLY = 0x5F,
		IS_SHADER_WATER_FFT_HORIZONTAL_SCRAMBLE = 0x60,
		IS_SHADER_WATER_FFT_VERTICAL_SCRAMBLE = 0x61,
		IS_SHADER_WATER_FFT_NORMALS = 0x62,
		IS_SHADER_WATER_FFT_FILTER = 0x63,
		IS_SHADER_WATER_FFT_DISPLAY_NORMALS = 0x64,
		IS_SHADER_WATER_FFT_DISPLAY_HIGHW = 0x65,
		IS_SHADER_WATER_FFT_DISPLAY_AMPLITUTE = 0x66,
		IS_SHADER_WATER_FFT_WATER_SPECTRUM_1 = 0x67,
		IS_SHADER_WATER_FFT_DISPLAY_WATER_HEIGHT = 0x68,
		kWaterDisplaceClearSimulation = 0x69,
		kWaterDisplaceTexOffset = 0x6A,
		kWaterDisplacementWadingRipple = 0x6B,
		kWaterDisplacementRainRipple = 0x6C,
		kWaterWadingHeightmap = 0x6D,
		kWaterRainHeightmap = 0x6E,
		kWaterBlendHeightmaps = 0x6F,
		kWaterSmoothHeightmap = 0x70,
		kWaterDisplacementNormals = 0x71,
		IS_SHADER_NOISE_SCROLL_AND_BLEND = 0x72,
		IS_SHADER_NOISE_NORMAL_MAP = 0x73,
	};

	BSRenderedTexture* pMainTarget;
	NiTArray<ImageSpaceEffect*> EffectList;
	ImageSpaceBaseData pBaseData;
	ImageSpaceBaseData* pOverRideBaseData;
	ImageSpaceBaseData* activeImageSpaceParams;
	float unk0B4[76];
	bool bIsReady;
	UInt32 iActiveEffectsCount;
	UInt32 iLastEffect;
	NiTriShapePtr spScreenTriShape;
	NiTriShapePtr spScreenTriShapeColors;
	NiTriShapePtr spDynamicScreenTriShape;
	bool bUseDynamicResolution;
	NiTriShapePtr spPartialScreenTriShape;
	ImageSpaceTexture depthTexture;
	NiColorA unk214;
	NiColorA aTintColor;
	float unk234;
	NiColorA unk238;
	NiColorA aFadeColor;
	float unk258;
	float unk25C;
	float fBlurRadius;
	float unk264;
	float fDoubleVisionStrength;
	float fStrength;
	float fRampup;
	float fStart;
	float fRampdown;
	float fDownStart;
	float fRadialBlur280;
	float fRadialBlur284;
	float fRadialBlur288;
	float fRadialBlur28C;
	float fRadialBlur290;
	NiPoint2 aCenter;
	NiPoint2 aRadialBlurCenter;
	float fStrength2;
	float unk2A8;
	float unk2AC;
	float unk2B0;
	float unk2B4;
	float unk2B8;
	float unk2BC;
	float unk2C0;
	UInt32 unk2C4;
	UInt32 unk2C8;
	UInt8 byte2CC;
	UInt8 byte2CD;
	UInt8 gap2CE[2];
	float unk2D0;
	float unk2D4;
	float unk2D8;
	float unk2DC;
	float unk2E0;
	UInt32 unk2E4;
	UInt32 unk2E8;
	UInt32 unk2EC;
	float fMotionBlur;
	float fMotionBlurStrength;
	NiColorA kRefractionTint;
	NiViewport kViewport;
	BSRenderedTexture* pSwapTarget;

	static __forceinline ImageSpaceManager* GetSingleton() {
		return *(ImageSpaceManager**)0x11F91AC;
	}

	ImageSpaceEffect* GetEffect(UInt32 effectID) {
		return EffectList.GetAt(effectID);
	}

	void RenderEffect(ImageSpaceEffect* apEffect, NiDX9Renderer* apRenderer, BSRenderedTexture* apSourceTarget, BSRenderedTexture* apDestTarget, ImageSpaceEffectParam* apParam, bool abEndFrame);
	void RenderEffect(ImageSpaceManager::EffectID aeID, NiDX9Renderer* apRenderer, BSRenderedTexture* apSourceTarget, BSRenderedTexture* apDestTarget, ImageSpaceEffectParam* apParam, bool abEndFrame);
};

ASSERT_SIZE(ImageSpaceManager, 0x31C)