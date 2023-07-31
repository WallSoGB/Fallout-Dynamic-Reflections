#pragma once

#include "NiMemObject.hpp"
#include "NiSmartPointer.hpp"
#include "NiGlobalStringTable.hpp"

NiSmartPointer(NiFixedString);

class NiFixedString : NiMemObject {
public:
	NiFixedString();
	NiFixedString(const char* pcString);
	NiFixedString(const NiFixedString& kString);
	~NiFixedString();

	NiGlobalStringTable::GlobalStringHandle m_kHandle;

	NiFixedString& operator=(const char* pcString);
};

ASSERT_SIZE(NiFixedString, 0x4)