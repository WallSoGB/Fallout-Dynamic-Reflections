#pragma once

#include "BSShaderPPLightingProperty.hpp"

NiSmartPointer(Lighting30ShaderProperty);
NiRTTIAddress(Lighting30ShaderProperty, 0x12007B0);

class Lighting30ShaderProperty : public BSShaderPPLightingProperty {
public:
	Lighting30ShaderProperty();
	~Lighting30ShaderProperty();

	int unk104;

	CREATE_OBJECT(Lighting30ShaderProperty, 0xBB45D0);

	static Lighting30ShaderProperty* Create(BSShaderPPLightingProperty* apProperty);
};

ASSERT_SIZE(Lighting30ShaderProperty, 0x108);

typedef Lighting30ShaderProperty NoFaderShaderProperty;