#pragma once

template <typename T> struct BSSimpleArray {
	virtual void  Destroy(bool);
	virtual void* Allocate(UInt32);
	virtual void* FreeArg(UInt32);
	virtual void* Resize4BytesMemebers(UInt32);

	T* pBuffer;	  // 04
	UInt32 uiSize;  // 08
	UInt32 uiAllocSize; // 0C

	// this only compiles for pointer types
	T operator[](UInt32 idx)
	{
		if (idx < uiSize)
			return pBuffer[idx];
		return NULL;
	}

	UInt32 GetSize() { return uiSize; }
	UInt32 GetAllocSize() { return uiAllocSize; }
	bool IsEmpty() { return uiSize == 0; }
};

ASSERT_SIZE(BSSimpleArray<void>, 0x10);