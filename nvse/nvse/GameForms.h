
#pragma once

#include <vector>

#include "Utilities.h"
#include "GameTypes.h"
#include "GameBSExtraData.h"

#define IS_ID(form, type) (form->typeID == kFormType_##type)
#define NOT_ID(form, type) (form->typeID != kFormType_##type)

struct PermanentClonedForm {
	UInt32 orgRefID;
	UInt32 cloneRefID;
};

#include "BaseFormComponent.hpp"
#include "TESBoundObject.hpp"
#include "TESIcon.hpp"
#include "TESScriptableForm.hpp"
#include "BGSMessageIcon.hpp"
#include "TESValueForm.hpp"
#include "TESEnchantableForm.hpp"
#include "TESImageSpaceModifiableForm.hpp"
#include "TESWeightForm.hpp"
#include "TESHealthForm.hpp"
#include "TESAttackDamageForm.hpp"
#include "EffectItem.hpp"
#include "MagicItemForm.hpp"
#include "BGSTextureModel.hpp"
#include "TESModelTextureSwap.hpp"
#include "BGSClipRoundsForm.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSPickupPutdownSounds.hpp"
#include "BGSAmmoForm.hpp"
#include "BGSRepairItemList.hpp"
#include "BGSEquipType.hpp"
#include "BGSPreloadable.hpp"
#include "BGSBipedModelList.hpp"
#include "TESModelRDT.hpp"
#include "TESBipedModelForm.hpp"
#include "TESBoundAnimObject.hpp"
#include "TESContainer.hpp"
#include "BGSTouchSpellForm.hpp"
#include "TESActorBaseData.hpp"
#include "TESSpellList.hpp"
#include "TESAIForm.hpp"
#include "TESAttributes.hpp"
#include "TESAnimation.hpp"
#include "ActorValueOwner.hpp"
#include "CachedValuesOwner.hpp"
#include "TESActorBase.hpp"
#include "TESModelList.hpp"
#include "TESDescription.hpp"
#include "TESReactionForm.hpp"
#include "TESRaceForm.hpp"
#include "BSShaderTextureSet.hpp"
#include "BGSTextureSet.hpp"
#include "TESSoundFile.hpp"
#include "BGSQuestObjective.hpp"
#include "BGSOpenCloseForm.hpp"
#include "TESTopic.hpp"
#include "BGSMenuIcon.hpp"
#include "TESGlobal.hpp"
#include "TESClass.hpp"
#include "TESReputation.hpp"
#include "TESFaction.hpp"
#include "BGSHeadPart.hpp"
#include "TESSound.hpp"
#include "BGSAcousticSpace.hpp"
#include "TESSkill.hpp"
#include "EffectSetting.hpp"
#include "TESGrass.hpp"
#include "TESLandTexture.hpp"
#include "EnchantmentItem.hpp"
#include "BGSTalkingActivator.hpp"
#include "BGSNote.hpp"
#include "BGSTerminal.hpp"
#include "TESObjectARMO.hpp"
#include "TESObjectBOOK.hpp"
#include "TESObjectCLOT.hpp"
#include "TESObjectCONT.hpp"
#include "TESObjectDOOR.hpp"
#include "IngredientItem.hpp"
#include "TESObjectLIGH.hpp"
#include "TESObjectMISC.hpp"
#include "TESObjectSTAT.hpp"
#include "BGSStaticCollection.hpp"
#include "BGSMovableStatic.hpp"
#include "BGSPlaceableWater.hpp"
#include "TESObjectTREE.hpp"
#include "TESFlora.hpp"
#include "TESFurniture.hpp"
#include "TESObjectIMOD.hpp"
#include "TESObjectWEAP.hpp"
#include "TESAmmoEffect.hpp"
#include "TESAmmo.hpp"
#include "BipedAnim.hpp"
#include "TESNPC.hpp"
#include "TESCreature.hpp"
#include "TESLeveledList.hpp"
#include "TESLevCreature.hpp"
#include "TESLevCharacter.hpp"
#include "TESKey.hpp"
#include "AlchemyItem.hpp"
#include "BGSIdleMarker.hpp"
#include "BGSConstructibleObject.hpp"
#include "BGSProjectile.hpp"
#include "TESLevItem.hpp"
#include "TESImageSpaceModifier.hpp"
#include "TESWeather.hpp"
#include "TESClimate.hpp"
#include "TESRegionData.hpp"
#include "TESRegionDataGrass.hpp"
#include "TESRegionDataImposter.hpp"
#include "TESRegionDataLandscape.hpp"
#include "TESRegionDataMap.hpp"
#include "TESRegionDataSound.hpp"
#include "TESRegionDataWeather.hpp"
#include "TESRegion.hpp"
#include "NavMeshInfoMap.hpp"
#include "TESObjectCELL.hpp"
#include "TESWorldSpace.hpp"
#include "TESObjectLAND.hpp"
#include "NavMesh.hpp"
#include "TESCondition.hpp"
#include "ScriptLocal.hpp"
#include "VariableInfo.hpp"
#include "TESQuest.hpp"
#include "TESIdleForm.hpp"
#include "TESPackageData.hpp"
#include "TESPatrolPackageData.hpp"
#include "TESPackage.hpp"
#include "DialoguePackage.hpp"
#include "FleePackage.hpp"
#include "TressPassPackage.hpp"
#include "SpectatorPackage.hpp"
#include "TESFollowPackageData.hpp"
#include "TESCombatStyle.hpp"
#include "TESRecipeCategory.hpp"
#include "TESRecipe.hpp"
#include "TESLoadScreen.hpp"
#include "TESLevSpell.hpp"
#include "TESObjectANIO.hpp"
#include "TESWaterForm.hpp"
#include "TESEffectShader.hpp"
#include "BGSExplosion.hpp"
#include "TESImageSpace.hpp"
#include "BGSListForm.hpp"
#include "BGSPerkEntry.hpp"
#include "BGSQuestPerkEntry.hpp"
#include "BGSAbilityPerkEntry.hpp"
#include "BGSEntryPointFunctionData.hpp"
#include "BGSEntryPointFunctionDataOneValue.hpp"
#include "BGSEntryPointFunctionDataTwoValue.hpp"
#include "BGSEntryPointFunctionDataLeveledList.hpp"
#include "BGSEntryPointFunctionDataActivateChoice.hpp"
#include "BGSEntryPointPerkEntry.hpp"
#include "BGSPerk.hpp"
#include "BGSBodyPart.hpp"
#include "BGSBodyPartData.hpp"
#include "BGSAddonNode.hpp"
#include "ActorValueInfo.hpp"
#include "BGSRadiationStage.hpp"
#include "BGSCameraShot.hpp"
#include "BGSCameraPath.hpp"
#include "BGSVoiceType.hpp"
#include "BGSImpactData.hpp"
#include "BGSImpactDataSet.hpp"
#include "TESObjectARMA.hpp"
#include "BGSEncounterZone.hpp"
#include "BGSMessage.hpp"
#include "BGSRagdoll.hpp"
#include "BGSLightingTemplate.hpp"
#include "BGSMusicType.hpp"
#include "BGSDefaultObjectManager.hpp"

enum EActionListForm
{
	eActionListForm_AddAt	= 00,
	eActionListForm_DelAt,
	eActionListForm_ChgAt,
	eActionListForm_GetAt,
	eActionListForm_Check,
	eActionListForm_Max,
};

enum EWhichListForm
{
	eWhichListForm_RaceHair					= 00,
	eWhichListForm_RaceEyes,
	eWhichListForm_RaceHeadPart,			// ? //
	eWhichListForm_BaseFaction,
	eWhichListForm_BaseRank,
	eWhichListForm_BasePackage,
	eWhichListForm_BaseSpellListSpell,
	eWhichListForm_BaseSpellListLevSpell,
	eWhichListForm_FactionRankName,
	eWhichListForm_FactionRankFemaleName,
	eWhichListForm_HeadParts,
	eWhichListForm_LevCreatureRef,
	eWhichListForm_LevCharacterRef,
	eWhichListForm_FormList,
	eWhichListForm_Max,
};

