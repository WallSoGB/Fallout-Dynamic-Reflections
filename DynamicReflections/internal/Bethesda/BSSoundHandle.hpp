#pragma once

struct BSSoundHandle {
	UInt32 uiSoundID;
	bool bAssumeSuccess;
	UInt32 uiState;
};

ASSERT_SIZE(BSSoundHandle, 0xC);