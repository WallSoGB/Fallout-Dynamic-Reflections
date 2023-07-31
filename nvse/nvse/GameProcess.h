
#pragma once

#include "GameExtraData.h"
#include "NiNodes.h"
#include "GameForms.h"
#include "GameTasks.h"

class MagicTarget;
class bhkCharacterController;
struct AnimData;
struct CombatActors;
class TESAmmo;
class TESObjectWEAP;

// Straight from OBSE. Needs to be debugged ! ! ! 
// This is used all over the game code to manage actors and occassionally other objects.
class ActorProcessManager
{
public:
	ActorProcessManager();
	~ActorProcessManager();

	struct ActorList {
		tList<Actor>			head;
		tList<Actor>::_Node		* tail;
	};

	ActorList				middleHighActors;		// 00
	ActorList				lowActors0C;			// 0C significantly smaller list than lowActors18. 
													//	  Plausible: actors currently scheduled for low processing
	ActorList				lowActors18;			// 18
	float					unk24;					// 24
	UInt32					unk28;					// 28
	void					* unk2C;				// 2C
	UInt32					unk30;					// 30
	void					* unk34;				// 34
	UInt32					unk38[0x0A];			// 38
	// almost confirmed to be at index 60
	tList<BSTempEffect>		tempEffects;			// 60
	// needs recalc of offsets
	UInt32					unk4C[4];				// 4C
	tList<Actor>			highActors;				// 5C
	Actor					* actor64;				// 64
	tList<Actor>::_Node		* unkNodes[3];			// 68 ##TODO: which lists do these belong to
	UInt32					unk74;					// 74 Possibly not a member. Definitely no more members following this.
};

extern ActorProcessManager * g_actorProcessManager;

class Projectile;
class Explosion;
class DetectionData;

// 64
struct ActorHitData
{
	enum
	{
		kHitData_IsCritical = 0x4,
		kHitData_IsFatal = 0x10,
		kHitData_ExplodePart = 0x40,
		kHitData_DismemberPart = 0x20,
		kHitData_CripplePart = 0x80,
		kHitData_IsSneakAttackCritical = 0x400,
	};

	Actor* source;		// 00
	Actor* target;		// 04
	union								// 08
	{
		Projectile* projectile;
		Explosion* explosion;
	};
	UInt32				unk0C;			// 0C
	SInt32				hitLocation;	// 10
	float				healthDmg;		// 14
	float				wpnBaseDmg;		// 18	Skill and weapon condition modifiers included
	float				fatigueDmg;		// 1C
	float				limbDmg;		// 20
	float				blockDTMod;		// 24
	float				armorDmg;		// 28
	float				flt2C;			// 2C
	TESObjectWEAP* weapon;		// 30
	float				healthPerc;		// 34
	NiVector3			impactPos;		// 38
	NiVector3			impactAngle;	// 44
	UInt32				unk50;			// 50
	UInt32				unk54;			// 54
	UInt32				flags;			// 58
	float				dmgMult;		// 5C
	UInt32				unk60;			// 60	Unused
};

struct PackageInfo
{
	TESPackage* package;		// 00
	TESPackageData* packageData;	// 04
	TESObjectREFR* targetRef;		// 08
	UInt32			unk0C;			// 0C	Initialized to 0FFFFFFFFh, set to 0 on start
	float			unk10;			// 10	Initialized to -1.0	. Set to GameHour on start so some time
	UInt32			flags;			// 14	Flags, bit0 would be not created and initialized
};

#include "BaseProcess.hpp"

class LowProcess : public BaseProcess
{
public:
	LowProcess();
	~LowProcess();

	struct FloatPair {
		float	flt000;
		float	flt004;
	};

	struct	ActorValueModifier
	{
		UInt8	actorValue;	// 00 Might allow for other values
		UInt8	pad[3];		// 01
		float	damage;		// 04
	};

	struct ActorValueModifiers
	{
		tList<ActorValueModifier>	avModifierList;	// 00
		UInt8						unk008;			// 08
		UInt8						pad009[3];		// 09
		void*						** modifiedAV;	// 0C	array of damaged actorValue
	};	// 10

