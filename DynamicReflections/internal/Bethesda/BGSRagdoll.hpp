#pragma once

#include "TESForm.hpp"
#include "TESModel.hpp"

class BGSRagdoll : public TESForm {
public:
	BGSRagdoll();
	~BGSRagdoll();

	TESModel	model;					// 018
	UInt32	unk030[(0x148 - 0x30) >> 2];	// 030
};

ASSERT_SIZE(BGSRagdoll, 0x148);