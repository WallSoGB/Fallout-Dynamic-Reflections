#include "MemoryManager.hpp"
#include "ScrapHeap.hpp"

__forceinline __declspec(naked)  TLSData* TLSData::GetTLSData() {
	__asm {
		mov		eax, fs: [0x2C]
		mov		edx, ds : 0x126FD98
		mov		eax, [eax + edx * 4]
		retn
	}
}

inline UInt32 TLSData::GetHeapIndex() {
	return GetTLSData()->uiHeapIndex;
}

inline void TLSData::SetHeapIndex(UInt32 index) {
	GetTLSData()->uiHeapIndex = index;
}

MemoryManager* MemoryManager::GetSingleton() {
	return &*(MemoryManager*)0x11F6238;
}

// 0xAA42E0
ScrapHeap* MemoryManager::GetThreadScrapHeap() {
	return ThisStdCall<ScrapHeap*>(0xAA42E0, MemoryManager::GetSingleton());
}

// 0xAA3E40
void* MemoryManager::Allocate(size_t aSize) {
	return ThisStdCall<void*>(0xAA3E40, MemoryManager::GetSingleton(), aSize);
}

// 0xAA4150
void* MemoryManager::Reallocate(void* apOldMem, size_t auiNewSize) {
	return ThisStdCall<void*>(0xAA4150, MemoryManager::GetSingleton(), apOldMem, auiNewSize);
}

// 0xAA4060
void MemoryManager::Deallocate(void* apMemory){
	ThisStdCall(0xAA4060, MemoryManager::GetSingleton(), apMemory);
}

void* MemoryManager::AllocateScrap(size_t aSize, UInt32 aAlignment) {
	return GetThreadScrapHeap()->Allocate(aSize, aAlignment);
}

void MemoryManager::DeallocateScrap(void* apMemory) {
	GetThreadScrapHeap()->Deallocate(apMemory);
}

void MemoryManager::EnterContext(UInt32& apPrevious, UInt32 auiNew){
	TLSData* pTLSData = TLSData::GetTLSData();
	apPrevious = pTLSData->uiHeapIndex;
	pTLSData->uiHeapIndex = auiNew;
}

void MemoryManager::LeaveContext(UInt32& apPrevious) {
	TLSData::SetHeapIndex(apPrevious);
}
