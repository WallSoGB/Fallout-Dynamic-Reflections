#pragma once

struct Timer {
	bool bDisableCounter;		// 00
	float fFPSClamp;				// 04
	float fFPSClampRemainder;	// 08
	float fSecondsPassed;		// 0C
	float fLastSecondsPassed;	// 10
	UInt32 uiMsPassed;			// 14
	UInt32 uiUnk18;				// 18
	bool bIsChangeTimeMultSlowly;// 1C
	byte unk1D;					// 1D
	byte unk1E;					// 1E
	byte unk1F;					// 1F
};