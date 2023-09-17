#pragma once

#include "NiProperty.hpp"

NiSmartPointer(NiShadeProperty);

class NiShadeProperty : public NiProperty {
public:
	NiShadeProperty();
	virtual ~NiShadeProperty();

	enum ShaderType : UInt32
	{
		kType_Lighting = 0x1,
		kType_DistantLOD = 0x2,
		kType_GeometryDecal = 0x3,
		kType_TallGrass = 0x4,
		kType_SpeedTreeLeaf = 0x6,
		kType_PPLighting = 0x8,
		kType_Hair = 0x9,
		kType_SpeedTreeBranch = 0xA,
		kType_SpeedTreeBillboard = 0xB,
		kType_Lighting30 = 0xC,
		kType_Sky = 0xD,
		kType_Water = 0xE,
		kType_Bolt = 0xF,
		kType_Particle = 0x11,
		kType_Precipitation = 0x12,
		kType_Tile = 0x13,
		kType_NoLighting = 0x15,
		kType_VolumetricFog = 0x16,
		kType_BloodSplatter = 0x17,
		kType_DistantTree = 0x18,
	};

	UInt16 m_usFlags;
	ShaderType m_eShaderType;

	CREATE_OBJECT(NiShadeProperty, 0xA814E0);

	__forceinline const char* GetShaderType() { return NiShadeProperty::GetShaderType(this->m_eShaderType); };
	static const char* GetShaderType(UInt32 eType);
};

ASSERT_SIZE(NiShadeProperty, 0x20);