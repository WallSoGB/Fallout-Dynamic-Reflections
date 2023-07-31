#pragma once

#include "NiGeometryData.hpp"

NiSmartPointer(NiTriBasedGeomData);

class NiTriBasedGeomData : public NiGeometryData {
public:
	NiTriBasedGeomData();
	~NiTriBasedGeomData();

	virtual void Unk_29();
	virtual UInt16 GetActiveTriangleCount();
	virtual UInt16 GetTriangleIndices(UInt16 i, UInt16& i0, UInt16& i1, UInt16& i2);
	virtual UInt16 GetStripData(UInt16& usStrips, const UInt16*& pusStripLengths, const UInt16*& pusTriList, UInt16& uiStripLengthSum);

	UInt16 m_usTriangles;
	UInt16 m_usActiveTriangles;
};

ASSERT_OFFSET(NiTriBasedGeomData, m_usTriangles, 0x40);
ASSERT_OFFSET(NiTriBasedGeomData, m_usActiveTriangles, 0x42);