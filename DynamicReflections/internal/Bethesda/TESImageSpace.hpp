#pragma once

#include "TESForm.hpp"

class TESImageSpace : public TESForm {
public:
	TESImageSpace();
	~TESImageSpace();

	float traitValues[33];
	UInt32 unk9C[5];
};

ASSERT_SIZE(TESImageSpace, 0xB0);