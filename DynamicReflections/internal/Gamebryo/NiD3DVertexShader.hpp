#pragma once

#include "NiD3DShaderProgram.hpp"

NiSmartPointer(NiD3DVertexShader);

class NiD3DVertexShader : public NiD3DShaderProgram {
public:
	virtual UInt32 GetUsage();
	virtual void SetUsage(UInt32 uiUsage);
	virtual LPDIRECT3DVERTEXSHADER9 GetShaderHandle();
	virtual void SetShaderHandle(LPDIRECT3DVERTEXSHADER9 hShader);
	virtual LPDIRECT3DVERTEXSHADER9 GetVertexDeclaration();
	virtual void SetVertexDeclaration(LPDIRECT3DVERTEXSHADER9 hShader);
	virtual bool GetSoftwareVertexProcessing();
	virtual void SetSoftwareVertexProcessing(bool bSoftwareVP);
	virtual void DestroyRendererData();
	virtual void RecreateRendererData();

	bool m_bSoftwareVP;
	UInt32 m_uiUsage;
	LPDIRECT3DVERTEXSHADER9 m_hShader;
	LPDIRECT3DVERTEXDECLARATION9 m_hDecl;
};

ASSERT_SIZE(NiD3DVertexShader, 0x3C);