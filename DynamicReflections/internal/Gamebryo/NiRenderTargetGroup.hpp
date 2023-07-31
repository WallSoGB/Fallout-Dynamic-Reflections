#pragma once

#include "NiObject.hpp"
#include "Ni2DBuffer.hpp"
#include "NiDepthStencilBuffer.hpp"

class NiDX9Renderer;

NiSmartPointer(NiRenderTargetGroup);

class NiRenderTargetGroup : public NiObject {
public:
	virtual UInt32						GetWidth(UInt32 uiIndex);
	virtual UInt32						GetHeight(UInt32 uiIndex);
	virtual UInt32						GetDepthStencilWidth();
	virtual UInt32						GetDepthStencilHeight();
	virtual const NiPixelFormat*		GetPixelFormat(UInt32 uiIndex);
	virtual const NiPixelFormat*		GetDepthStencilPixelFormat();
	virtual UInt32						GetBufferCount();
	virtual bool						AttachBuffer(Ni2DBuffer* pkBuffer, UInt32 uiIndex);
	virtual bool						AttachDepthStencilBuffer(NiDepthStencilBuffer* pkDepthBuffer);
	virtual Ni2DBuffer*					GetBuffer(UInt32 uiIndex);
	virtual NiDepthStencilBuffer*		GetDepthStencilBuffer();
	virtual bool						GetByte08();
	virtual void						SetByte08();
	virtual const RendererData*			GetRendererData();
	virtual void						SetRendererData(RendererData* pkRendererData);
	virtual Ni2DBuffer::RendererData*	GetBufferRendererData(UInt32 uiIndex);
	virtual Ni2DBuffer::RendererData*	GetDepthStencilBufferRendererData();

	class RendererData;

	bool						Unk08;
	Ni2DBufferPtr				m_aspBuffers[4];
	UInt32						m_uiNumBuffers;
	NiDepthStencilBufferPtr		m_spDepthStencilBuffer;
	RendererData*				m_pkRendererData;

	static NiRenderTargetGroup* Create(UInt32 uiNumBuffers, NiDX9Renderer* pkRenderer) { return CdeclCall<NiRenderTargetGroup*>(0xEE8710, uiNumBuffers, pkRenderer); };

	static void SetRenderTargetGroup(NiRenderTargetGroup* apTarget, UInt32 uiClearMode);
	static void SetOffScreenRenderTargetGroup(NiRenderTargetGroup* apTarget, UInt32 auiClearMode);
	static void SetOnScreenRenderTargetGroup(NiRenderTargetGroup* apTarget, UInt32 auiClearMode);
};

ASSERT_SIZE(NiRenderTargetGroup, 0x28);