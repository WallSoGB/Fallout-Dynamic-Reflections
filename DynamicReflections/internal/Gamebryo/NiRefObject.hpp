#pragma once

#include "NiMemObject.hpp"
#include "NiSmartPointer.hpp"

NiSmartPointer(NiRefObject);

class NiRefObject : public NiMemObject {
public:
	NiRefObject();
	~NiRefObject();

	virtual void Destroy(bool bFreeThis);
	virtual void DeleteThis();

	UInt32 m_uiRefCount;

	__forceinline void IncRefCount() {
		InterlockedIncrement(&m_uiRefCount);
	}

	__forceinline void DecRefCount() {
		if (InterlockedDecrement(&m_uiRefCount) == 0)
			DeleteThis();
	}
};

ASSERT_SIZE(NiRefObject, 0x8);