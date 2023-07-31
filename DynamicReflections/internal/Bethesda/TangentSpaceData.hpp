#pragma once

#include "NiRefObject.hpp"

NiSmartPointer(TangentSpaceData);

class TangentSpaceData : public NiRefObject {
public:
	bool unk8;
	void* unkC;
	void* unk10;
};

ASSERT_SIZE(TangentSpaceData, 0x14);