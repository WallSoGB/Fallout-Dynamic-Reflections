#pragma once

#include "BSExtraData.hpp"
#include "TESObjectREFR.hpp"

class ExtraDroppedItemList : public BSExtraData {
public:
	BSSimpleList<TESObjectREFR*> droppedItemList;
};