	virtual void	Unk_1EE();
	virtual void	Unk_1EF();
	virtual void	Unk_1F0();
	virtual void	Unk_1F1();
	virtual void	Unk_1F2();
	virtual void	Unk_1F3();
	virtual void	Unk_1F4();
	virtual void	Unk_1F5();
	virtual void	Unk_1F6();
	virtual void	Unk_1F7();
	virtual void	Unk_1F8();
	virtual void	Unk_1F9();
	virtual void	Unk_1FA();
	virtual void	Unk_1FB();
	virtual void	Unk_1FC();
	virtual void	Unk_1FD();
	virtual void	Unk_1FE();
	virtual void	Unk_1FF();
	virtual void	Unk_200();
	virtual void	Unk_201();
	virtual void	Unk_202();
	virtual void	Unk_203();
	virtual void	Unk_204();
	virtual void	Unk_205();
	virtual void	Unk_206();
	virtual void	Unk_207();

	UInt8				byte30;		// 8 = IsAlerted
	UInt8				pad31[3];
	UInt32				unk34;
	FloatPair			unk38;
	TESForm*			unk40;		// Used when picking idle anims.
	UInt32				unk44;		// not initialized!	refr, expected actor, might be CombatTarget
	UInt32				unk48;
	UInt32				unk4C;
	UInt32				unk50;
	UInt32				unk54;		// not initialized!
	UInt32				unk58;
	UInt32				unk5C;
	tList<UInt32>		unk60;		// List
	UInt32				unk68;
	UInt32				unk6C;
	tList<TESForm>		unk70;
	tList<UInt32>		unk78;
	tList<UInt32>		unk80;
	UInt32				unk88;
	UInt32				unk8C;
	UInt32				unk90;
	UInt32				unk94;
	ActorValueModifiers	damageModifiers;
	float				gameDayDied;
	float				playerDamageDealt; // not initialized!
	UInt32				unkB0;		// not initialized!
};
// LowProcess has 207 virtual func


class MiddleLowProcess : public LowProcess
{
public:
	MiddleLowProcess();
	~MiddleLowProcess();

	virtual void	Unk_207();

	UInt32				unk0B4;			// 0B4
	ActorValueModifiers	tempModifiers;	// 0B8
};	// 0C8

// MiddleLowProcess has 208 virtual func, 208 would be SetAnimation

class QueuedFile;
class bhkCharacterController;
class BSFaceGenAnimationData;
class BSBound;
class NiTriShape;

// 25C
class MiddleHighProcess : public MiddleLowProcess
{
public:
	MiddleHighProcess();
	~MiddleHighProcess();

	struct	Unk138 {
		UInt32	unk000;
		UInt32	unk004;		// Semaphore
			// ... ?
	};

	struct	Unk148 {
		UInt32	unk000;
		UInt32	unk004;
		UInt32	unk008;
		UInt16	unk00C;
		UInt8	unk00E;
		UInt8	fil00F;
	};

	virtual void	SetAnimation(UInt32 newAnimation);
	virtual void	Unk_209();
	virtual void	Unk_20A();
	virtual void	Unk_20B();
	virtual void	Unk_20C();
	virtual void	Unk_20D();
	virtual void	Unk_20E();
	virtual void	Unk_20F();
	virtual void	Unk_210();
	virtual void	Unk_211();
	virtual void	Unk_212();
	virtual void	Unk_213();
	virtual void	Unk_214();
	virtual void	Unk_215();
	virtual void	Unk_216();
	virtual void	Unk_217();
	virtual void	Unk_218();
	virtual void	Unk_219();
	virtual void	Unk_21A();
	virtual void	Unk_21B();

