#pragma once

#include "BSSimpleArray.hpp"
#include "BSResizableTriShape.hpp"
#include "BSDistantTreeShaderProperty.hpp"
#include "BSMap.hpp"

class BGSTerrainNode;

struct BGSDistantTreeBlock {
	struct InstanceData {
		UInt32 id;
		UInt16 x;
		UInt16 y;
		UInt16 z;
		float fRotZ;
		float fScale;
		UInt32 unk18;
		UInt32 unk1C;
		bool bHidden;
	};

	struct TreeGroup {
		void* unk00;
		BSResizableTriShapePtr spGeometry;
		BSSimpleArray<BGSDistantTreeBlock::InstanceData*> Instances;
		UInt32 uiNum;
		bool bShaderPropertyUpToDate;
	};

	void* pLoadTask;
	BSSimpleArray<BGSDistantTreeBlock::TreeGroup*> TreeGroups;
	BSMap<UInt32, BGSDistantTreeBlock::InstanceData*> InstanceMap;
	BSMap<UInt32, BGSDistantTreeBlock::TreeGroup*> NextGroup;
	BSSimpleArray<UInt32> UIntArray;
	BGSTerrainNode* pNode;
	bool bDoneLoading;
	bool bAttached;
	bool bAllVisible;

	void UpdateShaderPropertyRecurse();
	void UpdateShaderProperty(BSDistantTreeShaderProperty* apShaderProp, BGSDistantTreeBlock::TreeGroup* apGroup);
	void HideLOD(UInt32 aID, bool unk3);

};

ASSERT_SIZE(BGSDistantTreeBlock, 0x4C);