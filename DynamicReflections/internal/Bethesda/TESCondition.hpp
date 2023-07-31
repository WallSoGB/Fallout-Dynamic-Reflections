#pragma once

#include "BSSimpleList.hpp"

class TESObjectREFR;

class TESCondition {
public:

	struct TESConditionItemData {
		UInt8			type;		// 000
		UInt8			pad[3];
		union {						// 004
			float	value;
			UInt32	global;
		} comparisonValue;
		UInt32			function;	// 008
		union {						// 00C
			float	value;
			UInt32	number;
			void* pointer;
		}				parameter1;
		union {						// 010
			float	value;
			UInt32	number;
			void* pointer;
		}				parameter2;
		UInt32			runOn;		// 014	Subject, Target, Reference, CombatTarget, LinkedReference
		TESObjectREFR* reference;	// 018
	};

	BSSimpleList<TESConditionItemData*> pHead;
};

ASSERT_SIZE(TESCondition, 0x8);