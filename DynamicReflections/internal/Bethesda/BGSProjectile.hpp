#pragma once

#include "TESBoundObject.hpp"
#include "TESModel.hpp"
#include "BGSPreloadable.hpp"
#include "BGSDestructibleObjectForm.hpp"

class TESObjectLIGH;
class TESSound;
class TESObjectWEAP;

class BGSProjectile : public TESBoundObject {
public:
	BGSProjectile();
	~BGSProjectile();

	enum
	{
		kFlags_Hitscan = 1 << 0,
		kFlags_Explosion = 1 << 1,
		kFlags_AltTrigger = 1 << 2,
		kFlags_MuzzleFlash = 1 << 3,
		//				1 << 4,
		kFlags_CanBeDisabled = 1 << 5,
		kFlags_CanBePicked = 1 << 6,
		kFlags_Supersonic = 1 << 7,
		kFlags_PinsLimbs = 1 << 8,
		kFlags_PassSmallTransparent = 1 << 9,
		kFlags_Detonates = 1 << 10,
		kFlags_Rotation = 1 << 11,
	};

	TESFullName						fullName;			// 030
	TESModel						model;				// 03C
	BGSPreloadable					preloadable;		// 054
	BGSDestructibleObjectForm		destructible;		// 058

	UInt16							projFlags;			// 060
	UInt16							type;				// 062
	float							gravity;			// 064
	float							speed;				// 068
	float							range;				// 06C
	TESObjectLIGH* lightProjectile;	// 070
	TESObjectLIGH* lightMuzzleFlash;	// 074
	float							tracerChance;		// 078
	float							altProximity;		// 07C
	float							altTimer;			// 080
	BGSExplosion* explosionForm;		// 084
	TESSound* soundProjectile;	// 088
	float							flashDuration;		// 08C
	float							fadeDuration;		// 090
	float							impactForce;		// 094
	TESSound* soundCountDown;		// 098
	TESSound* soundDisable;		// 09C
	TESObjectWEAP* defaultWeapSrc;		// 0A0
	float							rotationX;			// 0A4
	float							rotationY;			// 0A8
	float							rotationZ;			// 0AC
	float							bouncyMult;			// 0B0
	TESModel						muzzleFlash;		// 0B4
	UInt8							soundLevel;			// 0CC

	void SetFlag(UInt32 pFlag, bool bMod)
	{
		projFlags = bMod ? (projFlags | pFlag) : (projFlags & ~pFlag);
	}
};