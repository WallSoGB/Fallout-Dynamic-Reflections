#include "NiMemory.hpp"

// 0xAA13E0
void* NiNew(size_t stSize) {
    return CdeclCall<void*>(0xAA13E0, stSize);
}

// 0xAA1070
void* NiAlloc(size_t stSize) {
    return CdeclCall<void*>(0xAA1070, stSize);
}

// 0xAA10F0
void NiFree(void* pvMem) {
    CdeclCall(0xAA10F0, pvMem);
}

// 0xAA1110
void NiAlignedFree(void* pvMem) {
    CdeclCall(0xAA1110, pvMem);
}
