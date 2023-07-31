#pragma once

#include "BaseFormComponent.hpp"
#include "TESFullName.hpp"
#include "BSString.hpp"
#include "BSSimpleList.hpp"
#include "tList.hpp"
#include "TESFile.hpp"

enum FormType {
	kFormType_None = 0,					// 00
	kFormType_TES4,
	kFormType_Group,
	kFormType_GMST,
	kFormType_BGSTextureSet,
	kFormType_BGSMenuIcon,
	kFormType_TESGlobal,
	kFormType_TESClass,
	kFormType_TESFaction,					// 08
	kFormType_BGSHeadPart,
	kFormType_TESHair,
	kFormType_TESEyes,
	kFormType_TESRace,
	kFormType_TESSound,
	kFormType_BGSAcousticSpace,
	kFormType_TESSkill,
	kFormType_EffectSetting,					// 10
	kFormType_Script,
	kFormType_TESLandTexture,
	kFormType_EnchantmentItem,
	kFormType_SpellItem,
	kFormType_TESObjectACTI,
	kFormType_BGSTalkingActivator,
	kFormType_BGSTerminal,
	kFormType_TESObjectARMO,					// 18	inv object
	kFormType_TESObjectBOOK,						// 19	inv object
	kFormType_TESObjectCLOT,					// 1A	inv object
	kFormType_TESObjectCONT,
	kFormType_TESObjectDOOR,
	kFormType_IngredientItem,				// 1D	inv object
	kFormType_TESObjectLIGH,					// 1E	inv object
	kFormType_TESObjectMISC,						// 1F	inv object
	kFormType_TESObjectSTAT,					// 20
	kFormType_BGSStaticCollection,
	kFormType_BGSMovableStatic,
	kFormType_BGSPlaceableWater,
	kFormType_TESGrass,
	kFormType_TESObjectTREE,
	kFormType_TESFlora,
	kFormType_TESFurniture,
	kFormType_TESObjectWEAP,					// 28	inv object
	kFormType_TESAmmo,						// 29	inv object
	kFormType_TESNPC,						// 2A
	kFormType_TESCreature,					// 2B
	kFormType_TESLevCreature,			// 2C
	kFormType_TESLevCharacter,			// 2D
	kFormType_TESKey,						// 2E	inv object
	kFormType_AlchemyItem,				// 2F	inv object
	kFormType_BGSIdleMarker,				// 30
	kFormType_BGSNote,						// 31	inv object
	kFormType_BGSConstructibleObject,		// 32	inv object
	kFormType_BGSProjectile,
	kFormType_TESLevItem,				// 34	inv object
	kFormType_TESWeather,
	kFormType_TESClimate,
	kFormType_TESRegion,
	kFormType_NavMeshInfoMap,						// 38
	kFormType_TESObjectCELL,
	kFormType_TESObjectREFR,				// 3A
	kFormType_Character,						// 3B
	kFormType_Creature,						// 3C
	kFormType_MissileProjectile,						// 3D
	kFormType_GrenadeProjectile,						// 3E
	kFormType_BeamProjectile,						// 3F
	kFormType_FlameProjectile,						// 40
	kFormType_TESWorldSpace,
	kFormType_TESObjectLAND,
	kFormType_NavMesh,
	kFormType_TLOD,
	kFormType_TESTopic,
	kFormType_TESTopicInfo,
	kFormType_TESQuest,
	kFormType_TESIdleForm,						// 48
	kFormType_TESPackage,
	kFormType_TESCombatStyle,
	kFormType_TESLoadScreen,
	kFormType_TESLevSpell,
	kFormType_TESObjectANIO,
	kFormType_TESWaterForm,
	kFormType_TESEffectShader,
	kFormType_TOFT,						// 50	table of Offset (see OffsetData in Worldspace)
	kFormType_BGSExplosion,
	kFormType_BGSDebris,
	kFormType_TESImageSpace,
	kFormType_TESImageSpaceModifier,
	kFormType_BGSListForm,					// 55
	kFormType_BGSPerk,
	kFormType_BGSBodyPartData,
	kFormType_BGSAddonNode,				// 58
	kFormType_ActorValueInfo,
	kFormType_BGSRadiationStage,
	kFormType_BGSCameraShot,
	kFormType_BGSCameraPath,
	kFormType_BGSVoiceType,
	kFormType_BGSImpactData,
	kFormType_BGSImpactDataSet,
	kFormType_TESObjectARMA,						// 60
	kFormType_BGSEncounterZone,
	kFormType_BGSMessage,
	kFormType_BGSRagdoll,
	kFormType_DOBJ,
	kFormType_BGSLightingTemplate,
	kFormType_BGSMusicType,
	kFormType_TESObjectIMOD,					// 67	inv object
	kFormType_TESReputation,				// 68
	kFormType_ContinuousBeamProjectile,						// 69 Continuous Beam
	kFormType_TESRecipe,
	kFormType_TESRecipeCategory,
	kFormType_TESCasinoChips,				// 6C	inv object
	kFormType_TESCasino,
	kFormType_TESLoadScreenType,
	kFormType_MediaSet,
	kFormType_MediaLocationController,	// 70
	kFormType_TESChallenge,
	kFormType_TESAmmoEffect,
	kFormType_TESCaravanCard,				// 73	inv object
	kFormType_TESCaravanMoney,				// 74	inv object
	kFormType_TESCaravanDeck,
	kFormType_BGSDehydrationStage,
	kFormType_BGSHungerStage,
	kFormType_BGSSleepDeprevationStage,	// 78
};

