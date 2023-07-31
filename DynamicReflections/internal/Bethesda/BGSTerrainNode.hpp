#pragma once

#include "NiPoint3.hpp"
#include "NiPoint2.hpp"
#include "NiSmartPointer.hpp"
#include "BGSDistantTreeBlock.hpp"

struct BGSTerrainChunk;

class BGSTerrainManager;
class BGSDistantObjectBlock;

NiSmartPointer(BGSTerrainNode);

class BGSTerrainNode {
public:
	union Coordinate {
		UInt32 xy;
		struct {
			SInt16 y;
			SInt16 x;
		};
	};

	BGSTerrainManager* pManager;
	UInt32 uiLODLevel;
	Coordinate sBaseCellCoords;
	bool bIsLvlMaxOrLower;
	UInt8 byte0D;
	UInt8 byte0E;
	UInt8 byte0F;
	BGSTerrainChunk* pTerrainChunk;
	BGSDistantObjectBlock* pObjectBlock;
	BGSDistantTreeBlock* pTreeBlock;
	UInt32 ukn1C;
	BGSTerrainNode* pChildren[4];
	BGSTerrainNode* pParent;
	NiPoint3 pos34;
	float fDist;
	float fSplitDist;
	float fMorphStartDist;
	float fMorphEndDist;
	UInt32 uiTerrainFadeTimer;
	bool bForceFade;
	UInt32 uiLinkID;
	bool maybeShouldShow_5C;
	bool byte5D;
	bool byte5E;
	bool byte5F;

	SInt16 GetCellX();
	SInt16 GetCellY();
	BGSTerrainChunk* GetTerrainChunk();
	BGSDistantObjectBlock* GetObjectBlock();
	BGSDistantTreeBlock* GetTreeBlock();
	UInt32 GetLODLevel();
	float GetRange(const NiPoint2 apPos1, const NiPoint2 apPos2, float afScale);
	bool IsWithinLoadDistance(const NiPoint3& apPosition);
	bool IsWithinLowLoadDistance(const NiPoint3& apPosition);
	bool IsPlayerInRange();
};

ASSERT_SIZE(BGSTerrainNode, 0x60);