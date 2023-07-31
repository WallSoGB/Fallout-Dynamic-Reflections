#pragma once

#include "NiD3DShaderProgram.hpp"

NiSmartPointer(NiD3DPixelShader);

class NiD3DPixelShader : public NiD3DShaderProgram {
public:
	virtual LPDIRECT3DPIXELSHADER9 GetShaderHandle();
	virtual void SetShaderHandle(LPDIRECT3DPIXELSHADER9 hShader);
	virtual void DestroyRendererData(LPDIRECT3DPIXELSHADER9 hShader);
	virtual void RecreateRendererData();

	LPDIRECT3DPIXELSHADER9 m_hShader;
};

ASSERT_SIZE(NiD3DPixelShader, 0x30);