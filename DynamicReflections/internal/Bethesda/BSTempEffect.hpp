#pragma once

#include "NiObject.hpp"

class TESObjectCELL;

class BSTempEffect : public NiObject {
public:
	BSTempEffect();
	~BSTempEffect();

	virtual void Initialize();

	float			fLifetime;
	TESObjectCELL*	pCell;
	float			fAge;
	bool			bInitialized;
};