#pragma once

#include "BSSimpleList.hpp"
#include "TESIcon.hpp"
#include "TESFullName.hpp"
#include "TESModel.hpp"
#include "TESDescription.hpp"
#include "TESForm.hpp"

class TESObjectLIGH;
class TESEffectShader;
class TESSound;

class EffectSetting : public TESForm {
public:
	EffectSetting();
	~EffectSetting();

	enum
	{
		kArchType_ValueModifier = 0,
		kArchType_Script,
		kArchType_Dispel,
		kArchType_CureDisease,
		kArchType_Invisibility = 11,
		kArchType_Chameleon,
		kArchType_Light,
		kArchType_Lock = 16,
		kArchType_Open,
		kArchType_BoundItem,
		kArchType_SummonCreature,
		kArchType_Paralysis = 24,
		kArchType_CureParalysis = 30,
		kArchType_CureAddiction,
		kArchType_CurePoison,
		kArchType_Concussion,
		kArchType_ValueAndParts,
		kArchType_LimbCondition,
		kArchType_Turbo,
	};

	TESModel			model;					// 18
	TESDescription		description;			// 30
	TESFullName			fullName;				// 38
	TESIcon				icon;					// 44
	UInt32				unk50;					// 50
	UInt32				unk54;					// 54
	UInt32				effectFlags;			// 58 - start of DATA
	float				baseCost;				// 5C
	TESForm* associatedItem;			// 60 - Script* for ScriptEffects
	UInt32				magicSchool;			// 64 - unused
	UInt32				resistVal;				// 68 - actor value for resistance
	UInt16				counterEffectCount;		// 6C - counter effects count
	UInt8				pad6E[2];				// 6E
	TESObjectLIGH* light;					// 70
	float				projectileSpeed;		// 74
	TESEffectShader* effectShader;			// 78 - effect shader
	TESEffectShader* objectDisplayShader;	// 7C
	TESSound* effectSound;			// 80
	TESSound* boltSound;				// 84
	TESSound* hitSound;				// 88
	TESSound* areaSound;				// 8C
	float				fMagicDefaultCEEnchantFactor;
	float				fMagicDefaultCEBarterFactor;
	UInt32				archtype;				// 98
	UInt32				actorVal;				// 9C - actor value - last field of DATA
	BSSimpleList<EffectSetting*>	counterEffects;		// A0 - counter effects list
	UInt32				unkA8;					// A8
	UInt32				unkAC;					// AC

	Script* GetScript() { return 1 == archtype ? (Script*)associatedItem : NULL; };
	bool HasScript() { return 1 == archtype ? true : false; };
	Script* RemoveScript();
	Script* SetScript(Script* newScript);
};

ASSERT_SIZE(EffectSetting, 0xB0);