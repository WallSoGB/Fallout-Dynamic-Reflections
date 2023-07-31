#pragma once

#include "NiColor.hpp"
#include "Sun.hpp"
#include "Clouds.hpp"
#include "Moon.hpp"
#include "BSSimpleList.hpp"
#include "BSMultiBoundNode.hpp"
#include "Atmosphere.hpp"

class Stars;
class Precipitation;
class TESClimate;
class TESWeather;
class ImageSpaceModifierInstanceForm;

NiSmartPointer(Sky);

class Sky {
public:
	virtual Sky* Destroy(bool doFree);

	enum SkyObjectType {
		SOT_SUNGLARE = 0x1,
		SOT_CLOUDS = 0x3,
		SOT_STARS = 0x5,
		SOT_MOON = 0x7,
	};

	enum SkyColors {
		SC_SKY_UPPER = 0x0,
		SC_FOG = 0x1,
		SC_UNK = 0x2,
		SC_AMBIENT = 0x3,
		SC_SUNLIGHT = 0x4,
		SC_SUN = 0x5,
		SC_STARS = 0x6,
		SC_SKY_LOWER = 0x7,
		SC_HORIZON = 0x8,
		SC_MAX = 0xA,
	};

	struct SkySound {
		UInt32		unk00;		// 00
		UInt32		unk04;		// 04
		UInt32		unk08;		// 08
		TESWeather* weather;	// 0C
		UInt32		type;		// 10
		UInt32		soundID;	// 14
	};

	enum SKY_MODE {
		SM_NONE = 0x0,
		SM_INTERIOR = 0x1,
		SM_SKYDOME_ONLY = 0x2,
		SM_FULL = 0x3,
	};

	struct COLOR_BLEND
	{
		UInt32 uiRGBVal[4];
		float fBlend[4];
	};

	BSMultiBoundNodePtr spRoot;
	NiNodePtr spMoonsRoot;
	TESClimate* pCurrentClimate;
	TESWeather* pCurrentWeather;
	TESWeather* pLastWeather;
	TESWeather* pDefaultWeather;
	TESWeather* pOverrideWeather;
	Atmosphere* pAtmosphere;
	Stars* pStars;
	Sun* pSun;
	Clouds* pClouds;
	Moon* pMasser;
	Moon* pSecunda;
	Precipitation* precipitation;
	NiColor pColors[SC_MAX];
	NiColor pColorUnkown0B4;
	NiColor pColorSunFog;
	float fWindSpeed;
	float fWindAngle;
	float fogNearPlane;
	float fogFarPlane;
	UInt32 unk0DC;
	UInt32 unk0E0;
	UInt32 unk0E4;
	float fFogPower;
	float fCurrentGameHour;
	float fLastWeatherUpdate;
	float fCurrentWeatherPct;
	Sky::SKY_MODE eMode;
	BSSimpleList<SkySound>* pSkySoundList;
	float fFlash;
	UInt32 uiFlashTime;
	UInt32 uiLastMoonPhaseUpdate;
	float fWindowReflectionTimer;
	float fAccelBeginPct;
	UInt32 unk114;
	UInt32 uiFlags;
	ImageSpaceModifierInstanceForm* fadeInIMODCurrent;
	ImageSpaceModifierInstanceForm* fadeOutIMODCurrent;
	ImageSpaceModifierInstanceForm* fadeInIMODLast;
	ImageSpaceModifierInstanceForm* fadeOutIMODLast;
	float f12_0;
	float f23_99;
	float f0_0;

	__forceinline static Sky* GetInstance() { return *(Sky**)0x11DEA20; }

	__forceinline NiColor* GetSunColor() { return &pColors[SC_SUNLIGHT]; }
	__forceinline NiColor* GetAmbientColor() { return &pColors[SC_AMBIENT]; }

	void RefreshMoon();

	bool GetIsRaining();

	static void SetIsUnderwater(bool abIsUnderwater) { *(bool*)0x11FF8C4 = abIsUnderwater; };
	static bool IsUnderwater() { return *(bool*)0x11FF8C4; };
};

ASSERT_SIZE(Sky, 0x138);