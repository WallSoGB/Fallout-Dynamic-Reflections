#pragma once

#include "NiD3DShaderInterface.hpp"
#include "NiD3DShaderDeclaration.hpp"
#include "NiD3DShaderConstantMap.hpp"
#include "NiD3DPass.hpp"
#include "NiPropertyState.hpp"

class NiD3DRenderStateGroup;
class NiD3DShaderConstantMap;

class NiD3DShader : public NiD3DShaderInterface {
public:

	virtual void ResetPasses();

	bool m_bUsesNiRenderState;
	bool m_bUsesNiLightState;
	NiD3DShaderDeclarationPtr m_spShaderDecl;
	NiD3DRenderStateGroup* m_pkRenderStateGroup;
	NiD3DShaderConstantMapPtr m_spPixelConstantMap;
	NiD3DShaderConstantMapPtr m_spVertexConstantMap;
	UInt32 m_uiCurrentPass;

	static NiD3DPass* m_kPass;

	static NiD3DPass* GetCurrentPass();
};

ASSERT_SIZE(NiD3DShader, 0x3C);