	tList<TESForm>						unk0C8;				// 0C8
	tList<UInt32>						unk0D0;				// 0D0
	UInt32								unk0D8[3];			// 0D8
	PackageInfo							interruptPackage;	// 0E4
	UInt8								unk0FC[12];			// 0FC	Saved as one, might be Pos/Rot given size
	UInt32								unk108;				// 108
	TESIdleForm							*idleForm10C;		// 10C
	UInt32								unk110;				// 110  EntryData, also handled as part of weapon code. AmmoInfo.
	WeaponInfo							*weaponInfo;		// 114
	AmmoInfo							*ammoInfo;			// 118
	QueuedFile							*unk11C;			// 11C
	UInt8								byt120;				// 120
	UInt8								byt121;				// 121
	UInt8								byt122;				// 122
	UInt8								fil123;				// 123
	UInt8								isUsingOneHandGrenade;
	UInt8								isUsingOneHandMine;
	UInt8								isUsingOneHandThrown;
	UInt8								isWearingHeavyArmor;
	UInt8								isWearingPowerArmorTorso;
	UInt8								isWearingPowerArmorHelmet;
	UInt8								isWearingBackpack;
	UInt8								gap12B;
	NiNode								*node12C;			// 12C
	NiNode								*projectileNode;	// 130
	UInt8								byt134;				// 134
	bool								isWeaponOut;		// 135
	UInt8								byt136;				// 136
	UInt8								byt137;				// 137
	bhkCharacterController				*charCtrl;			// 138
	UInt8								knockedState;		// 13C
	UInt8								unk13D[3];			// 13D
	UInt32								unk140[8];			// 140
	MagicItem							*magicItem160;		// 160
	UInt32								unk164[3];			// 164
	float								actorAlpha;			// 170
	UInt32								unk174;				// 174
	BSFaceGenAnimationData				*unk178;			// 178
	UInt8								byte17C;			// 17C
	UInt8								byte17D;			// 17D
	UInt8								byte17E;			// 17E
	UInt8								byte17F;			// 17F
	UInt32								unk180[3];			// 180
	UInt8								byte18C;			// 18C
	UInt8								byte18D[3];			// 18D
	UInt32								unk190[10];			// 190
	void								*unk1B8;			// 1B8
	MagicTarget							*magicTarget1BC;	// 1BC
	AnimData							*animData;			// 1C0
	BSAnimGroupSequence					*animSequence[3];	// 1C4
	float								unk1D0;				// 1D0
	float								unk1D4;				// 1D4
	UInt8								byte1D8;			// 1D8
	UInt8								byte1D9;			// 1D9
	UInt8								gap1DA[2];			// 1DA
	NiNode								*limbNodes[15];		// 1DC
	NiNode								*unk218;			// 218
	NiNode								*weaponNode;		// 21C
	void								*ptr220;			// 220
	BSBound								*boundingBox;		// 224
	UInt8								isAiming;			// 228
	UInt8								byte229;			// 229
	UInt16								byte22A;			// 22A
	UInt32								unk22C;				// 22C
	tList<void>							queuedEquipItems;	// 230
	float								rads238;			// 238
	float								waterRadsSec;		// 23C
	ActorHitData						*lastHitData;		// 240 - last damage taken by actor
	UInt32								unk244;				// 244
	BSFaceGenNiNode						*unk248;			// 248
	BSFaceGenNiNode						*unk24C;			// 24C
	NiTriShape							*unk250;			// 250
	ActorHitData						*lastTargetHitData; // 254 - last damage dealt by actor
	UInt32								unk258;				// 258
};
STATIC_ASSERT(sizeof(MiddleHighProcess) == 0x25C);

// MiddleHighProcess has 21B virtual func

// HighProcess: 	// something in wrd2EC and unk2F0, Unk039C count the actor targeting the player (in the player process).
	// Byt0410[6] presence of data in Unk03F8[6], referenced during StopCombat, Byt413, Byt0420, Unk0413, Unk041C

	////virtual void	Unk_21C();
	////virtual void	Unk_21D();

class bhkShapePhantom;
class ProjectileData;
class DetectionEvent;
class NiBSplineCompTransformInterpolator;
class NiBSBoneLODController;

// 46C
class HighProcess : public MiddleHighProcess
{
public:
	HighProcess();
	~HighProcess();

	enum
	{
		kAnimAction_None = -1,
		kAnimAction_Equip_Weapon,
		kAnimAction_Unequip_Weapon,
		kAnimAction_Attack,
		kAnimAction_Attack_Follow_Through,
		kAnimAction_Attack_Latency,
		kAnimAction_Attack_Throw_Attach,
		kAnimAction_Attack_Throw_Release,
		kAnimAction_Block,
		kAnimAction_Stagger,
		kAnimAction_Reload,
		kAnimAction_Dodge,
		kAnimAction_Wait_For_Lower_Body_Anim,
		kAnimAction_Wait_For_Special_Idle,
		kAnimAction_Force_Script_Anim
	};

	enum
	{
		kSitSleepState_Normal = 0x0,
		kSitSleepState_LoadSitIdle = 0x1,
		kSitSleepState_WantToSit = 0x2,
		kSitSleepState_WaitingForSitAnim = 0x3,
		kSitSleepState_Sitting = 0x4,
		kSitSleepState_WantToStand = 0x5,
		kSitSleepState_LoadingSleepIdle = 0x6,
		kSitSleepState_WantToSleep = 0x7,
		kSitSleepState_WaitingForSleepAnim = 0x8,
		kSitSleepState_Sleeping = 0x9,
		kSitSleepState_WantToWake = 0xA,
	};

