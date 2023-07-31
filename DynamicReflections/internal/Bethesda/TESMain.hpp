#pragma once

#include "BSShaderAccumulator.hpp"
#include "SceneGraph.hpp"

class Sun;

class OSInputGlobals;
class OSSoundGlobals;
struct BSPackedTaskQueue;
class ImageSpaceManager;
class TESProjectile;
class NiPointLight;
class BGSCameraShot;
class ImageSpaceModifierInstanceForm;
class TESIdleForm;

enum VATS_MODE_ENUM {
	VATS_MODE_NONE = 0x0,
	VATS_TARGET_SELECT = 0x1,
	VATS_LIMB_SELECT = 0x2,
	VATS_PLAYBACK = 0x4,
	VATS_MODE_COUNT = 0x5,
};

struct VATSCameraData {
	BSSimpleList<UInt32> targetsList; // BSSimpleList<VATSQueuedAction>
	VATS_MODE_ENUM eMode;
	UInt32 unk0C;
	BGSCameraShot* pCamShot;
	float flt14;
	float flt18;
	TESProjectile* pProjectile;
	TESProjectile* unk20;
	TESIdleForm* pAttackAnim;
	ImageSpaceModifierInstanceForm* pISModInstForm;
	void* pISModInstRB;
	UInt32 unk30;
	NiPointLight* pLight;
	bool byte38;
	UInt32 uiNumKills;
	UInt32 unk40;
	UInt32 unk44;

	bool IsPlaying() { return eMode == VATS_PLAYBACK; }
	bool HasMode() { return eMode != VATS_MODE_NONE; };
};

class TESMain {
public:
	bool bOneMore;
	bool bQuitGame;
	bool bExitToMainMenu;
	bool bGameActive;
	bool unk04;
	bool unk05;
	bool bIsFlyCam;
	bool bFreezeTime;
	HWND__* hWnd;
	HINSTANCE__* hInstance;
	UInt32 iThreadID;
	void* mainThreadHandle;
	UInt32* PackedTaskHeap;
	UInt32 unk1C;
	OSInputGlobals* pInput;
	OSSoundGlobals* pSound;
	BSPackedTaskQueue* pTaskQueue;
	UInt32 unk2C;
	UInt32 unk30;
	UInt32 unk34;
	UInt32 unk38;
	UInt32 unk3C;
	UInt32 unk40;
	UInt32 unk44;
	UInt32 unk48;
	UInt32 unk4C;
	UInt32 SecondaryPackedTaskHeap;
	UInt32 unk54;
	UInt32 unk58;
	UInt32 unk5C;
	BSPackedTaskQueue* pSecondaryTaskQueue;
	UInt32 unk64;
	UInt32 unk68;
	UInt32 unk6C;
	UInt32 unk70;
	UInt32 unk74;
	UInt32 unk78;
	UInt32 unk7C;
	UInt32 unk80;
	UInt32 unk84;
	BSShaderAccumulatorPtr spWorldAccum;
	BSShaderAccumulatorPtr sp1stPersonAccum;
	BSShaderAccumulatorPtr spAccumulator_Aiming;
	BSShaderAccumulatorPtr spScreenSplatterAccum;
	BSShaderAccumulatorPtr spAccumulator5;
	bool bShouldSetViewPort;
	NiCameraPtr spFirstPersonCamera;

	static __forceinline VATSCameraData* GetVATSCameraData() { return (VATSCameraData*)0x11F2250; };
	static __forceinline BSMultiBoundNode* GetSkyRoot() { return *(BSMultiBoundNode**)0x11DEB34; };
	static __forceinline NiNode* GetObjectLODRoot() { return *(NiNode**)0x11DEA18; };
	static __forceinline NiNode* GetLandLODRoot() { return *(NiNode**)0x11DEA14; };
	static __forceinline SceneGraph* GetWorldRoot() { return *(SceneGraph**)0x11DEB7C; };
	static __forceinline NiNode* GetWeatherRoot() { return *(NiNode**)0x11DEDA4; };
	static __forceinline NiCamera* GetWorldRootCamera() { return GetWorldRoot()->spCamera.m_pObject; };
	static __forceinline NiNode* Get1stCamNode() { return *(NiNode**)0x11E07D0; };
	static __forceinline float GetFrameAnimTime() { return *(float*)0x11DEA30; };

