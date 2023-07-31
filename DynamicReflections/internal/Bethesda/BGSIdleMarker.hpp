#pragma once

#include "TESBoundObject.hpp"
#include "BGSIdleCollection.hpp"

class BGSIdleMarker : public TESBoundObject {
public:
	BGSIdleCollection bgsidlecollection30;
};

ASSERT_SIZE(BGSIdleMarker, 0x40);