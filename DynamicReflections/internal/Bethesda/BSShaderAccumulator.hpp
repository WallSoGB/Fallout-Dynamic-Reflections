#pragma once

#include "BSBatchRenderer.hpp"
#include "BSRenderPass.hpp"
#include "BSSimpleList.hpp"
#include "NiAlphaAccumulator.hpp"
#include "NiTPointerMap.hpp"
#include "ShadowSceneLight.hpp"
#include "ShadowSceneNode.hpp"

NiSmartPointer(BSShaderAccumulator)
NiRTTIAddress(BSShaderAccumulator, 0x11FA000)

class BSShaderProperty;

class BSShaderAccumulator : public NiAlphaAccumulator {
public:

	virtual void FinishAccumulatingPreResolveDepth();
	virtual void FinishAccumulatingPostResolveDepth();
	virtual void Func_32(UInt32, UInt32);

	enum BATCHRENDERER_CREATION_MODE
	{
		BRCM_NORMAL = 0x63,
		BRCM_NO_GROUPS = 0x64,
		BRCM_ALPHA_GROUP = 0x65,
	};

	BSShaderAccumulator(BATCHRENDERER_CREATION_MODE aeBatchRendererCreationType, UInt32 batchRendererCount, RenderPassTypes maxPassCount);
	~BSShaderAccumulator();

	enum etRenderMode
	{
		BSSM_RENDER_NORMAL = 0x0, // Renders everything as you'd expect
		BSSM_RENDER_UNK1 = 0x1,
		BSSM_RENDER_UNK2 = 0x2,
		BSSM_RENDER_UNK3 = 0x3,
		BSSM_RENDER_UNK4 = 0x4,
		BSSM_RENDER_UNK5 = 0x5,
		BSSM_RENDER_UNK6 = 0x6,
		BSSM_RENDER_DEPTH_MAP = 0x7,
		BSSM_RENDER_CONST_ALPHA = 0x8, // Everything is green
		BSSM_RENDER_LOCAL_MAP = 0x9, // Renders vertex normals, skips landscape
		BSSM_RENDER_TILES = 0xA,
		BSSM_RENDER_UNK11 = 0xB,
		BSSM_RENDER_NO_WATER_PASS = 0xC, // Skips water rendering
		BSSM_RENDER_UNK13 = 0xD,
		BSSM_RENDER_WATER_DEPTH = 0xE,
		BSSM_RENDER_UNK15 = 0xF, // Everything is black except for grass, sky and emissives
	};

	struct ActorOcclusionTest
	{
		NiBound bound;
		UInt32 uiRefID;
		void* pOcclusionQuery;
		BYTE byte18;
		BYTE byte19;
		BYTE byte20;
		DWORD dword1C;
	};

	struct SunOcclusionTest {
		void* pOcclusionQuery;
		bool bWaiting;
		float fPercentOccluded;
		UInt32 uiFrameCount;
		UInt32 uiPixelCount;
	};

	UInt32 unk034;
	bool bWireFrameRelated;
	bool unk039;
	bool bRenderDOF;
	UInt32 uiSunPixelCount;
	bool bWaitingForSunQuery;
	float fPercentSunOccludedStored;
	SunOcclusionTest pSunTests[3];
	bool bProcessLights;
	bool bFirstPersonSomething;
	bool unk086;
	UInt16 unk088;
	UInt16 usQueryCount;
	void** ppOcclusionQueries;
	NiTPointerList<NiGeometry*> volumetricFogGeoList;
	PersistentPassList passList_09C;
	PersistentPassList passList_0B0;
	PersistentPassList passList_0C4;
	PersistentPassList passList_0D8;
	PersistentPassList passList_0EC;
	PersistentPassList passList_100;
	PersistentPassList passList_114;
	PersistentPassList passList_128;
	UInt32 unk13C;
	BSSimpleList<ActorOcclusionTest>* pActorOcclusionTestList;
	UInt32 unk144;
	UInt32 unk148;
	UInt32 refID;
	bool unk150;
	NiColorA ambientColor;
	bool bIgnoreWater;
	bool bRenderWaterDepth;
	bool unk166; // Water height related
	bool bIsUnderwater;
	UInt32 iWaterHeight;
	bool bRenderDecals;
	UInt32 unk170;
	BSBatchRenderer* pBatchRenderers[2];
	RenderPassTypes* pPasses;
	UInt32* alphaRelated;
	bool* unk184;
	bool* unk188;
	UInt32 uiBatchRendererCount;
	UInt32 uiMaxPassCount;
	ShadowSceneNode* pActiveShadowSceneNode;
	NiObject* pUnk198;
	etRenderMode eRenderMode;
	ShadowSceneLight* pDepthLght1A0;
	BSRenderPass* pTileRenderPass;
	UInt16 usRenderPassType;
	UInt32 unk1AC;
	UInt32 unk1B0;
	NiTPointerMap<UInt32, UInt32> pointerMap1B4;
	UInt32 unk1C4;
	UInt32 unk1C8;
	UInt32 unk1CC;
	UInt32 unk1D0;
	UInt32 unk1D4;
	UInt32 unk1D8;
	UInt32 unk1DC;
	UInt32 unk1E0;
	UInt32 unk1E4;
	UInt32 unk1E8;
	UInt32 unk1EC;
	UInt32 unk1F0;
	UInt32 unk1F4;
	UInt32 unk1F8;
	UInt32 unk1FC;
	LPCRITICAL_SECTION criticalSection;
	UInt32 unk204;
	UInt32 unk208;
	UInt32 unk20C;
	UInt32 unk210;
	UInt32 unk214;
	UInt32 unk218;
	UInt32 unk21C;
	UInt32 unk220;
	UInt32 unk224;
	UInt32 unk228;
	UInt32 unk22C;
	UInt32 unk230;
	UInt32 unk234;
	UInt32 unk238;
	UInt32 unk23C;
	UInt32 unk240;
	UInt32 unk244;
	UInt32 unk248;
	UInt32 unk24C;
	UInt32 unk250;
	UInt32 unk254;
	UInt32 unk258;
	UInt32 unk25C;
	UInt32 unk260;
	UInt32 unk264;
	UInt32 unk268;
	UInt32 unk26C;
	UInt32 unk270;
	UInt32 unk274;
	UInt32 unk278;
	UInt32 unk27C;

