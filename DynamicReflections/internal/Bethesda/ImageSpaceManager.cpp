#include "ImageSpaceManager.hpp"
#include "ImageSpaceEffect.hpp"

// 0xB8C830
void ImageSpaceManager::RenderEffect(ImageSpaceEffect* apEffect, NiDX9Renderer* apRenderer, BSRenderedTexture* apSourceTarget, BSRenderedTexture* apDestTarget, ImageSpaceEffectParam* apParam, bool abEndFrame) {
#if 0
	ThisStdCall(0xB8C830, this, apEffect, apRenderer, apSourceTarget, apDestTarget, apParam, abEndFrame);
#else
	DWORD uiHeapID;
	MemoryManager::EnterContext(uiHeapID, 39);

	ImageSpaceTexture Tex1 = ImageSpaceTexture();
	ImageSpaceTexture Tex2 = ImageSpaceTexture();
	Tex1.SetTextureRenderTarget(apSourceTarget);
	Tex2.SetTextureRenderTarget(apDestTarget);
	if (apEffect) {
		apEffect->SetTexture(0, &Tex2, ImageSpaceTexture::TEXTURE_FILTER_MODE_NEAREST);
		apEffect->SetTexture(1, &Tex1, ImageSpaceTexture::TEXTURE_FILTER_MODE_NEAREST);
		auto spShape = &spDynamicScreenTriShape;
		if (!bUseDynamicResolution)
			spShape = &spScreenTriShape;
		apEffect->RenderShader(spShape->m_pObject, apRenderer, apParam, abEndFrame);
		apEffect->SetTexture(0, 0, ImageSpaceTexture::TEXTURE_FILTER_MODE_NEAREST);
		apEffect->SetTexture(1, 0, ImageSpaceTexture::TEXTURE_FILTER_MODE_NEAREST);
	}
	MemoryManager::LeaveContext(uiHeapID);
#endif
}

void ImageSpaceManager::RenderEffect(ImageSpaceManager::EffectID aeID, NiDX9Renderer* apRenderer, BSRenderedTexture* apSourceTarget, BSRenderedTexture* apDestTarget, ImageSpaceEffectParam* apParam, bool abEndFrame) {
	ImageSpaceManager::RenderEffect(EffectList.m_pBase[aeID], apRenderer, apSourceTarget, apDestTarget, apParam, abEndFrame);
}
