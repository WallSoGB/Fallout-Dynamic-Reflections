#pragma once

#include "BGSTerrainNode.hpp"
#include "BSSegmentedTriShape.hpp"
#include "BSMultiBoundNode.hpp"

class TESWorldSpace;

class BGSDistantObjectBlock {
public:
	BGSTerrainNodePtr spTerrainNode;
	BSSegmentedTriShapePtr spSegmentedTriShape;
	BSMultiBoundNodePtr spMultiboundNode;
	BSSegmentedTriShapePtr spNode0C; // old ones?
	BSMultiBoundNodePtr spNode10;
	NiNodePtr spNode14;
	void* spDistantObjectBlockLoadTask;
	NiNode* pNode1C;
	bool byte20;
	bool bIsAddedToDistantBlocksList;
	bool byte22;
	bool bIsHigh;
	UInt8 byte24;
	UInt32 unk28;

	static BGSDistantObjectBlock* Create(BGSTerrainNode* apTerrainNode, UInt32 auiLODLevel, SInt16 aZ, SInt16 aX, bool abIsLow);

	void Destroy(bool abFreeMemory);
	bool IsHigh();
	BSSegmentedTriShape* GetShape();
	BSMultiBoundNode* GetMultiBound(bool abUnk);
};