#pragma once

enum ExtraDataType : UInt8 {
	kExtraData_Havok = 0x01,
	kExtraData_Cell3D = 0x02,
	kExtraData_CellWaterType = 0x03,
	kExtraData_RegionList = 0x04,
	kExtraData_SeenData = 0x05,
	kExtraData_CellMusicType = 0x07,
	kExtraData_CellClimate = 0x08,
	kExtraData_ProcessMiddleLow = 0x09,
	kExtraData_CellCanopyShadowMask = 0x0A,
	kExtraData_DetachTime = 0x0B,
	kExtraData_PersistentCell = 0x0C,
	kExtraData_Script = 0x0D,
	kExtraData_Action = 0x0E,
	kExtraData_StartingPosition = 0x0F,
	kExtraData_Anim = 0x10,
	kExtraData_UsedMarkers = 0x12,
	kExtraData_DistantData = 0x13,
	kExtraData_RagdollData = 0x14,
	kExtraData_ContainerChanges = 0x15,
	kExtraData_Worn = 0x16,
	kExtraData_WornLeft = 0x17,
	kExtraData_PackageStartLocation = 0x18,
	kExtraData_Package = 0x19,
	kExtraData_TrespassPackage = 0x1A,
	kExtraData_RunOncePacks = 0x1B,
	kExtraData_ReferencePointer = 0x1C,
	kExtraData_Follower = 0x1D,
	kExtraData_LevCreaModifier = 0x1E,
	kExtraData_Ghost = 0x1F,
	kExtraData_OriginalReference = 0x20,
	kExtraData_Ownership = 0x21,
	kExtraData_Global = 0x22,
	kExtraData_Rank = 0x23,
	kExtraData_Count = 0x24,
	kExtraData_Health = 0x25,
	kExtraData_Uses = 0x26,
	kExtraData_TimeLeft = 0x27,
	kExtraData_Charge = 0x28,
	kExtraData_Light = 0x29,
	kExtraData_Lock = 0x2A,
	kExtraData_Teleport = 0x2B,
	kExtraData_MapMarker = 0x2C,
	kExtraData_LeveledCreature = 0x2E,
	kExtraData_LeveledItem = 0x2F,
	kExtraData_Scale = 0x30,
	kExtraData_Seed = 0x31,
	kExtraData_NonActorMagicCaster = 0x32,
	kExtraData_NonActorMagicTarget = 0x33,
	kExtraData_PlayerCrimeList = 0x35,
	kExtraData_EnableStateParent = 0x37,
	kExtraData_EnableStateChildren = 0x38,
	kExtraData_ItemDropper = 0x39,
	kExtraData_DroppedItemList = 0x3A,
	kExtraData_RandomTeleportMarker = 0x3B,
	kExtraData_MerchantContainer = 0x3C,
	kExtraData_SavedHavokData = 0x3D,
	kExtraData_CannotWear = 0x3E,
	kExtraData_Poison = 0x3F,
	kExtraData_Unk040 = 0x40,	// referenced during LoadFormInModule (in oposition to kExtraData_Light)
	kExtraData_LastFinishedSequence = 0x41,
	kExtraData_SavedAnimation = 0x42,
	kExtraData_NorthRotation = 0x43,
	kExtraData_XTarget = 0x44,
	kExtraData_FriendHits = 0x45,
	kExtraData_HeadingTarget = 0x46,
	kExtraData_RefractionProperty = 0x48,
	kExtraData_StartingWorldOrCell = 0x49,
	kExtraData_Hotkey = 0x4A,
	kExtraData_EditorRefMovedData = 0x4C,
	kExtraData_InfoGeneralTopic = 0x4D,
	kExtraData_HasNoRumors = 0x4E,
	kExtraData_Sound = 0x4F,
	kExtraData_TerminalState = 0x50,
	kExtraData_LinkedRef = 0x51,
	kExtraData_LinkedRefChildren = 0x52,
	kExtraData_ActivateRef = 0x53,
	kExtraData_ActivateRefChildren = 0x54,
	kExtraData_TalkingActor = 0x55,
	kExtraData_ObjectHealth = 0x56,
	kExtraData_DecalRefs = 0x57,
	kExtraData_CellImageSpace = 0x59,
	kExtraData_NavMeshPortal = 0x5A,
	kExtraData_ModelSwap = 0x5B,
	kExtraData_Radius = 0x5C,
	kExtraData_Radiation = 0x5D,
	kExtraData_FactionChanges = 0x5E,
	kExtraData_DismemberedLimbs = 0x5F,
	kExtraData_MultiBound = 0x61,
	kExtraData_MultiBoundData = 0x62,
	kExtraData_MultiBoundRef = 0x63,
	kExtraData_ReflectedRefs = 0x65,
	kExtraData_ReflectorRefs = 0x66,
	kExtraData_EmittanceSource = 0x67,
	kExtraData_RadioData = 0x68,
	kExtraData_CombatStyle = 0x69,
	kExtraData_Primitive = 0x6B,
	kExtraData_OpenCloseActivateRef = 0x6C,
	kExtraData_AnimNoteReciever = 0x6D,
	kExtraData_Ammo = 0x6E,
	kExtraData_PatrolRefData = 0x6F,
	kExtraData_PackageData = 0x70,
	kExtraData_OcclusionPlane = 0x71,
	kExtraData_CollisionData = 0x72,
	kExtraData_SayTopicInfoOnceADay = 0x73,
	kExtraData_EncounterZone = 0x74,
	kExtraData_SayToTopicInfo = 0x75,
	kExtraData_OcclusionPlaneRefData = 0x76,
	kExtraData_PortalRefData = 0x77,
	kExtraData_Portal = 0x78,
	kExtraData_Room = 0x79,
	kExtraData_HealthPerc = 0x7A,
	kExtraData_RoomRefData = 0x7B,
	kExtraData_GuardedRefData = 0x7C,
	kExtraData_CreatureAwakeSound = 0x7D,
	kExtraData_WaterZoneMap = 0x7E,
	kExtraData_IgnoredBySandbox = 0x80,
	kExtraData_CellAcousticSpace = 0x81,
	kExtraData_ReservedMarkers = 0x82,
	kExtraData_WeaponIdleSound = 0x83,
	kExtraData_WaterLightRefs = 0x84,
	kExtraData_LitWaterRefs = 0x85,
	kExtraData_WeaponAttackSound = 0x86,
	kExtraData_ActivateLoopSound = 0x87,
	kExtraData_PatrolRefInUseData = 0x88,
	kExtraData_AshPileRef = 0x89,
	kExtraData_CreatureMovementSound = 0x8A,
	kExtraData_FollowerSwimBreadcrumbs = 0x8B,
	//										= 0x8C,
	kExtraData_WeaponModFlags = 0x8D,
	//
	kExtraData_0x90 = 0x90,	// referenced in LoadGame but no data
	kExtraData_0x91 = 0x91,	// referenced in LoadGame but no data
	kExtraData_SpecialRenderFlags = 0x92
};

