#include "NiFixedString.hpp"
#include "NiGlobalStringTable.hpp"

NiFixedString::NiFixedString() {
	m_kHandle = nullptr;
}

// 0x438170
NiFixedString::NiFixedString(const char* pcString) {
	if (pcString)
		m_kHandle = NiGlobalStringTable::AddString(pcString);
	else
		m_kHandle = nullptr;
}

// 0x4381B0
NiFixedString::~NiFixedString() {
	NiGlobalStringTable::DecRefCount(this);
}

// 0xA2E750
NiFixedString& NiFixedString::operator=(const char* pcString) {
	ThisStdCall(0xA2E750, this, pcString);
	return *this;
}
