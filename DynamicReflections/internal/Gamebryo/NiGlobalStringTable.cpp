#include "NiGlobalStringTable.hpp"

// 0xA5B690
NiGlobalStringTable::GlobalStringHandle NiGlobalStringTable::AddString(const char* pcString) {
    return CdeclCall<GlobalStringHandle>(0xA5B690, pcString);
}

// 0x4381B0
void NiGlobalStringTable::DecRefCount(NiFixedString* apString) {
    ThisStdCall(0x4381B0, apString);
}
