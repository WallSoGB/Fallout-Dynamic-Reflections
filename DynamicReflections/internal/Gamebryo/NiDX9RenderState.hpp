#pragma once

#include "NiD3DRenderState.hpp"
#include <d3d9caps.h>

class NiDX9RenderState : public NiD3DRenderState {
public:
	bool m_bDeclaration;
	UInt32 m_uiCurrentFVF;
	UInt32 m_uiPreviousFVF;
	LPDIRECT3DVERTEXDECLARATION9 m_hCurrentVertexDeclaration;
	LPDIRECT3DVERTEXDECLARATION9 m_hPreviousVertexDeclaration;
	bool m_bUsingSoftwareVP;
	D3DCAPS9 m_kD3DCaps9;
};

ASSERT_SIZE(NiDX9RenderState, 0x1248);