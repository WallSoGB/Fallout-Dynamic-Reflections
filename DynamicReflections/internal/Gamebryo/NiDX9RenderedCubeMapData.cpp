#include "NiDX9RenderedCubeMapData.hpp"
#include "NiDX9Renderer.hpp"

// 0xE900C0
NiPixelFormat* __fastcall NiDX9RenderedCubeMapData::CreateSurf(NiDX9RenderedCubeMapData* apThis, void*, NiRenderedCubeMap* apTexture) {
    if (!apTexture)
        return nullptr;

    UInt32 uiSize = apTexture->GetWidth();
    apThis->m_uiHeight = uiSize;
    apThis->m_uiWidth = uiSize;
    apThis->m_uiLevels = 1;
    NiPixelFormat* pPixelFormat = CdeclCall<NiPixelFormat*>(0xE89ED0, &apTexture->m_kFormatPrefs, apThis->m_pkRenderer->m_aapkTextureFormats[3]);
    D3DFORMAT eFormat = pPixelFormat->m_uiRendererHint;

    if (apTexture->bUseCustomFormat)
        eFormat = apTexture->eCustomFormat;

    LPDIRECT3DCUBETEXTURE9 pTexture = nullptr;
    if (SUCCEEDED(apThis->m_pkRenderer->GetD3DDevice()->CreateCubeTexture(uiSize, 0, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, eFormat, D3DPOOL_DEFAULT, &pTexture, 0))) {
        pTexture->SetAutoGenFilterType(D3DTEXF_LINEAR);
        apThis->m_pkD3DTexture = pTexture;
        return pPixelFormat;
    }
    else {
        apThis->m_pkD3DTexture = nullptr;
        return nullptr;
    }
}