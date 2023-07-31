#pragma once

#include "TESForm.hpp"
#include "TESImageSpaceModifiableCountForm.hpp"

class TESWeather : public TESForm {
public:
	TESWeather();
	~TESWeather();

	struct WeatherSound
	{
		UInt32 soundID;
		UInt32 type;
	};

	TESImageSpaceModifiableCountForm pImageSpaceMods;
	TESTexture1024 cloudTexture[4];
	UInt8 cloudSpeed[4];
	UInt32 uiCloudColorData[4][6];
	TESModel model;
	UInt8 ucWeatherData[15];
	float fFogData[6];
	UInt32 uiColorData[10][6];
	BSSimpleList<WeatherSound*> soundList;
	float fHDRInfo[14];
	UInt32 unk238;
	UInt32 unk23C;
	UInt32 unk240;
	UInt32 unk244;
	UInt32 unk248;
	UInt32 unk24C;
	UInt32 unk250;
	UInt32 unk254;
	UInt32 unk258;
	UInt32 unk25C;
	UInt32 unk260;
	UInt32 unk264;
	UInt32 unk268;
	UInt32 unk26C;
	UInt32 unk270;
	UInt32 unk274;
	UInt32 unk278;
	UInt32 unk27C;
	UInt32 unk280;
	UInt32 unk284;
	UInt32 unk288;
	UInt32 unk28C;
	UInt32 unk290;
	UInt32 unk294;
	UInt32 unk298;
	UInt32 unk29C;
	UInt32 unk2A0;
	UInt32 unk2A4;
	UInt32 unk2A8;
	UInt32 unk2AC;
	UInt32 unk2B0;
	UInt32 unk2B4;
	UInt32 unk2B8;
	UInt32 unk2BC;
	UInt32 unk2C0;
	UInt32 unk2C4;
	UInt32 unk2C8;
	UInt32 unk2CC;
	UInt32 unk2D0;
	UInt32 unk2D4;
	UInt32 unk2D8;
	UInt32 unk2DC;
	UInt32 unk2E0;
	UInt32 unk2E4;
	UInt32 unk2E8;
	UInt32 unk2EC;
	UInt32 unk2F0;
	UInt32 unk2F4;
	UInt32 unk2F8;
	UInt32 unk2FC;
	UInt32 unk300;
	UInt32 unk304;
	UInt32 unk308;
	UInt32 unk30C;
	UInt32 unk310;
	UInt32 unk314;
	UInt32 unk318;
	UInt32 unk31C;
	UInt32 unk320;
	UInt32 unk324;
	UInt32 unk328;
	UInt32 unk32C;
	UInt32 unk330;
	UInt32 unk334;
	UInt32 unk338;
	UInt32 unk33C;
	UInt32 unk340;
	UInt32 unk344;
	UInt32 unk348;
	UInt32 unk34C;
	UInt32 unk350;
	UInt32 unk354;
	UInt32 unk358;
	UInt32 unk35C;
	UInt32 unk360;
	UInt32 unk364;
	UInt32 numCloudLayers;
};

ASSERT_SIZE(TESWeather, 0x36C);