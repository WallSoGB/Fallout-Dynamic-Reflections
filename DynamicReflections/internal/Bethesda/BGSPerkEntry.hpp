#pragma once

class BGSPerkEntry {
public:
	BGSPerkEntry();
	~BGSPerkEntry();

	UInt32				vtbl;				// 00
	UInt8				rank;				// 04 +1 for value shown in GECK
	UInt8				priority;			// 05
	UInt16				type;				// 06 (Quest: 0xC24, Ability: 0xB27, Entry Point: 0xD16)
};