class TESForm : public BaseFormComponent {
public:
	TESForm();
	~TESForm();

	virtual void* Destroy(bool doFree);			// func_00C in GECK ?? I think ??
	virtual void		InitializeData(void);
	virtual void		ClearData(void);
	virtual bool		Unk_07(void);
	virtual bool		LoadForm(TESFile* modInfo);		// func_010 in GECK
	virtual bool		Unk_09(void* arg);					// points to LoadForm on TESForm
	virtual bool		AppendForm(TESFile* modInfo);		// (ie SaveForm + append to modInfo)
	virtual void		SaveForm(void);						// saves in same format as in .esp	//	func_013 in GECK
	// data buffer and buffer size stored in globals when done, doesn't return anything
	virtual bool		LoadForm2(TESFile* modInfo);		// just calls LoadForm
	virtual void		WriteFormInfo(TESFile* modInfo);	// does some saving stuff, then calls Fn0A
	virtual bool		Unk_0E(void* arg);					// prepares a GRUP formInfo
	virtual bool		Sort(TESForm* form);				// returns if the argument is "greater or equal" to this form
	virtual TESForm* CreateForm(void* arg0, void* mapToAddTo);	// makes a new form,
	virtual void		Unk_11(void* arg);
	virtual void		AddChange(UInt32 changedFlags);
	virtual void		RemoveChange(UInt32 changedFlags);
	virtual UInt32		GetSaveSize(UInt32 changedFlags);	// bytes taken by the delta flags for this form, UNRELIABLE, not (always) overriden
	virtual void		AppendSaveLoadFormBuffer(void* arg);					// collect referenced forms?
	virtual void		SaveGame(UInt32 changedFlags);		// Used as part of CopyFromBase with LoadGame.
	virtual void		LoadGame(void* arg);				// load from BGSLoadFormBuffer arg
	virtual void		LoadGame2(UInt32 changedFlags);		// load from TESSaveLoadGame
	virtual void		InitLoadGame(void* arg);
	virtual void		Unk_1A(void* arg0, void* arg1);
	virtual void		Unk_1B(void* arg0, void* arg1);
	virtual void		Revert(UInt32 changedFlags);		// reset changes in form
	virtual void		Unk_1D(void* arg);
	virtual void		Unk_1E(void* arg);
	virtual bool		Unk_1F(void* arg);
	virtual void		Unk_20(void* arg);
	virtual void		FinishLoadGame(void* arg);
	virtual void		InitItem(void);
	virtual UInt32		GetSavedFormType(void);
	virtual void		GetFormDetailedString(BSStringT* apDest);
	virtual bool		IsPermanentOrIsQuestItem(void);
	// Unk_26 though Unk_36 get or set flag bits
	virtual bool		HasTalkedToPC(void);		// 00000040
	virtual bool		GetHavokDeath(void);		// 00010000
	virtual bool		Unk_28(void);		// 00010000
	virtual bool		IsNeedToChangeProcess(void);		// 00020000
	virtual bool		Unk_2A(void);		// 00020000
	virtual bool		GetFlag80000(void);		// 00080000
	virtual bool		GetFlag2000000(void);		// 02000000
	virtual bool		GetFlag40000000(void);		// 40000000
	virtual bool		GetOnLocalMap(void);		// 00000200
	virtual void		SetCastsShadows(bool abShadowCaster);	// 00000200
	virtual bool		Unk_30(void);		// returns false
	virtual void		SetDelete(bool abDeleted);	// 00000020 then calls Fn12 MarkAsModified
	virtual void		SetAltered(bool abAltered);	// 00000002 with a lot of housekeeping
#if RUNTIME
	virtual void		SetQuestItem(bool abQuestIem);
#else
	virtual bool		Unk_33(void);
#endif
	virtual void		SetTalkedToPC(bool abTalkedTo);
	virtual void		SetHavokDeath(bool abDied);
	virtual void		SetNeedToChangeProcess(bool abChange);	// 00020000
	virtual void		Unk_37(void);		// write esp format
	virtual void		readOBNDSubRecord(TESFile* modInfo);	// read esp format
	virtual bool		IsBoundObject(void);
	virtual bool		IsObject(void);
	virtual bool		IsMagicItem(void);
#if RUNTIME
	virtual bool		IsReference() const;
#else
	virtual bool		Unk_3C();
	bool GetIsReference() const { return typeID == kFormType_TESObjectREFR; }
#endif
	virtual bool		IsArmorAddon(void);
	virtual bool		IsActorBase(void);
	virtual bool		IsMobileObject(void) const;
	virtual bool		IsActor(void);
	virtual UInt32		Unk_41(void);
	virtual void		Copy(const TESForm* apCopy);
	virtual bool		Compare(TESForm* apForm);
	virtual bool		BelongsInGroup(void* apGroupFORM);	// Checks the group is valid for the form
	virtual void		CreateGroupData(void* apOutGroupFORM, void* apParentGroup);	// Fills the groupInfo with info valid for the form
	virtual bool		Unk_46(void);
	virtual bool		Unk_47(void);
	virtual bool		Unk_48(UInt32 formType);	// returns if the same FormType is passed in
	virtual bool		Activate(void* arg0, void* arg1, void* arg2, void* arg3, void* arg4);	// looks to be func33 in Oblivion
	virtual void		SetRefID(UInt32 aiID, bool abUpdateFile);
	virtual char* GetName2(void);
	virtual char* GetName(void) const;
	virtual bool		SetEditorID(const char* edid);
	// 4E

