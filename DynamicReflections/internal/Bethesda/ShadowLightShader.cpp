#include "ShadowLightShader.hpp"
#include "BSShaderManager.hpp"

// 0xB7C0A0
void ShadowLightShader::SetDiffuseMap(BSShaderPPLightingProperty* apShaderProp, UInt32 auiStageNumber, UInt32 auiTextureNumber) {
    ThisStdCall(0xB7C0A0, this, apShaderProp, auiStageNumber, auiTextureNumber);
}

ShadowLightShader* ShadowLightShader::GetShader() {
    return static_cast<ShadowLightShader*>(BSShaderManager::GetShader(BSShaderManager::BSSM_SHADER_SHADOWLIGHT));
}

NiD3DVertexShader* ShadowLightShader::GetVertexShader(UInt32 auID) {
    return ((NiD3DVertexShaderPtr*)0x11FDD88)[auID];
}

void ShadowLightShader::SetVertexShader(UInt32 auID, NiD3DVertexShader* apShader) {
    ((NiD3DVertexShaderPtr*)0x11FDD88)[auID] = apShader;
}

NiD3DPixelShader* ShadowLightShader::GetPixelShader(UInt32 auID) {
    return ((NiD3DPixelShaderPtr*)0x11FDA48)[auID];
}

void ShadowLightShader::SetPixelShader(UInt32 auID, NiD3DPixelShader* apShader) {
    ((NiD3DPixelShaderPtr*)0x11FDA48)[auID] = apShader;
}

void ShadowLightShader::InitPasses_2xEnvMap() {
    StdCall(0xBFBF60);
}
