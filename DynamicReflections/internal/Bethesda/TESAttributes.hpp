#pragma once

#include "BaseFormComponent.hpp"

class TESAttributes : public BaseFormComponent {
public:
	TESAttributes();
	~TESAttributes();

	enum
	{
		kStrength = 0,
		kPerception,
		kEndurance,
		kCharisma,
		kIntelligence,
		kAgility,
		kLuck,
	};

	UInt8	attributes[7];	// 4
	UInt8	padB;			// B
};

ASSERT_SIZE(TESAttributes, 0xC);