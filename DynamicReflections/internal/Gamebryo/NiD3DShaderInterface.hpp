#pragma once

#include "NiShader.hpp"

class NiDX9Renderer;
class NiDX9RenderState;
class NiD3DShaderDeclaration;

class NiD3DShaderInterface : public NiShader {
public:
	virtual NiD3DShaderDeclaration* GetShaderDecl();
	virtual void SetShaderDecl(NiD3DShaderDeclaration* pkShaderDecl);
	virtual void HandleResetDevice(void* pkShaderDecl);
	virtual void HandleLostDevice();
	virtual void DestroyRendererData();
	virtual bool RecreateRendererData();
	virtual bool GetVSPresentAllPasses();
	virtual bool Unk_54();
	virtual bool Unk_55();
	virtual bool Unk_56();
	virtual bool GetIsBestImplementation();
	virtual void SetIsBestImplementation(bool bIsBest);

	IDirect3DDevice9* m_pkD3DDevice;
	NiDX9Renderer* m_pkD3DRenderer;
	NiDX9RenderState* m_pkD3DRenderState;
	bool m_bIsBestImplementation;
};

ASSERT_SIZE(NiD3DShaderInterface, 0x24);