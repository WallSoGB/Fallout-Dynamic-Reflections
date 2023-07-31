#pragma once

#include "TESBoundObject.hpp"
#include "EffectItem.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESIcon.hpp"
#include "BGSMessageIcon.hpp"
#include "TESScriptableForm.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSEquipType.hpp"
#include "BGSPickupPutdownSounds.hpp"

class SpellItem;

class AlchemyItem : public TESBoundObject {
public:
	AlchemyItem();
	~AlchemyItem();

	TESFullName					fullName;				// 30
	EffectItemList				effects;				// 3C
	TESModelTextureSwap			model;					// 4C
	TESIcon						icon;					// 6C
	BGSMessageIcon				messageIcon;			// 78
	TESScriptableForm			scriptable;				// 88
	BGSDestructibleObjectForm	destructible;			// 94
	BGSEquipType				equipType;				// 9C

	UInt32						unkA4[2];				// A4
	BGSPickupPutdownSounds		pickupPutdownsounds;	// AC
	UInt32						value;					// B8
	UInt8						alchFlags;				// BC
	UInt8						padBD[3];				// BD
	SpellItem* withdrawalEffect;		// C0
	float						addictionChance;		// C4
	TESSound* consumeSound;			// C8
	UInt32						unkCC[3];				// CC
};

ASSERT_SIZE(AlchemyItem, 0xD8);