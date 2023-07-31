#pragma once

template <class T_Data> class NiTLargeArray {
public:
	NiTLargeArray();
	~NiTLargeArray();

	virtual void* Destructor(bool doFree);								// 000

	T_Data* m_pBase;     // pointer to the array storage
	UInt32 m_uiMaxSize;  // number of slots in array
	UInt32 m_uiSize;     // first available empty slot in array
	UInt32 m_uiESize;    // number of filled slots
	UInt32 m_uiGrowBy;   // number of slots to grow array when full

	T_Data operator[](UInt32 idx) {
		if (idx < m_uiSize)
			return m_pBase[idx];
		return NULL;
	}

	T_Data Get(UInt32 idx) { return (*this)[idx]; }

	UInt32 Length(void) { return m_uiSize; }
};

template <class T_Data>
class NiTLargeObjectArray : public NiTLargeArray<T_Data> {
};

template <class T_Data>
class NiTLargePrimitiveArray : public NiTLargeArray<T_Data> {
};