	BSRenderedTexture* SetupMainISTexture(NiDX9Renderer* apRenderer, BSRenderedTexture* apTexture, bool abDisableIS, bool abIsMSAA);

	void RenderWorldSceneGraph(Sun* pSun, int, bool bIsWireframe, bool bIsInVATS);

	void UpdateWater();

	static void __fastcall Swap(TESMain* apThis);
	static void __fastcall RenderDefault(TESMain* apThis, void*, BSRenderedTexture* apRenderedTexture2, bool bIsPipBoyMode);
	static void __fastcall RenderWireframe(TESMain* apThis, void*, BSRenderedTexture* apRenderedTexture2, bool bIsPipBoyMode);
	static void __fastcall RenderPipBoy(TESMain* apThis, void*, BSRenderedTexture* apRenderedTexture2, bool abDisableIS);

	static __forceinline TESMain* GetInstance() { return *(TESMain**)0x11DEA0C; };

	static __forceinline BSShaderAccumulator* GetShaderAccumulator() { return GetInstance()->spWorldAccum.m_pObject; };

	static __forceinline void StartAccumulating(NiCamera* apCamera, BSShaderAccumulator* apAccumulator);

	static __forceinline void SetMainISTexture(BSRenderedTexture* apTexture) { *(BSRenderedTexture**)0x11F9438 = apTexture; };
	static __forceinline BSRenderedTexture* GetMainISTexture() { return (*(BSRenderedTexture**)0x11F9438); };
	static __forceinline void SetBackgroundTexture(BSRenderedTexture* apTexture) { *(BSRenderedTexturePtr*)0x11DED3C = apTexture; };
	static __forceinline BSRenderedTexture* GetBackgroundTexture() { return (*(BSRenderedTexturePtr*)0x11DED3C).m_pObject; };



	static UInt32 GetFrameID() { return *(UInt32*)0x11A2FE0; }

	Sun* PrepareScene();
	void RenderShadowMaps();
	bool Render_VATS_8749B0();
	void Render_VATS_874AC0(bool bIsInVATS);
	static void SetOffScreenRTGroup(BSRenderedTexture* apTexture, UInt32 auiClearMode);
	void FinishRender(BSRenderedTexture* apRenderedTexture1, ImageSpaceManager* apImageSpaceManager, NiDX9Renderer* apRenderer, Sun* apSun);
	void RenderHands();
	void RenderViewModel(NiDX9Renderer* apRenderer, NiAVObject* apPipBoyNode, Sun* apSun, BSRenderedTexture* apRenderedTexture);
	void RenderPostProcess(BSRenderedTexture* apRenderedTexture1, NiDX9Renderer* apRenderer, BSRenderedTexture* apRenderedTexture2);
	void RenderAimDOF(BSRenderedTexture* apTexture);
	void RenderDepthOfField(BSShaderAccumulator* apAccumulator, BSRenderedTexture* apRenderedTexture);
	void RenderScreenSplatter(NiDX9Renderer* apRenderer);
	void InitRefraction(BSShaderAccumulator* apAccumulator, BSRenderedTexture* apTexture);
	void RenderPipboyScreen(NiDX9Renderer* apRenderer);
	void CreateBackgroundTexture(ImageSpaceManager* apImageSpaceManager, NiDX9Renderer* apRenderer, bool bIsMSAA, BSRenderedTexture* apTexture);
};

ASSERT_SIZE(TESMain, 0xA4);

namespace ToggleCellNodesFlags {
#define g_ToggleCellNodesFlags *(UInt32*)0x11CA08C

	static bool GetFlag(UInt8 flag) { return (g_ToggleCellNodesFlags & (1 << flag)) != 0; };
	static void SetFlag(UInt8 flag, bool bSet) { if (bSet) g_ToggleCellNodesFlags |= (1 << flag); else g_ToggleCellNodesFlags &= ~(1 << flag); };
}