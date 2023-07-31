#pragma once

#include "TESBoundAnimObject.hpp"
#include "TESContainer.hpp"
#include "TESFullName.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESScriptableForm.hpp"
#include "TESWeightForm.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSOpenCloseForm.hpp"

class TESSound;

class TESObjectCONT : public TESBoundAnimObject {
public:
	TESObjectCONT();
	~TESObjectCONT();

	TESContainer                container;          // 30
	TESFullName					name;				// 3C
	TESModelTextureSwap			model;				// 48
	TESScriptableForm			scriptForm;			// 68
	TESWeightForm				weightForm;			// 74
	//	TESMagicCasterForm			magicCaster;		//
	//	TESMagicTargetForm			magicTarget;		//
	BGSDestructibleObjectForm	destructForm;		// 7C
	BGSOpenCloseForm			openCloseForm;		// 84 / B8
	UInt32 unk88;
	TESSound* openSound;						// 08C
	TESSound* closeSound;						// 090
	TESSound* randomLoopingSound;				// 094
	UInt8		flags;								// 098
	UInt8		pad099[3];
};

ASSERT_SIZE(TESObjectCONT, 0x9C);