#pragma once

#include "BGSTerrainNode.hpp"
#include "BSSimpleArray.hpp"
#include "NiNode.hpp"

class TESWorldSpace;

class BGSTerrainManager {
public:
	TESWorldSpace* pWorld;
	BGSTerrainNode* pRootNode;
	NiNodePtr spLODRoot;
	NiNodePtr spWaterLODNode;
	BGSTerrainNode::Coordinate coordNW;
	BGSTerrainNode::Coordinate coordSE;
	UInt32 uiMaxLevel;
	UInt32 uiMinLevel;
	UInt32 uiRootLevel;
	UInt32 uiLODLevel;
	bool bNeedsImmediateUpdate;
	bool bHasLOD;
	UInt8 byte2A;
	UInt8 byte2B;
	BSSimpleArray<TESObjectREFR*> kTreeRefs;

	bool HasRootNode();

	NiNode* GetWaterLODNode();
	NiNode* GetLODRoot();
	UInt32 GetLODLevel();

	static NiNode* GetRootLandLODNode();
	static NiNode* GetRootObjectLODNode();
	static NiNode* GetRootTreeLODNode();

	void ToggleObjectLOD(NiNode* apNode, bool abEnable, bool abCurrentCellOnly);
	void ToggleLandLOD(bool abEnable, bool abCurrentCellOnly);
	void ToggleTreeLOD(bool abEnable, bool abCurrentCellOnly);
};

ASSERT_SIZE(BGSTerrainManager, 0x3C);