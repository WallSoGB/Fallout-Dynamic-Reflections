#pragma once

#include "ExtraContainerChanges.hpp"
#include "TESChildCell.hpp"
#include "ExtraDroppedItemList.hpp"

class ExtraScript;
class NiNode;
struct ScriptEventList;
class TESContainer;
class TESSound;
struct AnimData;
struct BipedAnim;
class NiGeometry;

struct LoadedRefData {
	TESObjectREFR* pCurrentWaterType;
	UInt32 iUnderwaterCount;
	float fRelevantWaterHeight;
	float revealDistance;
	UInt32 flags;
	NiNodePtr spNode;
	NiNode* niNode18;
};

class TESObjectREFR : public TESForm {
public:
	MEMBER_FN_PREFIX(TESObjectREFR);

	TESObjectREFR();
	~TESObjectREFR();

	virtual void		GetStartingPosition(void);	// GetStartingPosition(Position, Rotation, WorldOrCell)
	virtual void		VoiceSoundFunction(void);
	virtual void		Unk_50(void);
	virtual void		DamageObject(void);
	virtual bool		IsCastShadows(void);
	virtual void		SetCastShadows(void);
	virtual void		Unk_54(void);
	virtual void		Unk_55(void);
	virtual void		Unk_56(void);
	virtual void		IsObstacle(void);
	virtual void		IsQuestObject(void);
	virtual void		Unk_59(void);
	virtual void		Unk_5A(void);
	virtual void		GetStartingAngle(void);
	virtual void		GetStartingPos(void);
	virtual void		Unk_5D(void);
	virtual void		UpdateLight(void);
	virtual TESObjectREFR* RemoveItem(TESForm* toRemove, BaseExtraList* extraList, UInt32 count, UInt32 unk3, UInt32 unk4, TESObjectREFR* destRef,
		UInt32 unk6, UInt32 unk7, UInt32 unk8, UInt8 unk9);	// 40 unk2 quantity? Returns the reference assigned to the removed item.
	virtual void		Unk_60(void);
	virtual void		LoadEquipedItem(void);	// Linked to AddItem, (item, count, ExtraDataList), func0042 in OBSE
	virtual void		Unk_62(void);	// Linked to Unequip (and or equip maybe)
	virtual void		Unk_63(void);
	virtual void		AddItem(TESForm* item, ExtraDataList* xDataList, UInt32 Quantity);	// Needs confirmation
	virtual void		Unk_65(void);
	virtual void		Unk_66(void);
	virtual void		Unk_67(void);					// Actor: GetMagicEffectList
	virtual bool		GetIsChildSize(bool checkHeight);		// 068 Actor: GetIsChildSize
	virtual UInt32		GetActorUnk0148(void);			// result can be interchanged with baseForm, so TESForm* ?
	virtual void		SetActorUnk0148(UInt32 arg0);
	virtual void		GetBSFaceGenNiNodeBiped(void);
	virtual void		GetBSFaceGenNiNodeSkinned(void);	// REFR: GetBSFaceGenNiNodeSkinned
	virtual void		GetBSFaceGenNiNodeSkinned_(void);	// REFR: calls 006C
	virtual void		CreateFaceAnimationData(void);	// MobileActor: calls 006D then NiNode::Func0040
	virtual void		Unk_6F(void);
	virtual void		Unk_70(void);
	virtual void		InitHavok(void);					// same in FOSE ! identical to Func0052 in OBSE which says (inits animation-related data, and more)
	virtual void		GenerateNiNode(bool arg0);				// same in FOSE !
	virtual void		Set3D(NiNode* niNode, bool unloadArt);	// same in FOSE !
	virtual NiNode*		Get3D(void);						// same in FOSE !
	virtual void		Unk_75(void);
	virtual void		Unk_76(void);
	virtual void		GetMaxBounds(void);
	virtual void		UpdateAnimation(void);
	virtual AnimData* GetAnimData(void);			// 0079
	virtual BipedAnim* GetValidBip01Names(void);	// 007A	Character only
	virtual BipedAnim* CallGetBipedAnim(void);
	virtual void		SetValidBip01Names(BipedAnim validBip01Names);
	virtual NiPoint3* GetPos(void) const;				// GetPos or GetDistance
	virtual void		Unk_7E(UInt32 arg0);
	virtual void		Unk_7F(void);
	virtual void		Unk_80(UInt32 arg0);
	virtual void		Unk_81(UInt32 arg0);
	virtual void		Unk_82(void);
	virtual NiNode*		GetProjectileNode(void);
	virtual void		Unk_84(UInt32 arg0);
	virtual UInt32		Unk_85(void);			// 0 or GetActor::Unk01AC
	virtual bool		IsCharacter(void);			// return false for Projectile, Actor and Creature, true for character and PlayerCharacter
	virtual bool		IsCreature(void);			// seems to always return 0
	virtual bool		IsExplosion(void);			// seems to always return 0
	virtual void		IsProjectile(void);
	virtual void		SetParentCell(void);			// SetParentCell (Interior only ?)
	virtual bool		IsDying(bool);			// IsDead = IsDying (baseForm health <= 0 or Flags bit23 set)
	virtual bool		GetHasKnockedState(void);
	virtual bool		Unk_8D(void);
	virtual void		Unk_8E(void);
	virtual void		GetExtraDataAnimNoteReceiver(void);

