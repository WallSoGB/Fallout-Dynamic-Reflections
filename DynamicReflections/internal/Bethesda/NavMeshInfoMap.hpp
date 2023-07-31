#pragma once

#include "TESForm.hpp"

class NavMeshInfoMap : public TESForm {
	UInt8 byte18;
	UInt8 gap19[3];
	NiTPointerMap<UInt32, UInt32> navMeshInfoMap;
	NiTMap<UInt32, UInt32> intNavMeshInfoMap;
	UInt8 byte3C;
	UInt8 gap3D[3];
};

ASSERT_SIZE(NavMeshInfoMap, 0x40)