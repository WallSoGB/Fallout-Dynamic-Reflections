#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameExtraData.h"
#include "GameTasks.h"
#include "GameUI.h"
#include "SafeWrite.h"
#include "NiObjects.h"

static const UInt32 s_TESObject_REFR_init	= 0x0055A2F0;	// TESObject_REFR initialization routine (first reference to s_TESObject_REFR_vtbl)
static const UInt32	s_Actor_EquipItem		= 0x0088C650;	// maybe, also, would be: 007198E0 for FOSE	4th call from the end of TESObjectREFR::RemoveItem (func5F)
static const UInt32	s_Actor_UnequipItem		= 0x0088C790;	// maybe, also, would be: 007133E0 for FOSE next sub after EquipItem
static const UInt32 s_TESObjectREFR__GetContainer	= 0x0055D310;	// First call in REFR::RemoveItem
static const UInt32 s_TESObjectREFR_Set3D	= 0x005702E0;	// void : (const char*)
static const UInt32 s_PlayerCharacter_GetCurrentQuestTargets	= 0x00952BA0;	// BuildedQuestObjectiveTargets* : (void)
static const UInt32 s_PlayerCharacter_GenerateNiNode	= 0x0094E1D0; // Func0072
static const UInt32 kPlayerUpdate3Dpatch = 0x0094EB7A;
static const UInt32 TESObjectREFR_Set3D = 0x0094EB40;
static const UInt32 BipedAnim_Destroy = 0x00418E00;
static const UInt32 ExtraAnimAnimation_Destroy = 0x00418D20;
static const UInt32 RefNiRefObject_ReplaceNiRefObject = 0x0066B0D0;

static const UInt32 kg_Camera1st	= 0x011E07D0;
static const UInt32 kg_Camera3rd	= 0x011E07D4;
static const UInt32 kg_Bip			= 0x011E07D8;
static const UInt8 kPlayerUpdate3DpatchFrom	= 0x0B6;
static const UInt8 kPlayerUpdate3DpatchTo	= 0x0EB;

static NiObject **	g_3rdPersonCameraNode =				(NiObject**)kg_Camera3rd;
static NiObject **	g_1stPersonCameraBipedNode =		(NiObject**)kg_Bip;
static NiObject **	g_1stPersonCameraNode =				(NiObject**)kg_Camera1st;