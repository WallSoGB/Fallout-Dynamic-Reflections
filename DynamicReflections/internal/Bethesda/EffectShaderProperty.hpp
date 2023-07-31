#pragma once

#include "NiRefObject.hpp"
#include "NiColor.hpp"

class NiSourceTexture;

NiSmartPointer(EffectShaderProperty);

class EffectShaderProperty : public NiRefObject {
public:
	EffectShaderProperty();
	~EffectShaderProperty();

	NiSourceTexture* texture08;
	NiColorA newFillColor;
	NiColorA newEdgeColor;
	NiColorA fillColor;
	NiColorA edgeColor;
	float fAnimU;
	float fAnimY;
	float unk54;
	float unk58;
	int unk5C;
	int unk60;
	int unk64;
	int unk68;
	NiSourceTexture* texture6C;
	int dword70;
};

ASSERT_SIZE(EffectShaderProperty, 0x74)