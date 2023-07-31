#pragma once

#include "NiObject.hpp"
#include "NiFloatKey.hpp"

class NiFloatData : public NiObject {
public:
	UInt32 m_uiNumKeys;
	NiFloatKey* m_pkKeys;
	NiFloatKey::KeyType m_eType;
	UInt8 m_ucKeySize;
	UInt8 pad15[3];
};