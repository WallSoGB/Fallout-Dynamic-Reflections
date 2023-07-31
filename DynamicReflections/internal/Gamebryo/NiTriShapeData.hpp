#pragma once

#include "NiTriBasedGeomData.hpp"

NiSmartPointer(NiTriShapeData);

class NiTriShapeData : public NiTriBasedGeomData {
public:
	NiTriShapeData();
	~NiTriShapeData();

	class SharedNormalArray : public NiMemObject
	{
	public:
		UInt16 m_usNumSharedNormals;
		UInt16* m_pusSharedNormalIndexArray;
	};

	class SNAMemBlock : public NiMemObject
	{
	public:
		UInt16* m_pusBlock;
		UInt16* m_pusFreeBlock;
		UInt32 m_uiBlockSize;
		UInt32 m_uiFreeBlockSize;

		SNAMemBlock* m_pkNext;
	};

	UInt32 m_uiTriListLength;
	UInt16* m_pusTriList;
	NiTriShapeData::SharedNormalArray* m_pkSharedNormals;
	UInt16 m_usSharedNormalsArraySize;
	SNAMemBlock* m_pkSNAMemoryBlocks;

	CREATE_OBJECT(NiTriShapeData, 0xA7B790)
};

ASSERT_SIZE(NiTriShapeData, 0x58)