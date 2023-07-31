#include "BSRenderedTexture.hpp"
#include "NiDX9Renderer.hpp"

bool BSRenderedTexture::SaveTexture(const char* path, D3DXIMAGE_FILEFORMAT aeFormat) {
	return ((NiDX9TextureData*)spRenderedTextures[0].m_pObject->m_pkRendererData)->SaveTexture(path, aeFormat);
}

BSRenderedTexture* BSRenderedTexture::Create(BSStringT* apName, const UInt32 uiWidth, const UInt32 uiHeight, NiTexture::FormatPrefs* kPrefs, Ni2DBuffer::MultiSamplePreference eMSAAPref, bool bUseDepthStencil, NiDepthStencilBuffer* pkDSBuffer, UInt32 a7, UInt32 uiBackgroundColor) {
	return CdeclCall<BSRenderedTexture*>(0xB6B610, apName, uiWidth, uiHeight, kPrefs, eMSAAPref, bUseDepthStencil, pkDSBuffer, a7, uiBackgroundColor);
}

BSRenderedTexture* BSRenderedTexture::Create(const UInt32 uiWidth, const UInt32 uiHeight) {
	NiTexture::FormatPrefs kPrefs(NiTexture::FormatPrefs::PIX_DEFAULT, NiTexture::FormatPrefs::ALPHA_DEFAULT, NiTexture::FormatPrefs::NO);
	return BSRenderedTexture::Create(0, uiWidth, uiHeight, &kPrefs, Ni2DBuffer::MULTISAMPLE_2, 1, 0, 0, 0);
}

BSRenderedTexture* BSRenderedTexture::CreateCubeMap(const UInt32 auiSize) {
	NiTexture::FormatPrefs kPrefs(NiTexture::FormatPrefs::PIX_DEFAULT, NiTexture::FormatPrefs::ALPHA_DEFAULT, NiTexture::FormatPrefs::NO);
	NiRenderedCubeMap* pCubeMap = NiRenderedCubeMap::Create(auiSize, NiDX9Renderer::GetSingleton(), kPrefs);
	BSRenderedTexture* pTexture = NiCreate<BSRenderedTexture>(0xB6B380, pCubeMap, 0, 0);
	return pTexture;
}

NiRenderTargetGroup* BSRenderedTexture::GetRenderTargetGroup() {
	if (!this)
		return 0;
	NiRenderedTexture* pTexture = spRenderedTextures[0];
	if (pTexture && pTexture->GetRTTI() == NiRenderedCubeMap__ms_RTTI) {
		return spRenderTargetGroups[((NiRenderedCubeMap*)(pTexture))->m_eFace];
	}
	else
		return spRenderTargetGroups[0];
}

void BSRenderedTexture::SetOffScreenRenderTargetGroup(UInt32 auiClearMode) {
	// Code moved to NiRenderTargetGroup::SetOffScreenRenderTargetGroup directly
	NiRenderTargetGroup::SetOffScreenRenderTargetGroup(GetRenderTargetGroup(), (NiRenderer::ClearFlags)auiClearMode);
}

void BSRenderedTexture::SetOnScreenRenderTargetGroup(UInt32 auiClearMode) {
	NiRenderTargetGroup::SetOnScreenRenderTargetGroup(GetRenderTargetGroup(), (NiRenderer::ClearFlags)auiClearMode);
}

void BSRenderedTexture::SetRenderTargetGroup(UInt32 auiClearMode) {
	NiRenderTargetGroup* pTarget = GetRenderTargetGroup();
	if (pTarget)
		NiRenderTargetGroup::SetRenderTargetGroup(pTarget, (NiRenderer::ClearFlags)auiClearMode);
}

UInt32 BSRenderedTexture::GetWidth(UInt32 auiTexture) {
	NiRenderedTexture* pTexture = spRenderedTextures[auiTexture];
	if (!pTexture)
		return 0;
	return pTexture->GetWidth();
}

UInt32 BSRenderedTexture::GetHeight(UInt32 auiTexture) {
	NiRenderedTexture* pTexture = spRenderedTextures[auiTexture];
	if (!pTexture)
		return 0;
	return pTexture->GetHeight();
}