#include "BSTextureManager.hpp"

BSRenderedTexture* BSTextureManager::NewRenderedTexture(UInt32 uiWidth, UInt32 uiHeight, UInt32 auiFlags, D3DFORMAT eFormat, UInt32 auiMSAA){
	if (auiMSAA) {
		auiFlags |= BSTM_CF_USE_MSAA;
	}
	return ThisStdCall<BSRenderedTexture*>(0xB6D170, BSTextureManager::GetSingleton(),
		NiDX9Renderer::GetSingleton(), uiWidth, uiHeight, eFormat, 0, auiFlags, 0, auiMSAA, 0, 0);
}

BSRenderedTexture* BSTextureManager::NewRenderedCubemap(UInt32 uiSize, UInt32 auiFlags, D3DFORMAT eFormat, UInt32 auiMSAA) {
	auiFlags |= BSTM_CF_CUBE_MAP;
	return NewRenderedTexture(uiSize, uiSize, auiFlags, eFormat, auiMSAA);
}