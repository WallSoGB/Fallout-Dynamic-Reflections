#pragma once

#include "GameForms.h"
#include "Utilities.h"

class TESReputation;
class TESChallenge;
class TESRecipe;
class TESRecipeCategory;
class TESAmmoEffect;
class TESCasino;
class TESCaravanDeck;
class TESTopicInfo;
class BGSDehydrationStage;
class BGSHungerStage;
class BGSSleepDeprivationStage;
class TESLoadScreenType;
class MediaSet;
class MediaLocationController;
class TESRegionList;
class TESRegionManager;
class BSFile;

struct FormRecordData
{
	UInt8		typeID;		// corresponds to kFormType_XXX
	UInt32		typeCode;	// i.e. 'GMST', 'FACT'
	UInt32		unk08;		// only seen zero
};


#include "TESFile.hpp"
#include "TESDataHandler.hpp"