#pragma once

#include "TESBoundAnimObject.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESScriptableForm.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSOpenCloseForm.hpp"

class TESSound;

class TESObjectDOOR : public TESBoundAnimObject {
public:
	TESObjectDOOR();
	~TESObjectDOOR();

	TESFullName					name;				// 30
	TESModelTextureSwap			model;				// 3C
	TESScriptableForm			scriptForm;			// 5C
	BGSDestructibleObjectForm	destructForm;		// 68
	BGSOpenCloseForm			openCloseForm;		// 70
	UInt32 unk74;
	TESSound* openSound;
	TESSound* closeSound;
	TESSound* randomLoopingSound;
	UInt8 flags84;
	UInt8 byte85;
	UInt8 byte86;
	UInt8 byte87;
	BSSimpleList<int> list88;
};

ASSERT_SIZE(TESObjectDOOR, 0x90)