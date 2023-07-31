#pragma once

#include "TESBoundObject.hpp"
#include "TESModelTextureSwap.hpp"

class TESObjectSTAT : public TESBoundObject {
public:
	TESObjectSTAT();
	~TESObjectSTAT();

	// children
	TESModelTextureSwap model;
	UInt32 unk50[2];
};

ASSERT_SIZE(TESObjectSTAT, 0x58);