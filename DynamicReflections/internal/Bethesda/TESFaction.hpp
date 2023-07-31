#pragma once

#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESReactionForm.hpp"
#include "TESReputation.hpp"

class TESFaction : public TESForm {
public:
	TESFaction();
	~TESFaction();
	enum
	{
		// TESForm flags

		// TESReactionForm flags

		kModified_FactionFlags = 0x00000004
		// CHANGE_FACTION_FLAGS
		// UInt8	flags;
	};

	enum
	{
		kFlag_HiddenFromPC = 0x00000001,
		kFlag_Evil = 0x00000002,
		kFlag_SpecialCombat = 0x00000004,

		kFlag_TrackCrime = 0x00000100,
		kFlag_AllowSell = 0x00000200,
	};

	// 1C
	struct Rank
	{
		BSStringT		name;		// 00
		BSStringT		femaleName;	// 08
		TESTexture	insignia;	// 10 - effectively unused, can be set but there is no faction UI
	};

	TESFullName		fullName;	// 18
	TESReactionForm	reaction;	// 24

	UInt32			factionFlags;	// 34
	TESReputation* reputation;		// 38
	tList<Rank*>	ranks;			// 3C
	UInt32			crimeCount44;	// 44
	UInt32			crimeCount48;	// 48

	bool IsFlagSet(UInt32 flag) {
		return (factionFlags & flag) != 0;
	}
	void SetFlag(UInt32 flag, bool bMod) {
		factionFlags = bMod ? (factionFlags | flag) : (factionFlags & ~flag);
		AddChange(kModified_FactionFlags);
	}
	bool IsHidden()
	{
		return IsFlagSet(kFlag_HiddenFromPC);
	}
	bool IsEvil()
	{
		return IsFlagSet(kFlag_Evil);
	}
	bool HasSpecialCombat()
	{
		return IsFlagSet(kFlag_SpecialCombat);
	}
	void SetHidden(bool bHidden)
	{
		SetFlag(kFlag_HiddenFromPC, bHidden);
	}
	void SetEvil(bool bEvil)
	{
		SetFlag(kFlag_Evil, bEvil);
	}
	void SetSpecialCombat(bool bSpec)
	{
		SetFlag(kFlag_SpecialCombat, bSpec);
	}
	const char* GetNthRankName(UInt32 whichRank, bool bFemale = false);
	void SetNthRankName(const char* newName, UInt32 whichRank, bool bFemale);
};

ASSERT_SIZE(TESFaction, 0x4C);