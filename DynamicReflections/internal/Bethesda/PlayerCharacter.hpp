#pragma once

#include "Character.hpp"
#include "BSSimpleList.hpp"
#include "TESRegion.hpp"
#include "TESSound.hpp"
#include "NiVector3.hpp"
#include "QuestTarget.hpp"
#include "BSSoundHandle.hpp"

class AlchemyItem;
class BGSNote;
class BGSQuestObjective;
class bhkMouseSpringAction;
class CameraCaster;
class CombatGroup;
class DialoguePackage;
class ImageSpaceModifierInstanceDOF;
class ImageSpaceModifierInstanceDRB;
class MagicItem;
class MagicShaderHitEffect;
class MagicTarget;
class MusicMarker;
class QuestObjectiveTargets;
class TESCaravanCard;
class TESClass;
class TESEnchantableForm;
class TESObjectCELL;
class TESObjectREFR;
class TESObjectWEAP;
class TESQuest;
class TESReputation;
class TESTopic;
class TESWorldspace;
struct AnimData;
struct BipedAnim;

class PlayerCharacter : public Character {
public:
	PlayerCharacter();
	~PlayerCharacter();

	struct WobbleNodes
	{
		NiNode* wobbleAnimNodes[12];
		NiNode* wobbleAnimNodes2[12];
	};

	struct LevelupInfo
	{
		UInt8 shouldLevelUp;
		UInt8 pad01[3];
		UInt32 xpForNextLevel;
		UInt8 byte08;
		UInt8 pad09[3];
	};

	struct CompassTarget
	{
		Actor* target;
		UInt8 isHostile;
		UInt8 isUndetected;
		UInt8 pad06[2];
	};

	struct PositionRequest
	{
		TESWorldspace* worldspace;
		TESObjectCELL* cell;
		NiPoint3 pos;
		NiVector3 rot;
		UInt8 bResetWeather;
		UInt8 gap21[3];
		void(__cdecl* callbackFunc)(void*);
		void* callbackFuncArg;
		TESObjectREFR* destRef;
		TESObjectREFR* fastTravelRef;
	};

	struct FlyCamData
	{
		float rotX;
		float rotZ;
		NiPoint3 position;
	};

	enum GrabMode
	{
		kGrabMode_ZKey = 0x1,
		kGrabMode_Telekenesis = 0x3,
	};

	// used to flag controls as disabled in disabledControlFlags
	enum {
		kControlFlag_Movement = 1 << 0,
		kControlFlag_Look = 1 << 1,
		kControlFlag_Pipboy = 1 << 2,
		kControlFlag_Fight = 1 << 3,
		kControlFlag_POVSwitch = 1 << 4,
		kControlFlag_RolloverText = 1 << 5,
		kControlFlag_Sneak = 1 << 6,
	};

	enum KillcamMode
	{
		kKillcamMode_None = 0x0,
		kKillcamMode_PlayerView = 0x1,
		kKillcamMode_Cinematic = 0x2,
	};

	virtual void		Unk_139(void);
	virtual void		Unk_13A(void);

	// lotsa data