	struct ActorValueArray
	{
		struct Value
		{
			UInt8 isModified;
			UInt8 gap01[3];
			float value;
		};

		Value avs[77];
	};

	tList<DetectionData>* detectedActors;	// 25C
	tList<DetectionData>* detectingActors;	// 260
	void* ptr264;			// 264
	void* ptr268;			// 268
	void* ptr26C;			// 26C
	UInt32								unk270;				// 270
	tList<void>					combatTargetList274;			// 274
	tList<void>							list27C;			// 27C
	tList<void>							list284;			// 284
	tList<void>							list28C;			// 28C
	float								flt294;				// 294
	float								flt298;				// 298
	UInt32								unk29C;				// 29C
	float								flt2A0;				// 2A0
	UInt32								unk2A4;				// 2A4
	float								flt2A8;				// 2A8
	UInt32								unk2AC;				// 2AC
	float								alpha;				// 2B0
	float								flt2B4;				// 2B4
	float								flt2B8;				// 2B8
	float								flt2BC;				// 2BC
	UInt32								unk2C0;				// 2C0
	UInt8								byte2C4;			// 2C4
	UInt8								byte2C5;			// 2C5
	UInt8								byte2C6;			// 2C6
	UInt8								byte2C7;			// 2C7
	float								flt2C8;				// 2C8
	UInt32								unk2CC;				// 2CC
	float								flt2D0;				// 2D0
	float								flt2D4;				// 2D4
	float								flt2D8;				// 2D8
	UInt32								unk2DC;				// 2DC
	float								flt2E0;				// 2E0
	NiBSBoneLODController* ptr2E4;			// 2E4
	UInt32								unk2E8;				// 2E8
	SInt16								currentAction;		// 2EC
	UInt8								pad2EE[2];			// 2EE
	BSAnimGroupSequence* currentSequence;	// 2F0
	UInt8 forceFireWeapon;
	UInt8 gap2F5[3];
	float								flt2F8;				// 2F8
	UInt32								unk2FC[5];			// 2FC
	float								flt310;				// 310
	UInt32								unk314[7];			// 314
	float								flt330;				// 330
	float								flt334;				// 334
	float								flt338;				// 338
	float								diveBreath;			// 33C
	UInt32								unk340;				// 340
	float								flt344;				// 344
	UInt8								byte348;			// 348
	UInt8								bWeaponAlertDrawn;	// 349
	UInt8								gap34A;				// 34A
	UInt8								gap34B;				// 34B
	float								fAwarePlayerTimer;	// 34C
	TESIdleForm							*idleForm350;		// 350
	UInt32								unk354[4];			// 354
	NiBSplineCompTransformInterpolator** ptr364;			// 364
	UInt32 unk368;
	UInt32 unk36C;
	UInt32 unk370;
	UInt8 isContinuingPackagePCNear;
	UInt8 gap375[3];
	float								flt378;				// 378
	float								flt37C;				// 37C
	UInt32								unk380;				// 380
	float								flt384;				// 384
	float								flt388;				// 388
	tList<void>							list38C;			// 38C
	tList<void>							list394;			// 394
	UInt32								unk39C;				// 39C
	UInt32								unk3A0;				// 3A0
	float								flt3A4;				// 3A4
	UInt32								unk3A8[5];			// 3A8
	float								flt3BC;				// 3BC
	float								flt3C0;				// 3C0
	float								lightAmount;		// 3C4
	float								flt3C8;				// 3C8
	UInt32								unk3CC;				// 3CC
	UInt32								unk3D0;				// 3D0
	ProjectileData* projData;			// 3D4
	UInt32								unk3D8;				// 3D8
	DetectionEvent* detectionEvent;	// 3DC
	UInt32								unk3E0;				// 3E0
	UInt32								unk3E4;				// 3E4
	UInt32								fadeType;			// 3E8
	float								delayTime;			// 3EC
	UInt32								unk3F0;				// 3F0
	UInt32								unk3F4;				// 3F4
	UInt32								unk3F8[3];			// 3F8
	Actor* combatTarget;		// 404
	UInt32								unk408[4];			// 408
	float								flt418;				// 418
	TESObjectREFR* packageTarget;		// 41C
	UInt32								unk420;				// 420
	UInt32								queuedIdleFlags;	// 424
	UInt32								unk428;				// 428
	float								flt42C;				// 42C
	UInt32								unk430;				// 430
	bhkShapePhantom* ptr434;			// 434
	UInt32								unk438;				// 438
	float								unk43C;				// 43C
	float								radsSec440;			// 440
	UInt8								plantedExplosive;	// 444
	UInt8								pad445[3];			// 445
	float								flt448;				// 448
	UInt32								unk44C;				// 44C
	float								flt450;				// 450
	UInt32								unk454[6];			// 454
};
STATIC_ASSERT(sizeof(HighProcess) == 0x46C);

