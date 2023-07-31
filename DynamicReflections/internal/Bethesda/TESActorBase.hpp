#pragma once

#include "TESBoundAnimObject.hpp"
#include "TESActorBaseData.hpp"
#include "TESContainer.hpp"
#include "BGSTouchSpellForm.hpp"
#include "TESSpellList.hpp"
#include "TESAIForm.hpp"
#include "TESHealthForm.hpp"
#include "TESAttributes.hpp"
#include "TESAnimation.hpp"
#include "TESFullName.hpp"
#include "TESModel.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "TESScriptableForm.hpp"
#include "ActorValueOwner.hpp"

class BGSBodyPartData;
class TESCombatStyle;

class TESActorBase : public TESBoundAnimObject {
public:
	TESActorBase();
	~TESActorBase();

	virtual BGSBodyPartData* GetBodyPartData(void);
	virtual void				Fn_61(void* arg);
	virtual TESCombatStyle* GetCombatStyle(void);	// Result saved as ZNAM GetCombatStyle
	virtual void				SetCombatStyle(TESCombatStyle* combatStyle);
	virtual void				SetAttr(UInt32 idx, float value);	// calls Fn65
	virtual void				SetAttr(UInt32 idx, UInt32 value);
	virtual void				ModActorValue(UInt32 actorValueCode, float value);
	virtual void				Fn_67(void* arg0, UInt32 arg1);	// mod actor value?

	// bases
	TESActorBaseData			baseData;		// 030/054
	TESContainer				container;		// 064/084
	BGSTouchSpellForm			touchSpell;		// 070/090	Unarmed attack effect
	TESSpellList				spellList;		// 07C/09C
	TESAIForm					ai;				// 090
	TESHealthForm				health;			// 0B0
	TESAttributes				attributes;		// 0B8
	TESAnimation				animation;		// 0C4/0E4	special idles
	TESFullName					fullName;		// 0D0/0F8
	TESModel					model;			// 0DC/104
	TESScriptableForm			scriptable;		// 0F4/128
	ActorValueOwner				avOwner;		// 100
	BGSDestructibleObjectForm	destructible;	// 104
	// 10C
};

ASSERT_OFFSET(TESActorBase, baseData, 0x30);
ASSERT_OFFSET(TESActorBase, avOwner, 0x100);
ASSERT_SIZE(TESActorBase, 0x10C);