#pragma once

#include "NiRenderedTexture.hpp"
#include "NiRenderTargetGroup.hpp"
#include "NiRenderedCubeMap.hpp"
#include "BSString.hpp"
#include "NiDX9TextureData.hpp"

NiSmartPointer(BSRenderedTexture);

class BSRenderedTexture : public NiObject {
public:
	NiRenderTargetGroupPtr spRenderTargetGroups[6];
	NiRenderTargetGroupPtr spSomeRT;
	NiObject* unk024;
	NiObject* unk028;
	UInt32 eType; // BSTextureManager::RenderTargetTypes
	NiRenderedTexturePtr spRenderedTextures[4];

	bool SaveTexture(const char* path, const D3DXIMAGE_FILEFORMAT aeFormat);

	static BSRenderedTexture* Create(BSStringT* apName, const UInt32 uiWidth, const UInt32 uiHeight,
		NiTexture::FormatPrefs* kPrefs, Ni2DBuffer::MultiSamplePreference eMSAAPref,
		bool bUseDepthStencil, NiDepthStencilBuffer* pkDSBuffer, UInt32 a7, UInt32 uiBackgroundColor);

	static BSRenderedTexture* Create(const UInt32 uiWidth, const UInt32 uiHeight);

	static BSRenderedTexture* CreateCubeMap(const UInt32 auiSize);

	NiRenderedTexture* GetTexture(const UInt32 uiIndex) {
		return ThisStdCall<NiRenderedTexture*>(0x4BC320, this, uiIndex);
	}

	NiRenderTargetGroup* GetRenderTargetGroup();

	void SetOffScreenRenderTargetGroup(UInt32 auiClearMode);

	void SetOnScreenRenderTargetGroup(UInt32 auiClearMode);

	void SetRenderTargetGroup(UInt32 auiClearMode);

	static __forceinline void SwitchRTGroups() {
		CdeclCall(0xB6B840);
	}

	UInt32 GetWidth(UInt32 auiTexture);

	UInt32 GetHeight(UInt32 auiTexture);
};

ASSERT_SIZE(BSRenderedTexture, 0x40);