#pragma once

#include "TESForm.hpp"
#include "TESWorldSpace.hpp"
#include "NiPoint3.hpp"
#include "BSSimpleList.hpp"
#include "TESRegionData.hpp"

class TESWeather;

class TESRegion : public TESForm {
public:
	TESRegion();
	~TESRegion();

	struct AreaPointEntry
	{
		float	x;
		float	y;
	};
	typedef BSSimpleList<AreaPointEntry> AreaPointEntryList;

	struct RegionAreaEntry
	{
		AreaPointEntryList	points;
		UInt32				unk08[2];
		float				unk10[4];
		UInt32				edgeFallOff;
		UInt32				pointCount;
	};
	typedef BSSimpleList<RegionAreaEntry> RegionAreaEntryList;

	RegionDataEntryList* dataEntries;	// 18
	RegionAreaEntryList* areaEntries;	// 1C
	TESWorldSpace* worldSpace;
	TESWeather* weather;
	float unk28;
	NiPoint3 externalEmittance;
};

ASSERT_SIZE(TESRegion, 0x38);

class TESRegionList : public BSSimpleList<TESRegion> {
public:
	TESRegionList();
	~TESRegionList();
};