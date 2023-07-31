#pragma once

#include "TESForm.hpp"
#include "TESTexture.hpp"
#include "TESDescription.hpp"

class TESLoadScreen : public TESForm {
public:
	TESLoadScreen();
	~TESLoadScreen();

	TESTexture		texture;			// 018
	TESDescription	description;		// 024
	UInt32	unk2C[(0x3C - 0x2C) >> 2];	// 02C
};