class AnimSequenceBase;

// 100+
struct AnimData
{
	struct Unk124
	{
		struct Unk18
		{
			UInt32			unk00[9];
			UInt32			unk24;
		};

		UInt32			unk00[6];
		Unk18* unk18;
	};

	struct Unk128
	{
		UInt32			unk00[11];
		TESIdleForm* idle2C;
	};

	UInt32							unk000;				// 000
	Actor* actor;				// 004
	NiNode* nSceneRoot;		// 008
	NiNode* nBip01;			// 00C
	UInt32							unk010;				// 010
	float							flt014;				// 014
	float							flt018;				// 018
	UInt32							unk01C;				// 01C
	float							flt020;				// 020
	UInt32							unk024;				// 024
	NiNode* nPelvis;			// 028
	NiNode* nBip01Copy;		// 02C
	NiNode* nLForearm;			// 030
	NiNode* nHead;				// 034
	NiNode* nWeapon;			// 038
	UInt32							unk03C[2];			// 03C
	NiNode* nNeck1;			// 044
	UInt32							unk048[5];			// 048
	SInt32							sequenceState1[8];	// 05C
	SInt32							sequenceState2[8];	// 07C
	UInt32							unk09C[12];			// 09C
	float							flt0CC;				// 0CC
	float							flt0D0;				// 0D0
	UInt32							unk0D4;				// 0D4
	NiControllerManager* unk0D8;			// 0D8
	NiTPointerMap<UInt32, AnimSequenceBase>* unk0DC;			// 0DC
	BSAnimGroupSequence* animSequence[8];	// 0E0
	BSAnimGroupSequence* animSeq100;		// 100
	UInt32							unk104;				// 104
	UInt32							unk108;				// 108
	float							flt10C;				// 10C
	float							flt110;				// 110
	float							flt114;				// 114
	float							flt118;				// 118
	float							flt11C;				// 11C
	UInt8							byte120;			// 120
	UInt8							byte121;			// 121
	UInt16							word122;			// 122
	Unk124* unk124;			// 124
	Unk128* unk128;			// 128
};
STATIC_ASSERT(sizeof(AnimData) == 0x12C);

class CombatController;

class CombatProcedure
{
public:
	virtual void	Destroy(bool doFree);
	virtual void	Update(void);
	virtual void	SetCombatController(CombatController* _combatCtrl);
	virtual void	Unk_03(void);
	virtual void	ClearTargettedRefIfEqualTo(TESObjectREFR* targettedRef);
	virtual void	DebugPrint(void);
	virtual void	Unk_06(NiVector3* out, NiVector3* in);
	virtual void	SetLastError_Disarmed(int unused);
	virtual void	Unk_08(int a1);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(int a1, int a2, int a3, int a4);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	SaveGame(int a1);
	virtual void	LoadGame(int a1);
	virtual void	LoadGame2(int a1);

	CombatController* combatCtrl;	// 04
	UInt32* status;		// 08
	char* errorText;		// 0C
};
class PathingCoverLocation;
class UnreachableCoverLocation;
class UnreachableLocation;
class CombatGoal;

// 0C
struct CombatActionInfo
{
	char* name;	// 00
	float		cost;	// 04
	UInt32		unk08;	// 08
};

enum CombatActions
{
	COMBAT_ACTION_ATTACK_RANGED_EXPLOSIVE,
	COMBAT_ACTION_ATTACK_RANGED_EXPLOSIVE_F,
	COMBAT_ACTION_ATTACK_RANGED,
	COMBAT_ACTION_ATTACK_RANGED_FROM_COVER,
	COMBAT_ACTION_ATTACK_GRENADE,
	COMBAT_ACTION_ATTACK_GRENADE_FLUSH_TARG,
	COMBAT_ACTION_ATTACK_GRENADE_FROM_COVER,
	COMBAT_ACTION_ATTACK_MELEE,
	COMBAT_ACTION_ATTACK_HAND_TO_HAND,
	COMBAT_ACTION_MOVE,
	COMBAT_ACTION_MOVE_AND_SWITCH_TO_MELEE,
	COMBAT_ACTION_MOVE_AND_ATTACK_RANGED,
	COMBAT_ACTION_MOVE_AND_ATTACK_RANGED_EX,
	COMBAT_ACTION_MOVE_AND_ATTACK_GRENADE,
	COMBAT_ACTION_DRAW_WEAPON,
	COMBAT_ACTION_SWITCH_WEAPON,
	COMBAT_ACTION_AVOID_THREAT,
	COMBAT_ACTION_SEARCH,
	COMBAT_ACTION_INVESTIGATE,
	COMBAT_ACTION_DODGE,
	COMBAT_ACTION_IGNORE_BLOCKED_TARGET,
	COMBAT_ACTION_FLEE,
	COMBAT_ACTION_ACTIVATE_COMBAT_ITEM,
	COMBAT_ACTION_USE_COMBAT_ITEM,
	COMBAT_ACTION_ACQUIRE_LINE_OF_SIGHT,
	COMBAT_ACTION_HIDE,
	COMBAT_ACTION_APPROACH_TARGET
};