	const char* GetEditorID() const;

	struct EditorData {
		BSStringT		editorID;			// 00
		UInt32		vcMasterFormID;		// 08 - Version control 1 (looks to be a refID inside the Version Control master)
		UInt32		vcRevision;			// 0C
	};
	// 10

	enum
	{
		kFormFlags_Initialized = 0x00000008,	// set by TESForm::InitItem()
		kFormFlags_QuestItem = 0x00000400,
		kFormFlags_DontSaveForm = 0x00004000,	// TODO: investigate
		kFormFlags_VisibleWhenDistant = 0x0008000,
		kFormFlags_Compressed = 0x00040000,
	};

	enum
	{
		kModified_Flags = 0x00000001
		//	UInt32	flags;
	};

	UInt8	typeID;					// 004
	UInt8	typeIDPad[3];			// 005
	UInt32	iFormFlags;					// 008
	UInt32	refID;					// 00C
#ifdef EDITOR
	EditorData	editorData;			// +10
#endif
	tList<TESFile> mods;			// 010 ModReferenceList in Oblivion
	// 018 / 028

	// Looks like there is another DWord here, used as a byte: LastLoaded or Active or Selected ?

	TESForm* TryGetREFRParent(void);
	UInt8			GetModIndex() const;
	TESFullName* GetFullName() const;
	const char* GetTheName();
	std::string		GetStringRepresentation() const;

	bool IsWeapon() { return typeID == kFormType_TESObjectWEAP; }
	bool IsArmor() { return typeID == kFormType_TESObjectARMO; }

	// adds a new form to the game (from CloneForm or LoadForm)
	void DoAddForm(TESForm* newForm, bool bPersist = true, bool record = true) const;
	// return a new base form which is the clone of this form
	TESForm* CloneForm(bool bPersist = true) const;
	bool     IsInventoryObject() const;

	bool FormMatches(TESForm* toMatch) const;

	MEMBER_FN_PREFIX(TESForm);
#if RUNTIME
	DEFINE_MEMBER_FN(MarkAsTemporary, void, 0x00484490);	// probably a member of TESForm
#endif
};

ASSERT_SIZE(TESForm, 0x18);