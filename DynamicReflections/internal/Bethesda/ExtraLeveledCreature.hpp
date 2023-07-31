#pragma once

#include "BSExtraData.hpp"

class TESForm;

class ExtraLeveledCreature : public BSExtraData {
public:
	ExtraLeveledCreature();
	virtual ~ExtraLeveledCreature();

	TESForm* baseForm;	// 00C
	TESForm* form;		// 010
};

ASSERT_SIZE(ExtraLeveledCreature, 0x14);