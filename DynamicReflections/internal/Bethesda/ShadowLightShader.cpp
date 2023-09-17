#include "ShadowLightShader.hpp"

// 0xB7C0A0
void ShadowLightShader::SetDiffuseMap(BSShaderPPLightingProperty* apShaderProp, UInt32 auiStageNumber, UInt32 auiTextureNumber) {
    ThisStdCall(0xB7C0A0, this, apShaderProp, auiStageNumber, auiTextureNumber);
}
