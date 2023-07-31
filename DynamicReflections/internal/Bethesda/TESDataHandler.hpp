#pragma once

#include "tList.hpp"
#include "TESFile.hpp"
#include "NiTArray.hpp"

class BGSAcousticSpace;
class BGSAddonNode;
class BGSBodyPartData;
class BGSCameraShot;
class BGSDebris;
class BGSDehydrationStage;
class BGSEncounterZone;
class BGSExplosion;
class BGSHeadPart;
class BGSHungerStage;
class BGSImpactData;
class BGSImpactDataSet;
class BGSLightingTemplate;
class BGSListForm;
class BGSMenuIcon;
class BGSMessage;
class BGSMusicType;
class BGSNote;
class BGSPerk;
class BGSProjectile;
class BGSRadiationStage;
class BGSRagdoll;
class BGSSleepDeprivationStage;
class BGSVoiceType;
class EnchantmentItem;
class MediaLocationController;
class MediaSet;
class Script;
class SpellItem;
class TESAmmoEffect;
class TESBoundObject;
class TESCaravanDeck;
class TESCasino;
class TESChallenge;
class TESClass;
class TESClimate;
class TESCombatStyle;
class TESEffectShader;
class TESEyes;
class TESFaction;
class TESGlobal;
class TESHair;
class TESImageSpace;
class TESImageSpaceModifier;
class TESLandTexture;
class TESLoadScreen;
class TESLoadScreenType;
class TESObjectANIO;
class TESObjectCELL;
class TESPackage;
class TESQuest;
class TESRace;
class TESRecipe;
class TESRecipeCategory;
class TESRegionList;
class TESRegionManager;
class TESReputation;
class TESSound;
class TESTopic;
class TESTopicInfo;
class TESWaterForm;
class TESWeather;
class TESWorldSpace;

struct ModList {
	tList<TESFile>		modInfoList;		// 00
	UInt32				loadedModCount;		// 08
	TESFile* loadedMods[0xFF];	// 0C
};

ASSERT_SIZE(ModList, 0x408);

// 5B8
class TESDataHandler {
public:
	TESDataHandler();
	~TESDataHandler();

	class BoundObjecBSSimpleListHead
	{
	public:
		BoundObjecBSSimpleListHead();
		~BoundObjecBSSimpleListHead();

		UInt32			boundObjectCount;	// 0
		TESBoundObject* first;			// 4
		TESBoundObject* last;				// 8
		UInt32			unkC;				// C
	};

