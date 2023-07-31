#pragma once

struct ScrapHeapManager {
	struct Struct0 {
		LPVOID address;
		DWORD unk4;
	};

	Struct0 list0[64];
	UInt32 uiBufferCount;
	DWORD dword204;
	BYTE gap208[24];
	_RTL_CRITICAL_SECTION criticalSection;
	DWORD unk238;
	DWORD unk23C;

	ScrapHeapManager* GetSingleton();
	void FreeAllBuffers();
	void FreeBuffers(UInt32 auiBuffersToFree);
	void ReleaseBuffer(LPVOID lpAddress, int a3);
	void* RequestBuffer(SIZE_T* apSize);
};

ASSERT_SIZE(ScrapHeapManager, 0x240);

struct ScrapHeap {
	void* Allocate(UInt32 aSize, UInt32 aAlignment);
	void Deallocate(void* apMem);
};