	UInt32 unk1C8;
	UInt32 unk1CC;
	UInt32 unk1D0;
	UInt32 unk1D4;
	UInt32 unk1D8;
	UInt32 unk1DC;
	UInt32 unk1E0;
	UInt32 unk1E4;
	UInt32 unk1E8;
	PlayerCharacter::PositionRequest* positionRequest;
	TESObjectWEAP* weap1F0;
	float time1F4;
	UInt8 byte1F8;
	UInt8 gap1F9[3];
	UInt32 sandmanDetectionValue;
	UInt32 unk200;
	UInt8 byte204;
	UInt8 byte205;
	UInt8 questTargetsNeedRecalculated;
	UInt8 byte207;
	DialoguePackage* closestConversation;
	UInt8 isPlayerMovingIntoNewSpace;
	UInt8 gap20D[3];
	void* activeEffects;
	MagicItem* magicItem214;
	MagicTarget* magicTarget218;
	CameraCaster* cameraCaster;
	UInt32 unk220;
	UInt32 unk224;
	UInt32 unk228;
	float time22C;
	UInt32 unk230;
	float time234;
	BSSimpleList<UInt32>* list238;
	BSSimpleList<TESEnchantableForm*>* enchantmentList23C;
	bool showQuestItems;
	UInt8 byte241;
	UInt8 byte242;
	UInt8 byte243;
	float actorValue244[77];
	float permAVMods[77];
	float healthAV_4AC;
	float actorValues4B0[77];
	BSSimpleList<UInt32> notes;
	ImageSpaceModifierInstanceDOF* imod5EC;
	ImageSpaceModifierInstanceDOF* unk5F0;
	ImageSpaceModifierInstanceDRB* unk5F4;
	UInt8 isDetected;
	UInt8 bPreventRegionSoundUpdates;
	UInt8 byte5FA;
	UInt8 byte5FB;
	BSSimpleList<UInt32> teammates;
	TESObjectREFR* lastExteriorDoor;
	UInt8 isPlayingCombatAttackSound;
	UInt8 pad609[3];
	void* actionList;
	BSSimpleList<UInt32>* casinoDataList;
	BSSimpleList<TESCaravanCard*>* caravanCards1;
	BSSimpleList<TESCaravanCard*>* caravanCards2;
	UInt32 caravanCapsEarned;
	UInt32 caravanCapsLost;
	UInt32 numCaravanWins;
	UInt32 numCaravanLosses;
	UInt32 largestCaravanWin;
	UInt32 unk630;
	bhkMouseSpringAction* GrabSpringA;
	TESObjectREFR* grabbedRef;
	PlayerCharacter::GrabMode eGrabType;
	float currentGrabbedItemWeight;
	float fGrabDistance;
	UInt8 byte648;
	UInt8 byte649;
	bool is3rdPersonVisible;
	bool is3rdPerson;
	bool bThirdPerson;
	UInt8 bShouldRestoreFirstPersonAfterVanityMode;
	UInt8 bWasFirstPersonBeforeVanityCam;
	bool isForceFirstPerson;
	UInt8 byte650;
	bool alwaysRun;
	bool autoMove;
	UInt8 byte653;
	UInt32 sleepHours;
	UInt8 isResting;
	UInt8 byte659;
	UInt8 byte65A;
	UInt8 byte65B;
	float unk65C;
	float time660;
	float time664;
	float unused_time668;
	UInt8 isActorWithin_iSneakSkillUseDistance;
	UInt8 flag66D;
	UInt8 canSleepWait;
	UInt8 byte66F;
	float fWorldFOV;
	float f1stPersonFOV;
	float fOverShoulderFOV;
	UInt32 unk67C;
	UInt8 pcControlFlags;
	UInt8 isWaitingForOpenContainerAnim;
	UInt8 byte682;
	UInt8 byte683;
	float waitingForContainerOpenAnimPreventActivateTimer;
	TESObjectREFR* activatedDoor;
	BipedAnim* bipedAnims1st;
	AnimData* firstPersonArms;
	NiNodePtr spPlayerNode;
	float eyeHeight;
	NiNode* inventoryMenu;
	AnimData* animData6A0;
	MagicShaderHitEffect* magicShaderHitEffect;
	BSSimpleList<UInt32> topicList;
	BSSimpleList<UInt32> list6B0;
	TESQuest* activeQuest;
	BSSimpleList<UInt32> questObjectiveList;
	BSSimpleList<UInt32> questTargetList;
	UInt8 bPlayerGreetFlag;
	UInt8 pad6CD[3];
	float fPlayerGreetTimer;
	UInt32 unk6D4;
	UInt8 bIsAMurderer;
	UInt8 pad6D9;
	UInt8 pad6DA;
	UInt8 pad6DB;
	UInt32 amountSoldStolen;
	float sortActorDistanceListTimer;
	float seatedRotation;
	UInt8 byte6E8;
	UInt8 byte6E9;
	UInt8 byte6EA;
	UInt8 byte6EB;
	MagicItem* magicItem6EC;
	UInt32 playerSpell;
	TESObjectREFR* placedMarker;
	QuestTarget placedMarkerTarget;
	float timeGrenadeHeld;
	UInt32 unk734;
	UInt32 unk738;
	TESClass* class73C_unset;
	UInt32 unk740;
	UInt32 crimeCounts[5];
	AlchemyItem* poisonToApply;
	bool inCharGen;
	UInt8 byte75D;
	UInt8 canUseTelekinesis;
	UInt8 byte75F;
	TESRegion* currentRegion;
	BSSimpleArray<UInt32> regionsList;
	BSSimpleList<UInt32> list774;
	BSSoundHandle heartBeatSound;
	UInt32 unk788;
	UInt32 iLastPlayingTimeUpdate;
	UInt32 iTotalPlayingTime;
	UInt32 unk794;
	char isInSleepPackage;
	char isTransitioningSeatedState;
	char isDrinkingPlacedWater;
	char isPackagePlaying;
	UInt8 byte79C;
	UInt8 byte79D;
	UInt8 gap79E[2];
	NiPoint3 lastBorderRegionPosition;
	void* pcWorldOrCell;
	NiTPrimitiveArray<TESRegion>* regionArray;
	void* musicType;
	UInt32 gameDifficulty;
	UInt32 isHardcore;
	KillcamMode killCamMode;
	char inCombatWithGuard;
	char isYoung;
	char isToddler;
	char canUsePA;
	BSSimpleList<UInt32> mapMarkers;
	void* worldspaceForMapMarkerUpdates;
	BSSimpleList<MusicMarker*> musicMarkers;
	MusicMarker* currMusicMarker;
	FlyCamData flycamPos;
	UInt32 unk7F4;
	BSSoundHandle sound7F8_unused;
	BSSoundHandle unk808[6];
	BSSimpleList<UInt32> droppedRefList;
	NiTMap<UInt32, UInt8> unk858;
	UInt32 unk868;
	UInt32 unk86C;
	UInt8 hasShownNoChargeWarning;
	UInt8 gap86D[3];
	float fDropAngleMod;
	float fLastDropAngleMod;
	PlayerCharacter::LevelupInfo* levelupInfo;
	BSSimpleList<UInt32> perkRanksPC;
	BSSimpleList<UInt32> perkEntriesPC[74];
	BSSimpleList<UInt32> perkRanksTM;
	BSSimpleList<UInt32> perkEntriesTM[74];
	Actor* autoAimActor;
	NiPoint3 BulletAutoAim;
	NiNode* nodeD3C;
	UInt8 isActorWithinInterfaceManagerPickDistance;
	UInt8 gapD41[3];
	void* reticleActor;
	BSSimpleList<CompassTarget*>* compassTargets;
	float pipboyLightHeldTime;
	float ammoSwapTimer;
	char shouldOpenPipboy;
	char byteD55;
	char byteD56;
	char byteD57;
	NiPoint3 ptD58;
	CombatGroup* combatGroup;
	int teammateCount;
	float combatYieldTimer;
	float combatYieldRetryTimer;
	PlayerCharacter::WobbleNodes wobbleAnims;
	NiVector3 vectorDD4;
	NiVector3 cameraPos;
	void* rigidBody;
	char pcInCombat;
	char pcUnseen;
	char isLODApocalypse;
	char byteDF3;
	BSSimpleArray<UInt32> rockitLauncherContainer;
	float rockItLauncherWeight;
	char hasNightVisionApplied;
	char byteE09;
	char byteE0A;
	char byteE0B;
	TESReputation* modifiedReputation;
	int unkE10;
	int unkE14;
	float killCamTimer;
	float killCamCooldown;
	char byteE20;
	char isUsingTurbo;
	char byteE22;
	char byteE23;
	float lastHelloTime;
	float counterAttackTimer;
	char byteE2C;
	char isCateyeEnabled;
	char isSpottingImprovedActive;
	char byteE2F;
	float itemDetectionTimer;
	NiNode* pIronSightNode;
	bool noHardcoreTracking;
	bool skipHCNeedsUpdate;
	char byteE3A;
	char byteE3B;
	BSSimpleArray<UInt32> hotkeyedWeaponAmmos;
	TESQuest* patch04DebugQuest;

