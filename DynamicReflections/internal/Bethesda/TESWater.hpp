#pragma once

#include "BSRenderedTexture.hpp"
#include "BSShaderAccumulator.hpp"
#include "BSSimpleList.hpp"
#include "NiCamera.hpp"
#include "NiRefObject.hpp"
#include "NiTListBase.hpp"
#include "NiTStringMap.hpp"
#include "BSSoundHandle.hpp"
#include "TESForm.hpp"
#include "TESObjectREFR.hpp"
#include "NiSourceTexture.hpp"

class TES;
class TESWaterForm;
class WadingWaterData;

NiSmartPointer(TESWater);

class TESWater {
public:

	//struct WaterGroup
	//{
	//	TESWaterForm* waterForm;
	//	UInt32 unk04;
	//	WaterGroup* waterGroup;
	//	float flt0C;
	//	float waterHeight;
	//	UInt32 unk14;
	//	UInt32 unk18;
	//	float flt1C;
	//	float flt20;
	//	NiTListBase<TESObjectREFR> waterPlanes;
	//};

	struct WaterGroup
	{
		TESWaterForm*					pWaterForm;
		NiPlane							mainPlane;
		NiPlane							plane014;
		NiTListBase<TESObjectREFR*>		lWaterPlanes;
		NiTListBase<TESObjectREFR*>		dList030;
		NiTListBase<TESObjectREFR*>		dList03C;
		NiTListBase<UInt32>				dList048;
		BSRenderedTexturePtr			spReflectionTexture;
		NiAVObjectPtr					spRef058;
		bool							bUsesWaterLevel;
		bool							bIsVisible;
		bool							bUnk05E;
		bool							bIsInterior;
		bool							bAllowLowDetailReflections;
		NiTPointerListBase<NiNode*>		geometryGroup;
		NiTPointerListBase<NiNode*>		explosionList;
		NiTPointerListBase<NiNode*>		depth_CellGeometryList;
		NiTPointerListBase<NiNode*>		dList088;
		BSShaderAccumulatorPtr			spShaderAccum;
		BSShaderAccumulatorPtr			spDepthShaderAccum;
		UInt32							uiReflectionGroupCount;
		UInt32							uiDepthGroupCount;
		NiCameraPtr						spCamera;
		NiCameraPtr						spDepthCamera;
		UInt32							uiStencilMask;
	};

	UInt32												uiNumWaterGroups;
	UInt32												uiUnk004;
	NiRefObjectPtr										spRT008;
	NiRefObjectPtr										spRef00C;
	NiRefObjectPtr										spRt010;
	NiRefObjectPtr										spRt014;
	NiRefObjectPtr										spRef018;
	NiSourceTexturePtr									spWaterNoiseTexture;
	NiRefObjectPtr										spRef020;
	float												fUnk24;
	NiPoint2											point28;
	UInt32												uiUnk30;
	BYTE												unk34;
	float												fUnk38;
	NiTListBase<WaterGroup*>							lWaterGroups;
	WaterGroup*											pWaterLOD;
	NiTPointerMap<TESObjectREFR*, TESObjectREFR*>		refMap04C;
	NiTPointerMap<TESObjectREFR*, TESObjectREFR*>		refMap05C;
	NiTPointerMap<TESWaterForm*, bool>					waterFormMap06C;
	NiTPointerMap<TESObjectREFR*, WadingWaterData*>		WadingWaterMap;
	BSSoundHandle										sound;
	float												fUnk098;
	UInt8												bUnk09C;

	static bool bSkipNextUpdate;
	static NiCamera* pCamera;
	static UInt32 uiActiveWaterGroups;
	static bool* const bPauseTime;

	static __forceinline void SetIsUnderwater(bool abIsUnderwater) { *(bool*)0x11C7A59 = abIsUnderwater; }
	static __forceinline bool IsUnderwater() { return *(bool*)0x11C7A59; }
	static __forceinline bool IsUnderwater2() { return *(bool*)0x11C7A58; }

	static __forceinline bool IsWaterEnabled() { return *(bool*)0x1189624; }
	static __forceinline void SetWaterEnabled(bool abEnabled) { *(bool*)0x1189624 = abEnabled; }

	static __forceinline float GetCameraHeight() { return *(float*)0x11FF8A8; }
	static __forceinline void SetCameraHeight(float afHeight) { *(float*)0x11FF8A8 = afHeight; }

	static __forceinline bool IsInInterior() { return *(bool*)0x11FF101; }
	static __forceinline void SetIsInInterior(bool abIsInInterior) { *(bool*)0x11FF101 = abIsInInterior; }

	static __forceinline bool CanReflectAtCustomLvl() { return *(bool*)0x11C7A67; }
	static __forceinline void SetCanReflectAtCustomLvl(bool abCanReflect) { *(bool*)0x11C7A67 = abCanReflect; }

	static __forceinline bool CanReflectAtWaterLvl() { return *(bool*)0x11C7A66; }
	static __forceinline void SetCanReflectAtWaterLvl(bool abCanReflect) { *(bool*)0x11C7A66 = abCanReflect; }

	static __forceinline NiNode* GetWadeRoot() { return *(NiNodePtr*)0x11C7C28; }

	static void* __fastcall RenderSurface_Hook(NiRefObjectPtr* apThis);
	void UpdateLOD(NiCamera* apCamera, bool abForceDisplay);
	void RenderWater(NiCamera* apCamera, bool abForceDisplay);
	static bool ReflectionFix_Hook();
	static TESObjectCELL* __fastcall ReflectionFix_Hook2(TES* tes);
};

ASSERT_SIZE(TESWater, 0xA0);
ASSERT_SIZE(TESWater::WaterGroup, 0xB0);