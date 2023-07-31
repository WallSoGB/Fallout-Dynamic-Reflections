#pragma once

#include "TESForm.hpp"
#include "TESIcon.hpp"

class BGSMenuIcon : public TESForm {
public:
	BGSMenuIcon();
	~BGSMenuIcon();

	TESIcon	icon;	// 18
};

ASSERT_SIZE(BGSMenuIcon, 0x24);