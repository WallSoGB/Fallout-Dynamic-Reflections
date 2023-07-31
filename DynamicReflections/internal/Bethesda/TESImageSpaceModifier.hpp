#pragma once

#include "NiFloatInterpolator.hpp"
#include "NiColorInterpolator.hpp"
#include "TESForm.hpp"

class TESSound;

class TESImageSpaceModifier : public TESForm {
public:
	struct FloatData
	{
		UInt32 unk00;
		float value;
	};

	struct ColorData
	{
		UInt32 unk00;
		float value[4];
	};

	TESSound* outroSound;
	TESSound* introSound;
	UInt8 animable;
	UInt8 pad021[3];
	float duration;
	UInt32 unk028[49];
	float radialBlurCentreX;
	float radialBlurCentreY;
	UInt32 unk0F4[3];
	UInt8 useTarget;
	UInt8 pad101[3];
	UInt32 unk104;
	UInt32 unk108;
	UInt32 uiNumKeys;
	UInt32 unk110;
	NiFloatInterpolator fltIntrpl1[22][2];
	NiColorInterpolator TintColorInterpl;
	NiColorInterpolator FadeColorInterpl;
	NiFloatInterpolator fltIntrpl2[9];
	FloatData* floatData654[22][2];
	ColorData* colorData704[2];
	FloatData* floatData70C[9];
};

ASSERT_SIZE(TESImageSpaceModifier, 0x730);