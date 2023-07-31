#pragma once

#include "MobileObject.hpp"
#include "ActorValueOwner.hpp"
#include "CachedValuesOwner.hpp"
#include "MagicCaster.hpp"
#include "MagicTarget.hpp"
#include "ExtraContainerChanges.hpp"
#include "NiVector3.hpp"

class ActorMover;
class BGSPerk;
class bhkRagdollController;
class bhkRagdollPenetrationUtil;
class TESActorBase;
class ContinuousBeamProjectile;
class TESPackage;

typedef std::vector<TESForm*> EquippedItemsList;

class Actor : public MobileObject {
public:
	Actor();
	~Actor();

	virtual void		Unk_C1(void);
	virtual void		Unk_C2(void);
	virtual void		Unk_C3(void);
	virtual void		Unk_C4(void);
	virtual void		Unk_C5(void);
	virtual void		Unk_C6(void);
	virtual void		Unk_C7(void);
	virtual void		Unk_C8(void);
	virtual void		Unk_C9(void);
	virtual void		Unk_CA(void);
	virtual void		Unk_CB(void);
	virtual void		Unk_CC(void);
	virtual void		Unk_CD(void);
	virtual void		Unk_CE(void);
	virtual void		Unk_CF(void);
	virtual void		Unk_D0(void);
	virtual void		Unk_D1(void);
	virtual void		Unk_D2(void);
	virtual void		Unk_D3(void);
	virtual void		Unk_D4(void);
	virtual void		Unk_D5(void);
	virtual void		Unk_D6(void);
	virtual void		Unk_D7(void);
	virtual void		Unk_D8(void);	// IsPlayerRef
	virtual void		Unk_D9(void);
	virtual void		Unk_DA(void);
	virtual void		Unk_DB(void);
	virtual void		Unk_DC(void);
	virtual void		Unk_DD(void);
	virtual void		Unk_DE(void);
	virtual void		Unk_DF(void);
	virtual void		Unk_E0(void);
	virtual void		SetRefraction(bool, float);
	virtual void		Unk_E2(void);
	virtual void		Unk_E3(void);
	virtual void		Unk_E4(void);	// Creature = 0, Character = 1, PlayerCharacter = 2
	virtual void		Unk_E5(void);
	virtual void		Unk_E6(void);
	virtual void		Unk_E7(void);
	virtual void		Unk_E8(void);
	virtual void		Unk_E9(void);
	virtual void		Unk_EA(void);
	virtual void		Unk_EB(void);
	virtual void		Unk_EC(void);
	virtual void		Unk_ED(void);
	virtual void		Unk_EE(void);
	virtual void		Unk_EF(void);
	virtual void		Unk_F0(void);
	virtual void		Unk_F1(void);
	virtual void		Unk_F2(void);
	virtual void		Unk_F3(void);
	virtual void		Unk_F4(void);
	virtual void		Unk_F5(void);
	virtual void		Unk_F6(void);
	virtual void		Unk_F7(void);
	virtual void		Unk_F8(void);	// 0F8 bool AddSpell(spell)
	virtual void		Unk_F9(void);
	virtual void		Unk_FA(void);
	virtual void		Unk_FB(void);
	virtual void		Unk_FC(void);
	virtual void		Unk_FD(void);
	virtual void		Unk_FE(void);
	virtual void		Unk_FF(void);
	virtual void		Unk_100(void);
	virtual void		Unk_101(void);
	virtual void		Unk_102(void);
	virtual void		Unk_103(void);
	virtual void		Unk_104(void);
	virtual void		Unk_105(void);
	virtual void		Unk_106(void);
	virtual float		GetAlpha(void);
	virtual void		Unk_108(void);
	virtual void		Unk_109(void);
	virtual bool		IsInCombat(void);
	virtual Actor* GetCombatTarget(void);
	virtual void		Unk_10C(void);
	virtual void		Unk_10D(void);
	virtual void		Unk_10E(void);
	virtual void		Unk_10F(void);
	virtual void		Unk_110(void);
	virtual void		Unk_111(void);
	virtual void		Unk_112(void);
	virtual void		Unk_113(void);
	virtual void		Unk_114(void);
	virtual void		Unk_115(void);
	virtual void		Unk_116(void);
	virtual void		Unk_117(void);
	virtual void		Unk_118(void);
	virtual void		Unk_119(void);
	virtual void		Unk_11A(void);
	virtual void		Unk_11B(void);
	virtual void		Unk_11C(void);
	virtual void		Unk_11D(void);
	virtual void		Unk_11E(void);
	virtual void		Unk_11F(void);
	virtual void		Unk_120(void);
	virtual void		Unk_121(void);
	virtual void		Unk_122(void);	//	0122	Check for LevelUp
	virtual void		Unk_123(void);
	virtual void		Unk_124(void);
	virtual void		Unk_125(void);
	virtual void		SetPerkRank(BGSPerk* perk, UInt8 rank, bool alt);
	virtual void		Unk_127(void);
	virtual UInt8		GetPerkRank(BGSPerk* perk, bool alt);
	virtual void		Unk_129(void);
	virtual void		Unk_12A(void);
	virtual void		Unk_12B(void);
	virtual void		Unk_12C(void);
	virtual void		Unk_12D(void);
	virtual void		Unk_12E(void);
	virtual void		Unk_12F(void);
	virtual void		Unk_130(void);
	virtual void		Unk_131(void);
	virtual void		Unk_132(void);
	virtual void		Unk_133(void);
	virtual void		Unk_134(void);
	virtual void		Unk_135(void);
	virtual void		Unk_136(void);

