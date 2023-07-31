#pragma once

class Actor;
struct ActorHitData;
class bhkCharacterController;
class DetectionData;
class TESAmmo;
class TESIdleForm;
class TESObjectREFR;
class TESObjectWEAP;
class TESPackage;
class TESPackageData;

class BaseProcess {
public:
	BaseProcess();
	~BaseProcess();

	struct AmmoInfo
	{
		void* unk00;	// 00
		UInt32	count;	// 04
		TESAmmo* ammo;	// 08
		UInt32	unk0C;	// 0C
		UInt32	unk10;	// 10
		UInt32	unk14;	// 14
		UInt32	unk18;	// 18
		UInt32	unk1C;	// 1C
		UInt32	unk20;	// 20
		UInt32	unk24;	// 24
		UInt32	unk28;	// 28
		UInt32	unk2C;	// 2C
		UInt32	unk30;	// 30
		UInt32	unk34;	// 34
		UInt32	unk38;	// 38
		UInt32	unk3C;	// 3C
		UInt32	unk40;	// 40
		TESObjectWEAP* weapon;	// 44
	};

	struct WeaponInfo
	{
		ExtraDataList** xData;
		UInt32			unk04;
		TESObjectWEAP* weapon;

		ExtraDataList* GetExtraData()
		{
			return xData ? *xData : NULL;
		}
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

	struct CachedValues
	{
		enum
		{
			kCached_Radius = 0x1,
			kCached_WidthX = 0x2,
			kCached_WidthY = 0x4,
			kCached_DPS = 0x8,
			kCached_MedicineSkillMult = 0x10,
			kCached_Paralysis = 0x20,
			kCached_HealRate = 0x40,
			kCached_FatigueReturnRate = 0x80,
			kCached_PerceptionCondition = 0x100,
			kCached_EyeHeight = 0x200,
			kCached_SomethingShouldAttack = 0x400,
			kCached_WalkSpeed = 0x1000,
			kCached_RunSpeed = 0x2000,
			kCached_NoCrippledLegs = 0x4000,
			kCached_Height = 0x8000,
			kCached_IsGhost = 0x10000000,
			kCached_Health = 0x20000000,
			kCached_Fatigue = 0x40000000,
			kCached_SurvivalSkillMult = 0x80000000
		};

		float	radius;
		float	widthX;
		float	widthY;
		float	height;
		float	DPS;
		float	medicineSkillMult;
		float	survivalSkillMult;
		float	paralysis;
		float	healRate;
		float	fatigueReturnRate;
		float	perceptionCondition;
		float	eyeHeight;
		SInt32	unk30;
		SInt32	unk34;
		float	walkSpeed;
		float	runSpeedMult;
		UInt8	hasNoCrippledLegs;
		UInt8	pad41[3];
		UInt32	flags;
	};

	enum
	{
		kProcessLevel_High = 0,
		kProcessLevel_MiddleHigh = 1,
		kProcessLevel_MiddleLow = 2,
		kProcessLevel_Low = 3
	};

