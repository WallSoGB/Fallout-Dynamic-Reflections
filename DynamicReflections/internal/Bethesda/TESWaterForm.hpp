#pragma once

#include "TESForm.hpp"
#include "TESAttackDamageForm.hpp"
#include "NiColor.hpp"
#include "TESTexture.hpp"
#include "NiSourceTexture.hpp"
#include "BSRenderedTexture.hpp"
#include "NiPoint3.hpp"

class TESSound;
class SpellItem;
class BGSPlaceableWater;

struct WaterShaderData {
	float float0;
	float float4;
	float float8;
	float floatC;
	float fSunSpecularPower;
	float float14;
	float fFresnelAmount;
	float float1C;
	float fFogNear;
	float fFogFar;
	DWORD dword28;
	DWORD dword2C;
	DWORD ReflectionWaterColor;
	float float34;
	float float38;
	float float3C;
	float float40;
	float float44;
	float float48;
	float fDisplacementForce;
	float fDisplacementVelocity;
	float fDisplacementFalloff;
	float fDisplacementDampener;
	float fDisplacementSize;
	float float60;
	float float64;
	float float68;
	float float6C;
	float float70;
	float float74;
	float float78;
	float depthX;
	float depthY;
	float float84;
	float float88;
	float float8C;
	float float90;
	float float94;
	float float98;
	float float9C;
	float floatA0;
	float floatA4;
	float floatA8;
	float floatAC;
	float floatB0;
	float floatB4;
};

ASSERT_SIZE(WaterShaderData, 0xB8);

class TESWaterForm : public TESForm, TESFullName {
public:
	TESWaterForm();
	~TESWaterForm();

	TESAttackDamageForm attackDamage;
	bool bNeedUpdate;
	UInt8 pad2D[3];
	BSRenderedTexturePtr spNormalNoiseTexture;
	NiColorA fTexScroll0;
	NiColorA fTexScroll1;
	NiColorA fTexScroll2;
	TESTexture NoiseTexture;
	char cAlpha;
	char cFlags;
	UInt8 unk072[2];
	UInt32 unk074;
	UInt32 unk078;
	TESSound* pWaterSound;
	TESWaterForm* waterForm;
	WaterShaderData Data;
	NiPoint3 kAmplitude;
	TESWaterForm* pWaterWeatherControl[3];
	int iCurrentTextureSelect01;
	int iCurrentTextureSelect02;
	UInt32 fFrequencyX;
	UInt32 fFrequencyY;
	int iOctaves;
	float fAmplitude;
	float fLacunarity;
	float fBias;
	float fGain;
	SpellItem* pConsumeSpell;
	NiSourceTexturePtr spNoiseTexture;
	BGSPlaceableWater* PlaceableAutoWater;
	BGSPlaceableWater* pPlaceableAutoWater;
	UInt8 radiation;
	UInt32 unk18C;
	bool bResetNoiseTextures;

	const char* GetNoiseTextureName();
	UInt32 GetNoiseTextureNameLength();
};

ASSERT_SIZE(TESWaterForm, 0x194);