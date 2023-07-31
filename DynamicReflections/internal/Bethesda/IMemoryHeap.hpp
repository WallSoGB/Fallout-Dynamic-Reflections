#pragma once

class IMemoryHeap {
public:
	virtual void Destroy(bool);
	virtual const char*  GetName();
	virtual void Unk_02();
	virtual void Unk_03(int, int);
	virtual bool Unk_04(UInt32);
	virtual void Unk_05();
	virtual void Unk_06(void*, bool);
	virtual UInt32 Unk_07(void*);
	virtual UInt32 Unk_08(void*, bool);
	virtual int Unk_09(int, int);
	virtual int Unk_10(int);
	virtual void Unk_11();
};