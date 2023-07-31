#pragma once

#include "TESForm.hpp"
#include "BGSPreloadable.hpp"

class BGSImpactDataSet : public TESForm {
public:
	BGSImpactDataSet();
	~BGSImpactDataSet();

	BGSPreloadable	preloadable;		// 018
	UInt32 unk01C[(0x4C - 0x1C) >> 2];	// 01C
};

ASSERT_OFFSET(BGSImpactDataSet, preloadable, 0x018);
ASSERT_SIZE(BGSImpactDataSet, 0x4C);