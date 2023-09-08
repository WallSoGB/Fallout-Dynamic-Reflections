#pragma once

#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESTexture.hpp"
#include "BSExtraData.hpp"
#include "ExtraDataList.hpp"
#include "NiTMap.hpp"
#include "NiSmartPointer.hpp"
#include "BSMultiBoundNode.hpp"
#include "BSPortalGraph.hpp"

class NiNode;
class NavMesh;
class TESObjectLAND;
class TESWorldSpace;
class TESObjectREFR;
class BGSLightingTemplate;

class TESObjectCELL : public TESForm {
public:
	TESObjectCELL();
	~TESObjectCELL();

	typedef BSSimpleList<TESObjectREFR*> RefList;

	enum CELL_STATE {
		CS_NOT_LOADED = 0x0,
		CS_UNLOADING = 0x1,
		CS_LOADING = 0x2,
		CS_LOADED = 0x3,
		CS_DETACHING = 0x4,
		CS_ATTACHING = 0x5,
		CS_ATTACHED = 0x6,
	};


	struct LoadedData {
		NiNodePtr spCell3D;
		BSSimpleList<TESObjectREFR*> LargeAnimatedRefs;
		NiTMap<TESObjectREFR*, NiNode*> AnimatedRefs;

		// Form can be either TESRegion or TESObjectLIGH
		NiTMap<TESForm*, TESObjectREFR*> EmittanceSourceRefMap;
		NiTMap<TESObjectREFR*, NiNode*> EmittanceLightRefMap;
		NiTMap<TESObjectREFR*, NiPointer<BSMultiBoundNode>> MultiboundRefMap;
		BSSimpleList<TESObjectREFR*> ScriptedRefs;
		BSSimpleList<TESObjectREFR*> ActivatingRefs;
		BSSimpleList<TESObjectREFR*> WaterRefs;
	};

	struct ExteriorData {
		SInt32 iCellX;
		SInt32 iCellY;
		UInt8 byte08;
	};

	struct InteriorData {
		UInt32 iAmbient;
		UInt32 iDirectional;
		UInt32 iFogColorNear;
		float fFogNear;
		float fFogFar;
		UInt32 iDirectionalXY;
		UInt32 iDirectionalZ;
		float fDirectionalFade;
		float fClipDist;
		float fFogPower;
		UInt32* getValuesFrom;
	};

	union CellData {
		ExteriorData* pCellDataExterior;
		InteriorData* pCellDataInterior;
	};

	enum CELLNODE {
		CN_ACTOR = 0x0,
		CN_MARKER = 0x1,
		CN_LAND = 0x2,
		CN_STATIC = 0x3,
		CN_DYNAMIC = 0x4,
		CN_OCCLUSION_PLANE = 0x5,
		CN_PORTAL = 0x6,
		CN_MULTIBOUND = 0x7,
		CN_COLLISION = 0x8,
		CN_LIGHT_MARKER = 0x9,
		CN_SOUND_MARKER = 0xA,
		CN_WATER_WADE = 0xB,
		CN_MAX = 0xC,
	};


	enum CELL_INHERIT_FLAGS {
		CIF_AMBIENT_COLOR = 0x1,
		CIF_DIRECTIONAL_COLOR = 0x2,
		CIF_FOG_COLOR = 0x4,
		CIF_FOG_NEAR = 0x8,
		CIF_FOG_FAR = 0x10,
		CIF_DIRECTIONAL_ROT = 0x20,
		CIF_DIRECTIONAL_FADE = 0x40,
		CIF_CLIP_DIST = 0x80,
		CIF_FOG_POWER = 0x100,
	};

	TESFullName								name;
	UInt8									sCellFlags;
	UInt8									sCellGameFlags;
	UInt8									cCellState;
	UInt8									byte27;
	ExtraDataList							ExtraList;
	CellData								pCellData;
	TESObjectLAND*							pCellLand;
	float									fWaterHeight;
	bool									bAutoWaterLoaded;
	TESTexture								noiseTexture;
	NavMesh**								pNavMeshes;
	UInt32									unk68[6];
	RTL_CRITICAL_SECTION					kSpinLock;
	UInt32									unk98;
	UInt32									unk9C;
	SInt32									iNumNonActorRefs;
	SInt32									iNumRefs;
	UInt16									usCountVisibleDistant;
	UInt16									usVisibleWhenDistantCountLoaded;
	BSSimpleList<NiPointer<TESObjectREFR>>	ReferencesA;
	NiNodePtr								spLightMarkerNode;
	NiNodePtr								spSoundMarkerNode;
	UInt32									unkBC;
	TESWorldSpace*							pWorldSpace;
	LoadedData*								pLoadedData;
	float									fLODFadeOut;
	UInt8									byteCC;
	UInt8									byteCD;
	UInt8									byteCE;
	UInt8									byteCF;
	UInt8									byteD0;
	bool									bCellDetached;
	UInt8									byteD2;
	UInt8									byteD3;
	BSPortalGraphPtr						spPortalGraph;
	BGSLightingTemplate*					pLightingTemplate;
	UInt32									uiInheritFlags;

	__forceinline bool IsInterior() { return (sCellFlags & 1) != 0; }

	__forceinline bool HasWater() { return (sCellFlags & 2) != 0; }

	__forceinline TESWorldSpace* GetWorldspace() { return IsInterior() ? pWorldSpace : nullptr; }

	CELL_STATE GetState();

	bool IsAttached();
	bool GetInheritFlag(CELL_INHERIT_FLAGS aeFlag);
	BGSLightingTemplate* GetLightingTemplate();
	float GetExteriorWaterHeight();

	NiNode* Get3D();

	NiNode* GetChildNode(CELLNODE aeNode);

	NiNode* GetGeometry(UInt32 auiIndex);

	static SInt32 GetCoord(SInt32 x, SInt32 y);

	InteriorData* GetInteriorData();
};

ASSERT_SIZE(TESObjectCELL::LoadedData, 0x64);
ASSERT_OFFSET(TESObjectCELL, pCellLand, 0x4C);
ASSERT_OFFSET(TESObjectCELL, spPortalGraph, 0xD4);
ASSERT_SIZE(TESObjectCELL, 0xE0);