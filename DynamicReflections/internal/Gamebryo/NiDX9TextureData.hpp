#pragma once

#include "NiPersistentSrcTextureRendererData.hpp"
#include "Defines.hpp"
#include "NiTexture.hpp"

class NiDX9Renderer;
class NiDX9SourceTextureData;
class NiDX9RenderedTextureData;
class NiDX9DynamicTextureData;

class NiDX9TextureData : public NiTexture::RendererData {
public:
	virtual UInt32 GetLevels();
	virtual LPDIRECT3DBASETEXTURE9 GetD3DTexture();
	virtual void SetD3DTexture(LPDIRECT3DBASETEXTURE9 pkD3DTexture);
	virtual NiDX9RenderedTextureData* GetAsRenderedTexture();
	virtual NiDX9SourceTextureData* GetAsSourceTexture();
	virtual NiDX9DynamicTextureData* GetAsDynamicTexture();
	virtual bool InitializeFromD3DTexture(LPDIRECT3DBASETEXTURE9 pkD3DTexture);

	NiDX9Renderer* m_pkRenderer;		// 60
	LPDIRECT3DBASETEXTURE9 m_pkD3DTexture;		// 64
	UInt32 m_uiLevels;

	bool SaveTexture(const char* path, D3DXIMAGE_FILEFORMAT aeFormat) {
		return D3DXSaveTextureToFile(path, aeFormat, m_pkD3DTexture, NULL);
	}
};

ASSERT_SIZE(NiDX9TextureData, 0x6C);