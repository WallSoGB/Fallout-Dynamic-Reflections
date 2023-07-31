#pragma once

#include "Ni2DBuffer.hpp"
#include <d3d9.h>

class NiDX92DBufferData : public Ni2DBuffer::RendererData {
public:
	virtual void Unk3();
	virtual NiRTTI* GetRTTI();
	virtual void Unk5();
	virtual void Unk6();
	virtual void Unk7();
	virtual void Unk8();
	virtual void Unk9();
	virtual void Unk10();
	virtual void Unk11();
	virtual void Unk12();
	virtual void Unk13();
	virtual void Unk14();
	virtual void Unk15();
	virtual void Unk16();
	virtual void Unk17();
	virtual void Unk18();
	virtual void Unk19();
	virtual void Unk20();
	virtual bool DisplayFrame();
	virtual bool Shutdown();
	virtual bool Recreate(LPDIRECT3DDEVICE9 pkD3DDevice9);
	virtual bool SetRenderTarget(LPDIRECT3DDEVICE9 pkD3DDevice9, UInt32 uiTarget);
	virtual bool SetDepthTarget(LPDIRECT3DDEVICE9 pkD3DDevice9);
	virtual void Unk26();
	virtual void ReleaseReferences();

	LPDIRECT3DSURFACE9 m_pkSurface;
	int unk18;
	int unk1C;
};

ASSERT_SIZE(NiDX92DBufferData, 0x20);