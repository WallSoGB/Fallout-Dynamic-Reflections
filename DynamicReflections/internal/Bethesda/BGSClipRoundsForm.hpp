#pragma once

#include "BaseFormComponent.hpp"

class BGSClipRoundsForm : public BaseFormComponent {
public:
	BGSClipRoundsForm();
	~BGSClipRoundsForm();

	UInt8	clipRounds;
	UInt8	padding[3];
	// 008
};

ASSERT_SIZE(BGSClipRoundsForm, 0x8);