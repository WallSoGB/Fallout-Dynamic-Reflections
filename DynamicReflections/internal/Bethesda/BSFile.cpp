#include "BSFile.hpp"

UInt32 BSFile::ReadBuffer(void* apData, UInt32 auiSize) {
    return ThisStdCall(0x462D80, this, apData, auiSize);
}