	struct Disposition
	{
		UInt32 disposition;
		UInt32 target;
	};

	typedef BSSimpleList<Disposition*> DispositionList;

	MagicCaster magicCaster;
	MagicTarget magicTarget;
	ActorValueOwner avOwner;
	CachedValuesOwner cvOwner;
	bhkRagdollController* ragDollController;
	bhkRagdollPenetrationUtil* ragDollPentrationUtil;
	UInt32 unk0B4;
	float flt0B8;
	UInt8 IsAIProcessing;
	UInt8 byte0BD;
	UInt8 byte0BE;
	UInt8 byte0BF;
	Actor* killer;
	UInt8 byte0C4;
	UInt8 byte0C5;
	UInt8 byte0C6;
	UInt8 byte0C7;
	float time0C8;
	float fCheckDeadBodyTimer;
	void* forceAVList[2];
	UInt8 byte0D8;
	UInt8 byte0D9;
	UInt8 byte0DA;
	UInt8 byte0DB;
	UInt32 unk0DC;
	void* setAVList[2];
	UInt8 byte0E8;
	UInt8 byte0E9;
	UInt8 byte0EA;
	UInt8 byte0EB;
	UInt32 unk0EC;
	UInt8 byte0F0;
	UInt8 byte0F1;
	UInt8 byte0F2;
	UInt8 byte0F3;
	void* list0F4[2];
	Actor::DispositionList dispositions;
	bool isInCombat;
	UInt8 jipActorFlags1;
	UInt8 jipActorFlags2;
	UInt8 jipActorFlags3;
	UInt32 lifeState;
	UInt32 criticalStage;
	UInt32 queuedAttackAnim;
	float painSoundTimer;
	UInt8 byte118;
	UInt8 byte119;
	UInt16 jip11A;
	UInt32 flags11C;
	UInt32 hoursPassed120;
	bool forceRun;
	bool forceSneak;
	UInt8 byte126;
	UInt8 hasSearch;
	Actor* combatTarget;
	Actor** combatTargets;
	Actor** combatAllies;
	UInt8 byte134;
	UInt8 byte135;
	UInt16 jip136;
	UInt32 unk138;
	UInt32 minorCrimeCount;
	UInt32 actorFlags;
	bool ignoreCrime;
	UInt8 byte145;
	UInt8 isResetAI;
	UInt8 byte147;
	TESActorBase* actorbase148;
	UInt8 inWater;
	UInt8 isSwimming;
	UInt8 byte14E;
	UInt8 gap14F;
	UInt32 iActionValue;
	float fTimerOnAction;
	float fUpdateTargetTimer;
	UInt8 byte15C;
	UInt8 bShouldRotateToTrack;
	UInt16 jip15E;
	NiVector3 startingPos;
	float flt16C;
	TESForm* startingWorldOrCell;
	UInt8 byte174;
	UInt8 byte175;
	UInt16 jip176;
	float fCachedSpread_Projectile;
	float fCachedSpread_Scoped;
	float fCachedSpread_WeaponModel;
	float fCachedSpread_VATS;
	float flt188;
	UInt8 isCameraRagdollAnimDist;
	bool isTeammate;
	UInt8 byte18E;
	UInt8 byte18F;
	ActorMover* actorMover;
	UInt32 unk194;
	TESPackage* package198;
	float OneMinusRadResist;
	ContinuousBeamProjectile* continuousBeamProjectile;
	UInt32 speechExpression;
	UInt32 emotionValue;
	UInt32 sitSleepState;
	UInt8 isTurret;
	bool forceHit;
	UInt8 byte1B2;
	UInt8 byte1B3;

	// OBSE: unk1 looks like quantity, usu. 1; ignored for ammo (equips entire stack). In NVSE, pretty much always forced internally to 1
	// OBSE: itemExtraList is NULL as the container changes entry is not resolved before the call
	// NVSE: Default values are those used by the vanilla script functions.
	void EquipItem(TESForm* objType, UInt32 equipCount = 1, ExtraDataList* itemExtraList = NULL, UInt32 unk3 = 1, bool lockEquip = false, UInt32 unk5 = 1);	// unk3 apply enchantment on player differently
	void UnequipItem(TESForm* objType, UInt32 unequipCount = 1, ExtraDataList* itemExtraList = NULL, UInt32 unk3 = 1, bool lockEquip = false, UInt32 unk5 = 1);
	bool IsInReloadAnim();
	bool IsWeaponOut();
	bool IsAiming();
	bool HasExtraRefractionProperty();

	EquippedItemsList	GetEquippedItems();
	ExtraContainerDataArray	GetEquippedEntryDataList();
	ExtraContainerExtendDataArray GetEquippedExtendDataList();
	TESObjectWEAP* GetEquippedWeapon();
};