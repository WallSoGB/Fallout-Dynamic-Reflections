#pragma once

#include "BSTempEffect.hpp"

class ActiveEffect;
class TESObjectREFR;

class MagicHitEffect : public BSTempEffect {
public:
	MagicHitEffect();
	~MagicHitEffect();

	ActiveEffect* activeEffect;	// 18
	TESObjectREFR* target;		// 1C
	float			unk20;			// 20	Init'd from ActiveEffect.timeElapsed
	UInt8 flags;
};