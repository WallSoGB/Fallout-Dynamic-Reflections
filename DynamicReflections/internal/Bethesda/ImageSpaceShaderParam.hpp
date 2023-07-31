#pragma once

#include "ImageSpaceEffectParam.hpp"
#include "NiTMap.hpp"
#include "NiD3DShaderConstantMap.hpp"

class ImageSpaceShaderParam : public ImageSpaceEffectParam {
public:
	int dword24;
	BOOL bClear;
	float float2C;
	float float30;
	float float34;
	float float38;
	float* pfVertexConstantGroup;
	int iVSize;
	float* pfPixelConstantGroup;
	int iPSize;
	NiD3DShaderConstantMap* vertexConstantMap;
	NiD3DShaderConstantMap* pixelConstantMap;
	UInt16 word54;
	bool byte56;
	NiTObjectArray<NiPointer<NiTexture>> pInputTextures;
	NiTPrimitiveArray<NiTexturingProperty::FilterMode> pInputFilterModes;
	NiTMap<UInt32, UInt32> TMap78;

	static ImageSpaceShaderParam* Create(ImageSpaceShaderParam* apThis);

	void ResizeConstantGroup(UInt32 auiCertexGroupSize, UInt32 auiPixelGroupSize);

	void SetVertexConstants(UInt32 auiIndex, float afVal1, float afVal2, float afVal3, float afVal4);
	void SetPixelConstants(UInt32 auiIndex, float afVal1, float afVal2, float afVal3, float afVal4);

	void Free();
};

ASSERT_SIZE(ImageSpaceShaderParam, 0x88);