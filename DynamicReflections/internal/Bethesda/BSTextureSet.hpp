#pragma once

#include "NiObject.hpp"

class NiSourceTexture;

class BSTextureSet : public NiObject {
public:
	BSTextureSet();
	~BSTextureSet();

	enum TextureSlots
	{
		BSSM_Diffuse = 0x0,
		BSSM_Normal = 0x1,
		BSSM_Glow = 0x2,
		BSSM_Parallax = 0x3,
		BSSM_CubeMap = 0x4,
		BSSM_EnvMask = 0x5,
	};

	virtual char* GetTexturePath(TextureSlots eTextureIndex);
	virtual void GetTexture(TextureSlots eTextureIndex, NiSourceTexture** ppTexture);
	virtual void SetTexturePath(TextureSlots eTextureIndex, char* path);
};