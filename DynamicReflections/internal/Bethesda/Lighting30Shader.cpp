#include "Lighting30Shader.hpp"

Lighting30Shader* Lighting30Shader::GetShader() {
	return (Lighting30Shader*)BSShaderManager::GetShader(BSShaderManager::BSSM_SHADER_LIGHTING30);
}

NiD3DPixelShader* Lighting30Shader::GetPixelShader(UInt32 auID) {
	return ((NiD3DPixelShaderPtr*)0x1200C48)[auID];
}

void Lighting30Shader::SetPixelShader(UInt32 auID, NiD3DPixelShader* apPixelShader) {
	((NiD3DPixelShaderPtr*)0x1200C48)[auID] = apPixelShader;
}

void Lighting30Shader::InitPasses() {
	ThisStdCall(0xC072C0, this);
}
