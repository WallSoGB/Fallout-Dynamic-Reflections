#pragma once

#include "Timer.hpp"

struct TimeGlobal : public Timer {
	float unk20;
	float unk24;
	float unk28;

	static TimeGlobal* GetSingleton() {
		return *(TimeGlobal**)0x11F6394;
	}

	static float GetGlobalTimeMult() {
		return *(float*)0x11AC3A0;
	}
};
