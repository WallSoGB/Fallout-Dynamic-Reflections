#pragma once

#include "TESForm.hpp"
#include "TESTexture.hpp"
#include "TESObjectCELL.hpp"
#include "BSSimpleArray.hpp"

class BGSTerrainManager;
class TESClimate;
class TESImageSpace;
class TESWaterForm;
class BGSMusicType;
class BGSEncounterZone;
class BGSImpactData;
class LODdata;

class TESWorldSpace : public TESForm {
public:
	struct CoordXY {
		float	X;	// 000
		float	Y;	// 004
	};	// 008

	struct DCoordXY {
		SInt32	X;	// 000
		SInt32	Y;	// 004
	};	// 008

	struct WCoordXY {
		SInt16	X;	// 000
		SInt16	Y;	// 002
	};	// 004

	struct Offset_Data
	{
		UInt32** unk000;	// 000 array of UInt32 stored in OFST record (indexed by relative CellXY).
		CoordXY min;		// 004 NAM0
		CoordXY max;		// 00C NAM9
		UInt32	fileOffset;	// 014 TESWorldSpace file offset in modInfo
	};	// 014

	struct MapData
	{
		DCoordXY	usableDimensions;
		WCoordXY	cellNWCoordinates;
		WCoordXY	cellSECoordinates;
	};	// 010

	struct ImpactData
	{
		typedef NiTMapBase<BGSImpactData*, BGSImpactData*> ImpactImpactMap;
		enum MaterialType
		{
			eMT_Stone = 0,
			eMT_Dirt,
			eMT_Grass,
			eMT_Glass,
			eMT_Metal,
			eMT_Wood,
			eMT_Organic,
			eMT_Cloth,
			eMT_Water,
			eMT_HollowMetal,
			eMT_OrganicBug,
			eMT_OrganicGlow,

			eMT_Max
		};

		ImpactImpactMap	impactImpactMap[eMT_Max];	// 000
		char			footstepMaterials[0x12C];	// 030
	};

	typedef NiTPointerMap<UInt32, BSSimpleList<TESObjectREFR*>*> RefListPointerMap;
	typedef NiTPointerMap<SInt32, TESObjectCELL*> CellPointerMap;
	typedef NiTMapBase<TESFile*, TESWorldSpace::Offset_Data*> OffsetDataMap;

	TESFullName			fullName;			// 018 confirmed
	TESTexture			texture;			// 024 confirmed ICON
	CellPointerMap* cellMap;			// 030 confirmed
	TESObjectCELL* pSkyCell;				// 034 should be the Permanent cell
	UInt32				unk038;				// 038
	BGSTerrainManager* terrainManager;			// 03C looks to be the LOD data (That is what is returned when checking the parent "Use LOD data" flag)
	TESClimate* climate;			// 040 confirmed CNAM
	TESImageSpace* imageSpace;		// 044 confirmed INAM
	ImpactData* impactSwap;			// 048 confirmed
	UInt8				flags;				// 04C confirmed DATA
	UInt8				unk04D;				// 04D filler
	UInt16				sParentUseFlags;		// 04E init'd to FF if has a parent. 5 is use ImageSpace, 4 is use parent climate, 3 is use parent Water, 1 is use parent LOD data, 0 is use parent LAND data
	RefListPointerMap	fixedPersistentRefMap;			// 050 confirmed
	BSSimpleList<TESObjectREFR*>		mobilePersistentRefs;				// 060
	BSSimpleList<BSPortalGraph*>		lst068;				// 068 confirmed as BSSimpleList
	TESWorldSpace* pParentWorld;			// 070 confirmed
	TESWaterForm* waterFormFirst;	// 074 confirmed NAM2
	TESWaterForm* waterFormLast;	// 078 confirmed NAM3 LOD Water type for xEdit
	float				fWaterLODHeight;		// 07C confirmed NAM4
	MapData				mapData;			// 080 confirmed MNAM
	float				worldMapScale;		// 090 confirmed ONAM for three floats
	float				worldMapCellX;		// 094 confirmed
	float				worldMapCellY;		// 098 confirmed
	BGSMusicType* music;			// 09C confirmed ZNAM
	CoordXY				min;				// 0A0 confirmed NAM0 min of all Offset_Data.min
	CoordXY				max;				// 0A8 confirmed NAM9 max of all Offset_data.max
	OffsetDataMap		offsetMap;			// 0B0 guarded by an isESM
	BSStringT			editorID;				// 0C0
	float				defaultLandHeight;	// 0C8 confirmed DNAM for the two
	float				defaultWaterHeight;	// 0CC
	BGSEncounterZone* encounterZone;	// 0D0 confirmed
	TESTexture			canopyShadow;		// 0D4 confirmed NNAM
	TESTexture			waterNoiseTexture;	// 0E0 confirmed XNAM

	BGSTerrainManager* GetTerrainManager();
	TESObjectCELL* GetCellAtCoord(SInt32 x, SInt32 y);
};

ASSERT_SIZE(TESWorldSpace, 0xEC);