	UInt32							unk00;					// 000
	BoundObjecBSSimpleListHead* boundObjecBSSimpleList;		// 004
	BSSimpleList<TESPackage*>				packageList;			// 008
	BSSimpleList<TESWorldSpace*>			worldSpaceList;			// 010
	BSSimpleList<TESClimate*>				climateList;			// 019
	BSSimpleList<TESImageSpace*>			imageSpaceList;			// 020
	BSSimpleList<TESImageSpaceModifier*>	imageSpaceModList;		// 028
	BSSimpleList<TESWeather*>				weatherList;			// 030
	BSSimpleList<EnchantmentItem*>			enchantmentItemList;	// 038
	BSSimpleList<SpellItem*>				spellItemList;			// 040
	BSSimpleList<BGSHeadPart*>				headParBSSimpleList;			// 048
	BSSimpleList<TESHair*>					hairList;				// 050
	BSSimpleList<TESEyes*>					eyeList;				// 058
	BSSimpleList<TESRace*>					raceList;				// 060
	BSSimpleList<BGSEncounterZone*>			encounterZoneList;		// 068
	BSSimpleList<TESLandTexture*>			landTextureList;		// 070
	BSSimpleList<BGSCameraShot*>			cameraShoBSSimpleList;			// 078
	BSSimpleList<TESClass*>					classList;				// 080
	BSSimpleList<TESFaction*>				factionList;			// 088
	BSSimpleList<TESReputation*>			reputationList;			// 090
	BSSimpleList<TESChallenge*>				challengeList;			// 098
	BSSimpleList<TESRecipe*>				recipeList;				// 0A0
	BSSimpleList<TESRecipeCategory*>		recipeCategoryList;		// 0A8
	BSSimpleList<TESAmmoEffect*>			ammoEffecBSSimpleList;			// 0B0
	BSSimpleList<TESCasino*>				casinoList;				// 0B8
	BSSimpleList<TESCaravanDeck*>			caravanDeckList;		// 0C0
	BSSimpleList<Script*>					scripBSSimpleList;				// 0C8
	BSSimpleList<TESSound*>					soundList;				// 0D0
	BSSimpleList<BGSAcousticSpace*>			acousticSpaceList;		// 0D8
	BSSimpleList<BGSRagdoll*>				ragdollList;			// 0E0
	BSSimpleList<TESGlobal*>				globalList;				// 0E8
	BSSimpleList<BGSVoiceType*>				voiceTypeList;			// 0F0
	BSSimpleList<BGSImpactData*>			impactDataList;			// 0F8
	BSSimpleList<BGSImpactDataSet*>			impactDataSeBSSimpleList;		// 100
	BSSimpleList<TESTopic*>					topicList;				// 108
	BSSimpleList<TESTopicInfo*>				topicInfoList;			// 110
	BSSimpleList<TESQuest*>					quesBSSimpleList;				// 118
	BSSimpleList<TESCombatStyle*>			combatStyleList;		// 120
	BSSimpleList<TESLoadScreen*>			loadScreenList;			// 128
	BSSimpleList<TESWaterForm*>				waterFormList;			// 130
	BSSimpleList<TESEffectShader*>			effectShaderList;		// 138
	BSSimpleList<BGSProjectile*>			projectileList;			// 140
	BSSimpleList<BGSExplosion*>				explosionList;			// 148
	BSSimpleList<BGSRadiationStage*>		radiationStageList;		// 150
	BSSimpleList<BGSDehydrationStage*>		dehydrationStageList;	// 158
	BSSimpleList<BGSHungerStage*>			hungerStageList;		// 160
	BSSimpleList<BGSSleepDeprivationStage*>	sleepDepriveStageList;	// 168
	BSSimpleList<BGSDebris*>				debrisList;				// 170
	BSSimpleList<BGSPerk*>					perkList;				// 178
	BSSimpleList<BGSBodyPartData*>			bodyPartDataList;		// 180
	BSSimpleList<BGSNote*>					noteList;				// 188
	BSSimpleList<BGSListForm*>				listFormList;			// 190
	BSSimpleList<BGSMenuIcon*>				menuIconList;			// 198
	BSSimpleList<TESObjectANIO*>			anioList;				// 1A0
	BSSimpleList<BGSMessage*>				messageList;			// 1A8
	BSSimpleList<BGSLightingTemplate*>		lightningTemplateList;	// 1B0
	BSSimpleList<BGSMusicType*>				musicTypeList;			// 1B8
	BSSimpleList<TESLoadScreenType*>		loadScreenTypeList;		// 1C0
	BSSimpleList<MediaSet*>					mediaSeBSSimpleList;			// 1C8
	BSSimpleList<MediaLocationController*>	mediaLocControllerList;	// 1D0
	TESRegionList* regionList;			// 1D8
	NiTArray<TESObjectCELL*>		cellArray;				// 1DC
	NiTArray<BGSAddonNode*>			addonArray;				// 1EC

	UInt32							unk1FC[0x3];			// 1FC	208 looks like next created refID
	UInt32							nextCreatedRefID;		// 208	Init'd to FF000800 (in GECK init'd to nn000800)
	TESFile* activeFile;					// 20C	last unselected mod in modList. GECK: active ESM
	ModList							modList;				// 210
	UInt8							unk618;					// 618	5A4
	UInt8							unk619;					// 619
	UInt8							unk61A;					// 61A	referenced during LoadForm (ie TESSpellList). bit 1 might mean refID to pointer conversion not done. For GECK means save in progress
	UInt8							unk61B;					// 61B
	UInt8							unk61C;					// 61C	5A8
	UInt8							unk61D;					// 61D
	UInt8							unk61E;					// 61E
	UInt8							unk61F;					// 61F
	UInt8							unk620;					// 620	5AC
	UInt8							loading;				// 621	Init'd to 0 after loadForms
	UInt8							unk622;					// 622	referenced during loading of modules. Compared with type = GameSetting but seems to always end up equal to 1.
	UInt8							unk623;					// 623
	TESRegionManager* regionManager;		// 624	5B0
	UInt32							unk628;					// 628	5B4
	UInt32							unk62C;					// 62C
	UInt32							unk630;					// 630
	UInt32							unk634;					// 634
	UInt32							unk638;					// 638

	static TESDataHandler* Get();
	const TESFile** GetActiveModList();		// returns array of modEntry* corresponding to loaded mods sorted by mod index
	const TESFile* LookupModByName(const char* modName);
	UInt8 GetModIndex(const char* modName);
	UInt8 GetActiveModCount() const;
	const char* GetNthModName(UInt32 modIndex);

	void DisableAssignFormIDs(bool shouldAsssign);

	MEMBER_FN_PREFIX(TESDataHandler);
#if RUNTIME
	DEFINE_MEMBER_FN(DoAddForm, UInt32, 0x004603B0, TESForm* pForm);	// stupid name is because AddForm is redefined in windows header files
#endif

	TESQuest* GetQuestByName(const char* questName);
};

ASSERT_SIZE(TESDataHandler, 0x63C);

typedef TESDataHandler DataHandler;