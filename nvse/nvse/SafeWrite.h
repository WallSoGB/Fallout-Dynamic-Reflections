#pragma once

void SafeWrite8(UInt32 addr, UInt32 data);
void SafeWrite16(UInt32 addr, UInt32 data);
void SafeWrite32(UInt32 addr, UInt32 data);
void SafeWriteBuf(UInt32 addr, void * data, UInt32 len);

// 5 bytes
void WriteRelJump(UInt32 jumpSrc, UInt32 jumpTgt);
void WriteRelCall(UInt32 jumpSrc, UInt32 jumpTgt);


// 6 bytes
void WriteRelJnz(UInt32 jumpSrc, UInt32 jumpTgt);
void WriteRelJle(UInt32 jumpSrc, UInt32 jumpTgt);

void PatchMemoryNop(ULONG_PTR Address, SIZE_T Size);

template <typename T>
void WriteRelCall(UInt32 jumpSrc, T jumpTgt)
{
	WriteRelCall(jumpSrc, (UInt32)jumpTgt);
}

template <typename T>
void WriteRelJump(UInt32 jumpSrc, T jumpTgt)
{
	WriteRelJump(jumpSrc, (UInt32)jumpTgt);
}

void ReplaceCall(UInt32 jumpSrc, UInt32 jumpTgt);

template <typename T>
void ReplaceCall(UInt32 jumpSrc, T jumpTgt)
{
	ReplaceCall(jumpSrc, (UInt32)jumpTgt);
}