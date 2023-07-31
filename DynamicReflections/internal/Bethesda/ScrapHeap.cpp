#include "ScrapHeap.hpp"

// 0x866D10
ScrapHeapManager* ScrapHeapManager::GetSingleton() {
	return StdCall<ScrapHeapManager*>(0x866D10);
}

void ScrapHeapManager::FreeAllBuffers() {
	ThisStdCall(0xAA5C80, this);
}

// 0xAA5B70
void ScrapHeapManager::ReleaseBuffer(LPVOID lpAddress, int a3) {
	ThisStdCall(0xAA5B70, this, lpAddress, a3);
}

void ScrapHeapManager::FreeBuffers(UInt32 auiBuffersToFree) {
	ThisStdCall(0xAA5D40, this, auiBuffersToFree);
}

// 0xAA59B0
void* ScrapHeapManager::RequestBuffer(SIZE_T* apSize) {
	return ThisStdCall<void*>(0xAA59B0, this, apSize);
}

// 0xAA54A0
void* ScrapHeap::Allocate(UInt32 aSize, UInt32 aAlignment) {
	return ThisStdCall<void*>(0xAA54A0, this, aSize, aAlignment);
}

// 0xAA5610
void ScrapHeap::Deallocate(void* apMem) {
	ThisStdCall(0xAA5610, this, apMem);
}