	virtual void	Destroy(bool noDealloc);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);
	virtual void	Unk_12(void);
	virtual void	Unk_13(void);
	virtual void	Unk_14(void);
	virtual void	Unk_15(void);
	virtual void	Unk_16(void);
	virtual void	Unk_17(void);
	virtual void	Unk_18(void);
	virtual void	Unk_19(void);
	virtual void	Unk_1A(void);
	virtual void	Unk_1B(void);
	virtual void	Unk_1C(void);
	virtual void	Unk_1D(void);
	virtual void	Unk_1E(void);
	virtual void	Unk_1F(void);
	virtual void	Unk_20(void);
	virtual void	Unk_21(void);
	virtual void	Unk_22(void);
	virtual void	Unk_23(void);
	virtual void	Unk_24(void);
	virtual void	Unk_25(void);
	virtual void	Unk_26(void);
	virtual void	Unk_27(void);
	virtual void	Unk_28(void);
	virtual void	Unk_29(void);
	virtual void	Unk_2A(void);
	virtual void	Unk_2B(void);
	virtual void	Unk_2C(void);
	virtual void	Unk_2D(void);
	virtual void	Unk_2E(void);
	virtual void	Unk_2F(void);
	virtual void	Unk_30(void);
	virtual void	Unk_31(void);
	virtual void	Unk_32(void);
	virtual void	Unk_33(void);
	virtual void	Unk_34(void);
	virtual void	Unk_35(void);
	virtual void	Unk_36(void);
	virtual void	Unk_37(void);
	virtual void	Unk_38(void);
	virtual void	Unk_39(void);
	virtual void	Unk_3A(void);
	virtual void	Unk_3B(void);
	virtual void	Unk_3C(void);
	virtual void	Unk_3D(void);
	virtual void	Unk_3E(void);
	virtual void	Unk_3F(void);
	virtual void	Unk_40(void);
	virtual void	Unk_41(void);
	virtual void	Unk_42(void);
	virtual void	Unk_43(void);
	virtual bool	HasCaughtPlayerPickpocketting(void);
	virtual void	Unk_45(void);
	virtual void	Unk_46(void);
	virtual void	Unk_47(void);
	virtual void	Unk_48(void);
	virtual void	Unk_49(void);
	virtual TESForm* GetLowProcess40();
	virtual void	Unk_4B(void);
	virtual void	Unk_4C(void);
	virtual void	Unk_4D(void);
	virtual void	Unk_4E(void);
	virtual void	Unk_4F(void);
	virtual void	Unk_50(void);
	virtual void	Unk_51(void);
	virtual WeaponInfo* GetWeaponInfo();
	virtual AmmoInfo* GetAmmoInfo();
	virtual void	Unk_54(void);
	virtual void	Unk_55(void);
	virtual void	Unk_56(void);
	virtual void	Unk_57(void);
	virtual void	Unk_58(void);
	virtual void	Unk_59(void);
	virtual void	UpdateAmmoInfo(AmmoInfo*);
	virtual void	Unk_5B(void);
	virtual void	Unk_5C(void);
	virtual void	Unk_5D(void);	// Called by 5E with count itemExtraList item
	virtual void	Unk_5E(void);	// EquipItem and UnEquipItem doEquip item count itemExtraList bytes = [equipArgC lockUnequip unk unEquipArcC lockEquip arg14 ] (arg as from Actor::(Un)EquipItem)
	virtual void	Unk_5F(void);
	virtual void	Unk_60(void);
	virtual NiNode* GetProjectileNode();
	virtual void	SetProjectileNode(NiNode* node);
	virtual void	Unk_63(void);
	virtual void	Unk_64(void);
	virtual void	Unk_65(void);
	virtual void	Unk_66(void);
	virtual void	Unk_67(void);
	virtual void	Unk_68(void);
	virtual void	Unk_69(void);
	virtual void	Unk_6A(void);
	virtual void	Unk_6B(void);
	virtual void	Unk_6C(void);
	virtual void	Unk_6D(void);
	virtual AnimData* GetAnimData(void);
	virtual void	Unk_6F(void);
	virtual void	Unk_70(void);
	virtual void	Unk_71(void);
	virtual void	Unk_72(void);
	virtual void	Unk_73(void);
	virtual void	Unk_74(void);
	virtual void	Unk_75(void);
	virtual void	Unk_76(void);
	virtual void	Unk_77(void);
	virtual void	Unk_78(void);
	virtual void	Unk_79(void);
	virtual void	Unk_7A(void);
	virtual void	Unk_7B(void);
	virtual void	Unk_7C(void);
	virtual void	Unk_7D(void);
	virtual void	Unk_7E(void);
	virtual void	Unk_7F(void);
	virtual void	Unk_80(void);
	virtual void	Unk_81(void);
	virtual void	Unk_82(void);
	virtual TESPackage* GetRunOncePackage();
	virtual void	SetInterruptPackage(TESPackage* package, Actor* onActor);
	virtual void	StopInterruptPackage();
	virtual void	Unk_86(void);	// 086 - SetInterruptPackageTargetRef
	virtual void	Unk_87(void);	// 087 - SetInterruptPackageTargetRef
	virtual void	Unk_88(void);	// 088 - IncreaseInterruptPackageUnk00C
	virtual void	Unk_89(void);
	virtual void	Unk_8A(void);
	virtual TESPackage* GetStablePackage();
	virtual void	SetStablePackage(TESPackage* package, Actor* onActor);
	virtual void	StopStablePackage();
	virtual void	Unk_8E(void);
	virtual void	Unk_8F(void);
	virtual void	Unk_90(void);
	virtual void	Unk_91(void);
	virtual void	Unk_92(void);	// Only HighProcess, get Unk0454
	virtual void	Unk_93(void);
	virtual void	Unk_94(void);
	virtual void	Unk_95(void);
	virtual void	Unk_96(void);
	virtual void	Unk_97(void);
	virtual void	Unk_98(void);
	virtual void	Unk_99(void);
	virtual void	Unk_9A(void);
	virtual void	Unk_9B(void);
	virtual TESPackageData* GetRunOncePackageData();
	virtual TESPackageData* GetPackageData();
	virtual void	Unk_9E(void);
	virtual TESPackage* GetCurrentPackage();
	virtual UInt32	GetPackageInfo0C();
	virtual void	Unk_A1();
	virtual void	Unk_A2();
	virtual bhkCharacterController* GetCharacterController();
	virtual void	SetCharacterController(bhkCharacterController* charCtrl);
	virtual void	Unk_A5();
	virtual void	Unk_A6();
	virtual void	Unk_A7();
	virtual void	Unk_A8();
	virtual void	Unk_A9();
	virtual void	Unk_AA();
	virtual void	Unk_AB();
	virtual void	Unk_AC();
	virtual void	Unk_AD();
	virtual void	Unk_AE();
	virtual void	Unk_AF();
	virtual void	Unk_B0();
	virtual void	Unk_B1();
	virtual void	Unk_B2();
	virtual void	Unk_B3();
	virtual void	Unk_B4();
	virtual void	Unk_B5();
	virtual void	Unk_B6();
	virtual void	Unk_B7();
	virtual void	Unk_B8();
	virtual void	Unk_B9();
	virtual void	Unk_BA();
	virtual void	Unk_BB();
	virtual void	Unk_BC();
	virtual void	Unk_BD();
	virtual void	Unk_BE();
	virtual void	SetDiveBreath(float breath);
	virtual float	GetDiveBreath();
	virtual void	Unk_C1();
	virtual void	Unk_C2();
	virtual void	Unk_C3();
	virtual void	Unk_C4();
	virtual void	Unk_C5();
	virtual void	Unk_C6();
	virtual bool	GetAlerted();
	virtual void	SetAlert(bool alert);
	virtual void	Unk_C9();
	virtual void	Unk_CA();
	virtual void	Unk_CB();
	virtual void	Unk_CC();
	virtual void	Unk_CD();
	virtual void	Unk_CE();
	virtual void	Unk_CF();
	virtual void	Unk_D0();
	virtual void	Unk_D1();
	virtual void	Unk_D2();
	virtual void	Unk_D3();
	virtual void	Unk_D4();
	virtual void	Unk_D5();
	virtual void	Unk_D6();
	virtual void	Unk_D7();
	virtual void	Unk_D8();
	virtual void	Unk_D9();
	virtual void	Unk_DA();
	virtual void	Unk_DB();
	virtual void	Unk_DC();
	virtual void	Unk_DD();
	virtual void	Unk_DE();
	virtual void	Unk_DF();
	virtual void	Unk_E0();
	virtual void	Unk_E1();
	virtual void	Unk_E2();
	virtual TESIdleForm* GetIdleForm10C();
	virtual void	SetIdleForm10C(TESIdleForm* idleForm);
	virtual void	StopIdle();
	virtual void	Unk_E6();
	virtual void	Unk_E7();	// float GetActorValue
	virtual void	Unk_E8();
	virtual void	Unk_E9();
	virtual void	Unk_EA();
	virtual void	Unk_EB();
	virtual void	Unk_EC(UInt32 avCode);
	virtual void	Unk_ED();
	virtual void	Unk_EE();
	virtual void	Unk_EF();
	virtual void	Unk_F0();
	virtual void	Unk_F1();
	virtual void	Unk_F2();
	virtual void	Unk_F3();
	virtual void	Unk_F4();
	virtual void	Unk_F5();
	virtual void	Unk_F6();
	virtual void	Unk_F7();
	virtual void	Unk_F8();
	virtual SInt16	GetCurrentAnimAction();
	virtual SInt16	GetCurrentSequence();
	virtual void	Unk_FB();
	virtual void	Unk_FC();
	virtual void	Unk_FD(char);
	virtual bool	IsReadyForAnim();
	virtual void	Unk_FF();
	virtual void	SetIsAiming(bool isAiming);
	virtual bool	IsAiming();
	virtual void	Unk_102();
	virtual SInt32	GetKnockedState();
	virtual void	SetKnockedState(char state);
	virtual void	Unk_105();
	virtual void	PushActorAway(Actor* pushed, float posX, float posY, float posZ, float force);
	virtual void	Unk_107();
	virtual void	Unk_108();
	virtual void	Unk_109();
	virtual void	Unk_10A();
	virtual void	Unk_10B();
	virtual void	Unk_10C();
	virtual void	Unk_10D();
	virtual void	Unk_10E();
	virtual void	Unk_10F();
	virtual void	Unk_110();
	virtual void	Unk_111();
	virtual void	Unk_112();
	virtual void	Unk_113();
	virtual void	Unk_114();
	virtual bool	IsWeaponOut();
	virtual void	SetWeaponOut(Actor* actor, bool weaponOut);
	virtual void	Unk_117();
	virtual void	Unk_118();
	virtual void	Unk_119(Actor* actor);
	virtual void	Unk_11A(UInt32 unk);
	virtual void	Unk_11B();
	virtual void	Unk_11C();
	virtual bool	Unk_11D(UInt32 arg);
	virtual void	Unk_11E();
	virtual void	Unk_11F();
	virtual void	Unk_120();
	virtual void	Unk_121();
	virtual void	Unk_122();
	virtual void	Unk_123();
	virtual void	Unk_124();
	virtual void	Unk_125();
	virtual void	Unk_126();
	virtual void	Unk_127();
	virtual void	Unk_128();
	virtual void	Unk_129();
	virtual void	Unk_12A();
	virtual void	Unk_12B();
	virtual void	Unk_12C();
	virtual void	Unk_12D();
	virtual void	Unk_12E();
	virtual int		GetSitSleepState();
	virtual void	Unk_130();
	virtual void	Unk_131();
	virtual void	Unk_132();
	virtual void	Unk_133();
	virtual void	Unk_134();
	virtual void	Unk_135();
	virtual void	Unk_136();
	virtual void	Unk_137();
	virtual void	Unk_138();
	virtual void	Unk_139();
	virtual void	Unk_13A();
	virtual void	Unk_13B();
	virtual void	Unk_13C();
	virtual void	Unk_13D();
	virtual void	Unk_13E();
	virtual void	Unk_13F(UInt32 unk);
	virtual void	Unk_140();
	virtual DetectionData* GetDetectionData(Actor* target, UInt32 detecting);
	virtual void	Unk_142();
	virtual void	Unk_143();
	virtual void	Unk_144();
	virtual void	Unk_145();
	virtual void	Unk_146();
	virtual void	Unk_147();
	virtual void	Unk_148();
	virtual void	Unk_149();
	virtual void	Unk_14A();
	virtual void	Unk_14B();
	virtual void	Unk_14C();
	virtual void	Unk_14D();
	virtual void	Unk_14E();
	virtual void	Unk_14F();
	virtual void	Unk_150();
	virtual void	Unk_151();
	virtual void	Unk_152();
	virtual void	Unk_153();
	virtual void	Unk_154();
	virtual void	Unk_155();
	virtual void	Unk_156();
	virtual void	Unk_157();
	virtual void	Unk_158();
	virtual void	Unk_159();
	virtual void	Unk_15A();
	virtual void	Unk_15B();
	virtual void	Unk_15C();
	virtual void	Unk_15D();
	virtual void	Unk_15E();
	virtual void	Unk_15F();
	virtual void	Unk_160();
	virtual void	Unk_161();
	virtual void	Unk_162();
	virtual void	Unk_163();
	virtual void	Unk_164();
	virtual void	Unk_165();
	virtual void	Unk_166();
	virtual void	Unk_167();
	virtual void	Unk_168();
	virtual void	Unk_169();
	virtual void	Unk_16A();
	virtual float	GetActorAlpha();
	virtual void	SetActorAlpha(float alpha);
	virtual void	Unk_16D();
	virtual void	Unk_16E();
	virtual void	Unk_16F();
	virtual void	Unk_170();
	virtual void	Unk_171();
	virtual void	Unk_172();
	virtual void	Unk_173();
	virtual void	Unk_174();
	virtual void	Unk_175();
	virtual void	Unk_176();
	virtual void	Unk_177();
	virtual void	Unk_178();
	virtual void	Unk_179();
	virtual void	Unk_17A();
	virtual void	Unk_17B();
	virtual void	Unk_17C();
	virtual void	Unk_17D();
	virtual void	Unk_17E();
	virtual void	Unk_17F();
	virtual void	Unk_180();
	virtual void	Unk_181();
	virtual void	Unk_182();
	virtual void	Unk_183();
	virtual void	Unk_184();
	virtual void	SetQueuedIdleFlags(UInt32 flags);
	virtual UInt32	GetQueuedIdleFlags();
	virtual void	Unk_187();
	virtual void	Unk_188();
	virtual void	Unk_189();
	virtual void	Unk_18A(Actor* actor);
	virtual void	Unk_18B();
	virtual void	Unk_18C();
	virtual void	Unk_18D();
	virtual void	Unk_18E();
	virtual void	Unk_18F();
	virtual void	Unk_190();
	virtual void	Unk_191();
	virtual void	Unk_192(UInt8 unk);
	virtual void	Unk_193();
	virtual void	Unk_194();
	virtual void	Unk_195();
	virtual void	Unk_196();
	virtual void	Unk_197();
	virtual void	Unk_198();
	virtual void	Unk_199();
	virtual void	Unk_19A();
	virtual void	Unk_19B();
	virtual void	Unk_19C();
	virtual void	Unk_19D();
	virtual void	Unk_19E();
	virtual void	Unk_19F();
	virtual void	Unk_1A0();
	virtual void	Unk_1A1();
	virtual void	Unk_1A2();
	virtual void	Unk_1A3();
	virtual void	Unk_1A4();
	virtual void	Unk_1A5();
	virtual void	Unk_1A6();
	virtual void	Unk_1A7();
	virtual void	Unk_1A8();
	virtual void	Unk_1A9();
	virtual void	Unk_1AA();
	virtual void	Unk_1AB();
	virtual void	Unk_1AC();
	virtual void	Unk_1AD();
	virtual void	Unk_1AE();
	virtual void	Unk_1AF();
	virtual void	Unk_1B0();
	virtual void	Unk_1B1();
	virtual void	Unk_1B2();
	virtual void	Unk_1B3();
	virtual void	Unk_1B4();
	virtual void	Unk_1B5();
	virtual void	Unk_1B6();
	virtual void	Unk_1B7();
	virtual void	Unk_1B8();
	virtual void	Unk_1B9();
	virtual void	Unk_1BA();
	virtual bool	IsWearingPowerArmorTorso();
	virtual bool	IsWearingPowerArmorHelmet();
	virtual bool	IsWearingBackpack();
	virtual void	Unk_1BE();
	virtual void	Unk_1BF();
	virtual void	Unk_1C0();
	virtual void	Unk_1C1();
	virtual void	Unk_1C2();
	virtual void	Unk_1C3();
	virtual void	Unk_1C4();
	virtual void	Unk_1C5();
	virtual TESIdleForm* GetIdleForm350();
	virtual void	SetIdleForm350(TESIdleForm* idleForm);
	virtual void	Unk_1C8();
	virtual void	Unk_1C9();
	virtual void	Unk_1CA();
	virtual void	Unk_1CB();
	virtual void	Unk_1CC();
	virtual float	GetLightAmount();
	virtual void	SetLightAmount(float lightAmount);
	virtual void	Unk_1CF();
	virtual void	Unk_1D0();
	virtual void	Unk_1D1();
	virtual void	Unk_1D2();
	virtual void	Unk_1D3();
	virtual void	Unk_1D4();
	virtual void	Unk_1D5();
	virtual void	Unk_1D6();
	virtual void	Unk_1D7();
	virtual void	Unk_1D8();
	virtual void	Unk_1D9();
	virtual void	Unk_1DA();
	virtual float	GetRadsSec();
	virtual ActorHitData* GetHitData();
	virtual void	CopyHitData(ActorHitData* hitData);
	virtual void	ResetHitData();
	virtual ActorHitData* GetHitData254();
	virtual void	CopyHitData254(ActorHitData* hitData);
	virtual void	ResetHitData254();
	virtual void	Unk_1E2();
	virtual void	Unk_1E3();
	virtual void	Unk_1E4();
	virtual void	Unk_1E5();
	virtual void	Unk_1E6();
	virtual void	Unk_1E7();
	virtual void	Unk_1E8();
	virtual void	Unk_1E9();
	virtual void	Unk_1EA();
	virtual void	Unk_1EB();
	virtual void	Unk_1EC();
	virtual void	Unk_1ED();	// Leads to Last Target

	// data

	PackageInfo		currentPackage;	// 04
	float			unk1C_maybeUnused;
	float			fHourLastProcessed;
	UInt32			iDateLastProcessed;			// 24	not initialized, only by descendant!
	UInt32			processLevel;	// 28	not initialized, only by descendant to 3 for Low, 2 for MiddleLow, 1 MiddleHighProcess and 0 for HighProcess
	CachedValues* cachedValues;			// 2C
};