	static BSShaderAccumulator* Create(BATCHRENDERER_CREATION_MODE aeBatchRendererCreationType,
		UInt32 batchRendererCount, RenderPassTypes maxPassCount);

	void DoSunOcclusionQuery(NiTriShape* apSunGeometry, UInt32 aiTestNumber, NiCamera* apCamera);
	void ResetSunOcclusion();
	void FinishAccumulating_Standard_PreResolveDepth();
	void FinishAccumulating_Standard_PostResolveDepth();
	bool __fastcall RegisterObject(BSShaderAccumulator* apThis, void*, NiGeometry* apGeo);
	static void __cdecl FinishAccumulating_Tiles(BSShaderAccumulator* apAccumulator);
	static void __cdecl RegisterObject_Custom(BSShaderAccumulator* apAccumuluator, NiGeometry* apGeo, UInt32 unused, BSShaderProperty* apShaderProp, BSShader* apShader);
	bool RegisterObject_Standard(NiGeometry* apGeometry, int unused, BSShaderProperty* apShaderProp, BSShader* apShader);
	void RenderBatches(RenderPassTypes aeStart, RenderPassTypes aeEnd, bool abAlphaPass, int aUnk);
	void RenderGeometryGroup(UInt32 auiGeometryGroup, bool abAlphaPass);
	void RenderBlendedDecals();
	void RenderTiles();
	void RenderAlphaGeometry(UInt32 auiGeometryGroup);
	void SortAlpha();
	void RenderScreenSplatter();
	void RenderRefraction(NiCamera* apCamera, BSRenderedTexture* apTexture);
	void Unk_B65660();
	void Unk_B630C0();
	void Unk_B63B90(UInt32 auiGroup);
	void RenderDepth(NiCamera* apCamera1, NiCamera* apCamera2);
	void StartGroupingAlphas(NiBound* apBound, bool abZPrePass);
	void ClearAlphaGroups();
	void FreeCurrentPass();

	__forceinline void SetActiveShadowSceneNode(ShadowSceneNode* apShadowSceneNode) { pActiveShadowSceneNode = apShadowSceneNode; };
	__forceinline ShadowSceneNode* GetActiveShadowSceneNode() { return pActiveShadowSceneNode; };

	__forceinline void SetIsUnderwater(bool abIsUnderwater) { bIsUnderwater = abIsUnderwater; };
	__forceinline bool IsUnderwater() { return bIsUnderwater; };

	__forceinline void SetWaterHeight(UInt32 aWaterHeight) { iWaterHeight = aWaterHeight; };
	__forceinline UInt32 GetWaterHeight() { return iWaterHeight; };

	__forceinline void SetRenderDecals(bool abRenderDecals) { bRenderDecals = abRenderDecals; };
	__forceinline bool GetRenderDecals() { return bRenderDecals; };

	__forceinline void SetRenderDOF(bool abRenderDOF) { bRenderDOF = abRenderDOF; };
	__forceinline bool GetRenderDOF() { return bRenderDOF; };


	__forceinline void SetRenderMode(etRenderMode aeRenderMode) { eRenderMode = aeRenderMode; };
	__forceinline void SetRenderMode(UInt32 aiRenderMode) { eRenderMode = (etRenderMode)aiRenderMode; };
	__forceinline etRenderMode GetRenderMode() { return eRenderMode; };

	__forceinline void SetByte166(bool abValue) { unk166 = abValue; };
	__forceinline bool GetByte166() { return unk166; };
};

ASSERT_SIZE(BSShaderAccumulator, 0x280)