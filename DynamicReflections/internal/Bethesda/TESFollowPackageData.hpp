#pragma once

#include "TESPackage.hpp"

class TESFollowPackageData : public TESPackageData {
public:
	TESFollowPackageData();
	~TESFollowPackageData();
	TESPackage::LocationData* endLocation;
	float	flt008;
};