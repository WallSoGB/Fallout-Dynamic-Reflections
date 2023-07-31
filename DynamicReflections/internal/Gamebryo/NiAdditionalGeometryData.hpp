#pragma once

#include "NiObject.hpp"

NiSmartPointer(NiAdditionalGeometryData);

class NiAdditionalGeometryData : public NiObject {
public:
	NiAdditionalGeometryData();
	~NiAdditionalGeometryData();

	class NiAGDDataStream {
	public:
		UInt8  m_ucflags;
		UInt32 m_uiType;
		UInt32 m_uiUnitSize;
		UInt32 m_uiTotalSize;
		UInt32 m_uiStride;
		UInt32 m_uiBlockIndex;
		UInt32 m_uiBlockOffset;
	};

	class NiAGDDataBlock {
	public:
		UInt32 m_uiDataBlockSize;
		UInt8* m_pucDataBlock;
	};

	UInt32 m_uiRevID;
	UInt16 m_usVertexCount;
	UInt32 m_uiDataStreamCount;
	NiAGDDataStream* m_pkDataStreamEntries;
	UInt32 unk18;
	NiTPrimitiveArray<NiAGDDataBlock*> m_aDataBlocks;

	CREATE_OBJECT(NiAdditionalGeometryData, 0xA73E20)
};

ASSERT_SIZE(NiAdditionalGeometryData, 0x2C)