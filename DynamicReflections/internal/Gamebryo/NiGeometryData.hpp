#pragma once

#include "NiObject.hpp"
#include "NiBound.hpp"
#include "NiColor.hpp"
#include "NiPoint2.hpp"
#include "NiAdditionalGeometryData.hpp"
#include "NiGeometryBufferData.hpp"
#include "NiShaderDeclaration.hpp"

NiSmartPointer(NiGeometryData);

class NiGeometryData : public NiObject {
public:

	virtual void SetActiveVertexCount(UInt16 usActive);
	virtual UInt16 GetActiveVertexCount();
	virtual void Unk_25();
	virtual void Unk_26(UInt32);
	virtual bool ContainsVertexData(NiShaderDeclaration::ShaderParameter eParameter);
	virtual void Unk_28();

	enum Consistency {
		MUTABLE = 0x0000,
		STATIC = 0x4000,
		VOLATILE = 0x8000,
		CONSISTENCY_MASK = 0xF000,
	};

	UInt16 m_usVertices;
	UInt16 m_usID;
	UInt16 m_usDataFlags;
	UInt16 m_usDirtyFlags;
	NiBound m_kBound;
	NiPoint3* m_pkVertex;
	NiPoint3* m_pkNormal;
	NiColorA* m_pkColor;
	NiPoint2* m_pkTexture;
	NiAdditionalGeometryData* m_spAdditionalGeomData;
	NiGeometryBufferData* m_pkBuffData;
	UInt8 m_ucKeepFlags;
	UInt8 m_ucCompressFlags;
	UInt8 Unk3A;
	UInt8 Unk3B;
	bool m_bCanSave;

	static void __fastcall LoadBinary_Hook(NiGeometryData* apData, void*, NiStream* kStream);
	static void __fastcall SaveBinary_Hook(NiGeometryData* apData, void*, NiStream* kStream);

	NiPoint3* GetVertices();
	NiPoint3* GetNormals();
	NiColorA* GetColors();
};

ASSERT_SIZE(NiGeometryData, 0x40);