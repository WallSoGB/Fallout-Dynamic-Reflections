#pragma once

#include "NiDX9TextureData.hpp"

class NiDX9DynamicTextureData : public NiDX9TextureData {
public:
	LPDIRECT3DBASETEXTURE9 m_pkD3DLockableSysMemTexture;
	bool m_bTextureLocked;
};

ASSERT_SIZE(NiDX9DynamicTextureData, 0x74);