	// 7C4 is a byte used during Combat evaluation (Player is targetted ?),
	// 7C6 is a boolean meaning toddler,
	// 7C7 byte bool PCCanUsePowerArmor, Byt0E39 referenced during LoadGame
	// Used when entering FlyCam : 7E8/7EC/7F0 stores Pos, 7F0 adjusted by scaledHeight multiplied by 0698 , 7E0 stores RotZ, 7E4 RotX
	// Perks forms a list at 87C and AD4. Caravan Cards at 614 and 618. Quest Stage LogEntry at 6B0. Quest Objectives at 6BC.
	// Hardcore flag would be E38. Byte at DF0 seems to be PlayerIsInCombat
	// BSSimpleList at 6C4 is cleared when there is no current quest. There is another NiNode at 069C
	// list of perk and perkRank are at 0x087C and 0x0AD4 (alt perks). 086C is cleared after equipement change.
	// D68 counts the Teammates.
	// D74: 96 bytes that are cleared when the 3D is cleared.

	bool IsThirdPerson() { return bThirdPerson; }

	static PlayerCharacter* GetSingleton();
	bool SetSkeletonPath(const char* newPath);
	bool SetSkeletonPath_v1c(const char* newPath);	// Less worse version as used by some modders
	QuestObjectiveTargets* GetCurrentQuestObjectiveTargets();
	bool HasPipBoyOpen() {
		return ThisStdCall(0x967AE0, this);
	}

	NiNode* GetNode(const bool bCurrentActive);
};

ASSERT_SIZE(Character, 0x1C8);
ASSERT_OFFSET(PlayerCharacter, unk1C8, 0x1C8);
ASSERT_OFFSET(PlayerCharacter, ragDollController, 0xAC);
ASSERT_OFFSET(PlayerCharacter, questObjectiveList, 0x6BC);
ASSERT_OFFSET(PlayerCharacter, bThirdPerson, 0x64C);
ASSERT_OFFSET(PlayerCharacter, actorMover, 0x190);
ASSERT_OFFSET(PlayerCharacter, flycamPos, 0x7E0);
ASSERT_OFFSET(PlayerCharacter, fLastDropAngleMod, 0x874);
ASSERT_OFFSET(PlayerCharacter, killCamTimer, 0xE18);
ASSERT_SIZE(PlayerCharacter, 0xE50);