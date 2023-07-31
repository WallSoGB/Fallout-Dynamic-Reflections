#pragma once

#include "BSExtraData.hpp"
#include "BSSimpleList.hpp"
#include "BSPointer.hpp"

class TESObjectREFR;

struct ExtraDataList : public BaseExtraList {
	static ExtraDataList* Create(BSExtraData* xBSData = NULL);

	BSSimpleList<BSPointer<TESObjectREFR>*>* GetReflectedRefs();
	void* GetRefractionProperty();
};

ASSERT_SIZE(ExtraDataList, 0x020);