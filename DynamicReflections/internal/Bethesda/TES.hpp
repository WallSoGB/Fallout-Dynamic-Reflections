#pragma once

#include "TESObjectCELL.hpp"
#include "TESWater.hpp"
#include "Sky.hpp"
#include "NiSourceTexture.hpp"
#include "NiDirectionalLight.hpp"
#include "BSTempNodeManager.hpp"
#include "GridCellArray.hpp"

class TESCreature;
class NavMeshInfoMap;
class LoadedAreaBound;
class NiFogProperty;
class TESWorldSpace;
class ImageSpaceModifierInstance;
class TESObjectREFR;
class QueuedFile;
class GridDistantArray;

class TES {
public:
	virtual void Fn_00(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5);

	struct DeathCount
	{
		TESCreature* creatureOrNPC;
		UInt16 count;
	};

	struct DeathCounts
	{
		DeathCount* data;
		DeathCounts* next;
	};

	GridDistantArray* pGridDistantArray;
	GridCellArray* pGridCellArray;
	NiNode* pObjRoot;
	NiNode* pLODRoot;
	NiNode* pObjLODWaterRoot;
	BSTempNodeManager* pTempNodeManager;
	NiDirectionalLight* pObjLight;
	NiFogProperty* pObjFog;
	int iCurrentGridX;
	int iCurrentGridY;
	int iCurrentQueuedX;
	int iCurrentQueuedY;
	TESObjectCELL* pInteriorCell;
	TESObjectCELL** pInteriorBuffer;
	TESObjectCELL** pExteriorBuffer;
	UInt32 iTempInteriorBufferSize;
	UInt32 iTempExteriorBufferSize;
	UInt32 iSaveGridX;
	UInt32 iSaveGridY;
	UInt8 byte50;
	bool bRunningCellTests;
	UInt8 byte52;
	UInt8 gap53;
	UInt32 renderTestCellsCallback;
	UInt32 unk58;
	UInt32 unk5C;
	bool bShowLANDborders;
	TESWater* pWaterManager;
	Sky* pSky;
	BSSimpleList<NiPointer<ImageSpaceModifierInstance>> listActiveImageSpaceModifiers;
	UInt32 unk74;
	UInt32 unk78;
	UInt8 byte7C;
	UInt8 byte7D;
	UInt8 gap7E;
	UInt8 gap7F;
	float fCell_delta_x;
	float fCell_delta_y;
	TESWorldSpace* pWorldSpace;
	UInt32* list8C[2];
	BSSimpleList<TESObjectREFR*> cellFurnitureList;
	TES::DeathCounts deathCounts;
	NiPointer<QueuedFile> spQueuedFileA4;
	NiSourceTexturePtr spBloodDecalPreload1;
	NiPointer<QueuedFile> spQueuedFileAC;
	void* pParticleCacheHead;
	bool bFadeWhenLoading;
	bool bAllowUnusedPurge;
	UInt8 byteB6;
	UInt8 byteB7;
	UInt32 iPlaceableWaterCount;
	NavMeshInfoMap* pNavMeshInfoMap;
	NiPointer<LoadedAreaBound> spLoadedAreaBound;

	static TES* GetSingleton();

	static Sky* GetSky();

	static TESWorldSpace* GetWorldSpace();

	static TESObjectCELL* GetInterior();

	static bool IsCellLoaded(TESObjectCELL* apCell, bool abIgnoreBuffered);

	GridCell* GetGridCell(SInt32 aX, SInt32 aY);

	void CreateTextureImage(const char* apPath, NiSourceTexturePtr* aspTexture, bool abNoFileOK, bool abArchiveOnly);
};

ASSERT_SIZE(TES, 0xC4);

extern TES* g_TES;