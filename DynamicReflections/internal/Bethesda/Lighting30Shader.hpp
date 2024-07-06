#pragma once

#include "BSShader.hpp"
#include "Lighting30ShaderProperty.hpp"
#include "NiPoint4.hpp"

class Lighting30Shader : public BSShader {
public:
	virtual void SetupShadowTexture(UInt32 aeRenderPass, Lighting30ShaderProperty* apShaderProperty);
	virtual void SetupEffectTextures(UInt32 aeRenderPass, Lighting30ShaderProperty* apShaderProperty);
	virtual void Func_81(UInt32 aeRenderPass, Lighting30ShaderProperty* apShaderProp);
	virtual void InitShaders();
	virtual void InitVertexShaders();
	virtual void InitPixelShaders();
	virtual void CreatePasses();

	NiD3DShaderConstantMap* pixelConstantMapTexEffect;
	NiD3DShaderConstantMap* vertexConstantMap;
	NiD3DShaderConstantMap* pPixelConstantMap74;
	NiD3DShaderConstantMap* pVertexConstantMap78;
	NiDX9ShaderDeclaration* pShaderDeclaration7C;
	NiDX9ShaderDeclaration* pShaderDeclaration80;
	NiDX9ShaderDeclaration* pShaderDeclaration84_VC;
	NiDX9ShaderDeclaration* pShaderDeclaration88;
	NiDX9ShaderDeclaration* pShaderDeclaration8C_S;
	NiDX9ShaderDeclaration* pShaderDeclaration90;
	NiDX9ShaderDeclaration* pShaderDeclaration94_VC_S;
	NiDX9ShaderDeclaration* pShaderDeclaration98;
	DWORD dword9C;
	DWORD dwordA0;

	enum PixelEntries {
		kPX_EnvMapToggles = 7,
	};
	
	static Lighting30Shader* GetShader();

	static NiD3DPixelShader* GetPixelShader(UInt32 auID);

	static void SetPixelShader(UInt32 auID, NiD3DPixelShader* apPixelShader);

	void InitPasses();
};

ASSERT_SIZE(Lighting30Shader, 0xA4);

// Custom
class Lighting30ShaderManager {
public:
	struct EnvToggles {
		float x;
		float y;
		float fEnvMapScale;
		float bHasMask;
	};

	struct PixelConstants {
		static __forceinline EnvToggles* GetEnvToggles() {
			return (EnvToggles*)0x1201BE0;
		}
	};

	static __forceinline NiShaderConstantMapEntry* GetPixelConstantMapEntry(Lighting30Shader::PixelEntries index) {
		return ((NiShaderConstantMapEntry**)0x12010C4)[index];
	}
};