// 2C
class CombatAction
{
public:
	virtual void	IsApplicable(void);
	virtual void	AddProcedureToController(CombatController* combatCtrl, void* a2);
	virtual void	Unk_02(void);
	virtual void	GetCost(CombatController* combatCtrl, int a2);

	tList<void>		list04;		// 04
	tList<void>		list0C;		// 0C
	tList<void>		list14;		// 14
	tList<void>		list1C;		// 1C
	UInt32			actionID;	// 24
	UInt32			unk28;		// 28
};
STATIC_ASSERT(sizeof(CombatAction) == 0x2C);

// 188
class CombatController : public TESPackage
{
public:
	struct Unk09C
	{
		UInt32									unk000[4];	// 000
		TESObjectWEAP* weapon1;	// 010
		TESObjectWEAP* weapon2;	// 014
		TESObjectWEAP* weapon3;	// 018
		TESObjectWEAP* weapon4;	// 01C
		UInt32									unk020;		// 020
		BSSimpleArray<TESObjectWEAP>			arr024;		// 024
		UInt32									unk034[24];	// 034
		float									flt094;		// 094
		UInt32									unk098[11];	// 098
		void* ptr0C4;	// 0C4
		UInt32									unk0C8[17];	// 0C8
		BSSimpleArray<PathingCoverLocation>		arr10C;		// 10C
		UInt32									unk11C[11];	// 11C
		BSSimpleArray<PathingCoverLocation>		arr148;		// 148
		UInt32									unk158[3];	// 158
		BSSimpleArray<UnreachableCoverLocation>	arr164;		// 164
		BSSimpleArray<UnreachableLocation>		arr174;		// 174
		UInt32									unk184[15];	// 184
		Actor* actor1C0;	// 1C0
		CombatController* cmbtCtrl;	// 1C4
		UInt32									unk1C8[25];	// 1C8
	};
	STATIC_ASSERT(sizeof(Unk09C) == 0x22C);

	CombatActors* combatActors;		// 080
	CombatProcedure* combatProcedure1;	// 084
	CombatProcedure* combatProcedure2;	// 088
	BSSimpleArray<CombatProcedure>	combatProcedures;	// 08C
	Unk09C* struct09C;			// 09C
	void* ptr0A0;			// 0A0
	UInt32							unk0A4;				// 0A4
	CombatAction* combatAction;		// 0A8
	CombatGoal* combatGoal;		// 0AC
	UInt32							unk0B0;				// 0B0
	float							flt0B4[2];			// 0B4
	Actor* packageOwner;		// 0BC
	Actor* packageTarget;		// 0C0
	UInt32							unk0C4[2];			// 0C4
	float							flt0CC;				// 0CC
	float							flt0D0;				// 0D0
	UInt8							byte0D4;			// 0D4
	UInt8							byte0D5;			// 0D5
	UInt8							pad0D6[2];			// 0D6
	float							flt0D8;				// 0D8
	float							flt0DC;				// 0DC
	float							flt0E0;				// 0E0
	UInt32							unk0E4[3];			// 0E4
	TESObjectWEAP* weapon;			// 0F0
	TESCombatStyle* combatStyle;		// 0F4
	UInt32							unk0F8[11];			// 0F8
	UInt8							byte124;			// 124
	bool							stopCombat;			// 125
	UInt8							byte126;			// 126
	UInt8							byte127;			// 127
	UInt32							unk128[8];			// 128
	float							flt148;				// 148
	UInt32							unk14C[15];			// 14C
};
STATIC_ASSERT(sizeof(CombatController) == 0x188);