	enum {
		kFlags_Unk00000002 = 0x00000002,
		kFlags_Deleted = 0x00000020,		// refr removed from .esp or savegame
		kFlags_Persistent = 0x00000400,		//shared bit with kFormFlags_QuestItem
		kFlags_Temporary = 0x00004000,
		kFlags_Taken = kFlags_Deleted | kFlags_Unk00000002,

		kChanged_Inventory = 0x08000000,
	};

#ifdef EDITOR
	EditorData	editorData;			// +04
#endif
	TESChildCell* pChildCell;
	TESSound* pLoopSound;
	TESForm* pObjectReference;
	NiPoint3 Rotation;
	NiPoint3 Position;
	float fRefScale;
	TESObjectCELL* pParentCell;
	ExtraDataList ExtraList;
	LoadedRefData* pLoadedData;

	ExtraScript* GetExtraScript() const;
	ScriptEventList* GetEventList() const;

	bool IsTaken() const { return (iFormFlags & kFlags_Taken) != 0; }
	bool IsPersistent() const { return (iFormFlags & kFlags_Persistent) != 0; }
	bool IsTemporary() { return (iFormFlags & kFlags_Temporary) ? true : false; }
	bool IsDeleted() const { return (iFormFlags & kFlags_Deleted) ? true : false; }

	bool Update3D();
	bool Update3D_v1c();	// Less worse version as used by some modders
	TESContainer* GetContainer();
	bool IsMapMarker();
	bool GetInventoryItems(InventoryItemsMap& invItems);
	ExtraDroppedItemList* GetDroppedItems();
	bool GetVisibleWhenDistant();

	double GetHeadingAngle(const TESObjectREFR* to) const;

	static TESObjectREFR* Create(bool bTemp = false);

	const char* GetModelPath();

	__forceinline TESObjectCELL* GetParentCell() const { return pParentCell; }

	static TESObjectREFR* FindReferenceFor3D(NiAVObject* apObject) {
		return CdeclCall<TESObjectREFR*>(0x56F930, apObject);
	}

	TESForm* GetBaseForm();

	MEMBER_FN_PREFIX(TESObjectREFR);
#if RUNTIME
	DEFINE_MEMBER_FN(Activate, bool, 0x00573170, TESObjectREFR*, UInt32, UInt32, UInt32);	// Usage Activate(actionRef, 0, 0, 1); found inside Cmd_Activate_Execute as the last call (190 bytes)
	DEFINE_MEMBER_FN(Set3D, void, 0x0094EB40, NiNode*, bool);	// Usage Set3D(niNode, true); virtual func 0073
#endif
};

TESForm* GetPermanentBaseForm(TESObjectREFR* thisObj);	// For LevelledForm, find real baseForm, not temporary one.

// Taken from JIP LN NVSE.
float __vectorcall GetDistance3D(const TESObjectREFR* ref1, const TESObjectREFR* ref2);

ASSERT_OFFSET(TESObjectREFR, pObjectReference, 0x20);
ASSERT_OFFSET(TESObjectREFR, pParentCell, 0x40);
ASSERT_OFFSET(TESObjectREFR, ExtraList, 0x44);
ASSERT_SIZE(TESObjectREFR, 0x68);