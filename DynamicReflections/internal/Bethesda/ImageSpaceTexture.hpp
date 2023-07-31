#pragma once

#include "BSRenderedTexture.hpp"

NiSmartPointer(ImageSpaceTexture);

class ImageSpaceTexture {
public:
	enum TextureFilterMode
	{
		TEXTURE_FILTER_MODE_NEAREST = 0x0,
		TEXTURE_FILTER_MODE_BILERP = 0x1,
		TEXTURE_FILTER_MODE_TRILERP = 0x2,
		TEXTURE_FILTER_MODE_ANISO = 0x3,
		TEXTURE_FILTER_MODE_COMP_BILERP = 0x4,
		TEXTURE_FILTER_MODE_COUNT = 0x5,
		TEXTURE_FILTER_MODE_DEFAULT = 0x3,
	};

	enum TextureAddressMode
	{
		TEXTURE_ADDRESS_MODE_CLAMP_S_CLAMP_T = 0x0,
		TEXTURE_ADDRESS_MODE_CLAMP_S_WRAP_T = 0x1,
		TEXTURE_ADDRESS_MODE_WRAP_S_CLAMP_T = 0x2,
		TEXTURE_ADDRESS_MODE_WRAP_S_WRAP_T = 0x3,
		TEXTURE_ADDRESS_MODE_COUNT = 0x4,
		TEXTURE_ADDRESS_MODE_DEFAULT = 0x0,
	};

	ImageSpaceTexture() : spTexture(0), iFilterMode(TEXTURE_FILTER_MODE_DEFAULT), iClampMode(TEXTURE_ADDRESS_MODE_DEFAULT), byte0(false), bIsRenderedTexture(false), bAcquiredTarget(false) { };
	~ImageSpaceTexture();

	bool byte0;
	bool bIsRenderedTexture;
	bool bAcquiredTarget;
	NiObjectPtr spTexture;
	TextureFilterMode iFilterMode;
	TextureAddressMode iClampMode;

	void SetTextureRenderTarget(BSRenderedTexture* pNewTexture) { spTexture = pNewTexture; bIsRenderedTexture = true; }
	void SetTexture(NiTexture* pNewTexture) { spTexture = pNewTexture; bIsRenderedTexture = false; }
	void Reset() { ThisStdCall(0xBA39A0, this); }
	void Free() {ThisStdCall(0xBA3A00, this); }

	NiTexture* GetRenderTarget() { return bIsRenderedTexture ? static_cast<BSRenderedTexture*>(spTexture.m_pObject)->GetTexture(0) : static_cast<NiTexture*>(spTexture.m_pObject); }
	BSRenderedTexture* GetTexture() { return bIsRenderedTexture ? static_cast<BSRenderedTexture*>(spTexture.m_pObject) : 0; }
};

ASSERT_SIZE(ImageSpaceTexture, 0x10);