class BSExtraData {
public:
	BSExtraData();
	~BSExtraData();

	virtual bool Differs(BSExtraData* extra);	// 001

	static BSExtraData* Create(UInt8 xType, UInt32 size, UInt32 vtbl);

	UInt8		type;		// 004
	BSExtraData* next;		// 008
};

struct BaseExtraList {
	bool HasType(UInt32 type) const;

	__forceinline BSExtraData* GetByType(UInt8 type) const
	{
		return ThisStdCall<BSExtraData*>(0x410220, this, type);
	}

	void MarkType(UInt32 type, bool bCleared);

	__forceinline void Remove(BSExtraData* toRemove, bool doFree)
	{
		ThisStdCall(0x410020, this, toRemove, doFree);
	}

	__forceinline void RemoveByType(UInt32 type)
	{
		ThisStdCall(0x410140, this, type);
	}

	__forceinline BSExtraData* Add(BSExtraData* toAdd)
	{
		return ThisStdCall<BSExtraData*>(0x40FF60, this, toAdd);
	}

	__forceinline void RemoveAll(bool doFree)
	{
		ThisStdCall(0x40FAE0, this, doFree);
	}

	bool MarkScriptEvent(UInt32 eventMask, TESForm* eventTarget);

	__forceinline void Copy(BaseExtraList* from)
	{
		ThisStdCall(0x411EC0, this, from);
	}

	void DebugDump() const;

	bool IsWorn();

	void** m_vtbl;					// 000
	BSExtraData* m_data;					// 004
	UInt8		m_presenceBitfield[0x15];	// 008 - if a bit is set, then the extralist should contain that extradata
	// bits are numbered starting from the lsb
	UInt8		pad1D[3];					// 01D
};


ASSERT_OFFSET(BaseExtraList, m_presenceBitfield, 0x008);