#pragma once

#include "ImageSpaceTexture.hpp"
#include "ImageSpaceShaderParam.hpp"
#include "ImageSpaceEffectParam.hpp"

class ImageSpaceManager;
class NiScreenGeometry;
class NiDX9Renderer;

class ImageSpaceEffect {
public:
	virtual void Destroy(bool doFree);
	virtual void RenderShader(NiGeometry* apScreenShape, NiDX9Renderer* pkRenderer, ImageSpaceEffectParam* apParam, bool abEndFrame);
	virtual void Setup(ImageSpaceManager* pISManager, ImageSpaceEffectParam* apParam);
	virtual void Shutdown(void);
	virtual void BorrowTextures(ImageSpaceEffectParam* apParam);
	virtual void ReturnTextures(void);
	virtual bool IsActive(void);
	virtual bool UpdateParams(ImageSpaceEffectParam* apParam);

	bool bIsActive;
	bool bParamsChanged;
	NiTArray<ImageSpaceEffect> pEffectList;
	NiTArray<ImageSpaceShaderParam> pEffectParamList;
	NiTArray<ImageSpaceTexture> pTextures;
	NiTArray<int> pEffectInputs;
	NiTArray<int> pEffectOutput;

	void SetTexture(UInt32 aiIndex, ImageSpaceTexture* apTex, ImageSpaceTexture::TextureFilterMode aiFilterMode) {
		ThisStdCall(0xBA3CB0, this, aiIndex, apTex, aiFilterMode);
	}
};

ASSERT_SIZE(ImageSpaceEffect, 0x58)