#pragma once

#include "NiTriBasedGeomData.hpp"

NiSmartPointer(NiTriStripsData);

class NiTriStripsData : public NiTriBasedGeomData {
public:
	NiTriStripsData();
	~NiTriStripsData();

	UInt16 m_usStrips;
	UInt16* m_pusStripLengths;
	UInt16* m_pusStripLists;

	CREATE_OBJECT(NiTriStripsData, 0xA75EC0)
};

ASSERT_SIZE(NiTriStripsData, 0x50);