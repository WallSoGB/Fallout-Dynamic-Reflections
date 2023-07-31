#pragma once

#include "TESModel.hpp"
#include "BSSimpleList.hpp"

class TESModelTextureSwap : public TESModel {
public:
	TESModelTextureSwap();
	~TESModelTextureSwap();

	struct Texture
	{
		UInt32	textureID;			// 00
		UInt32	index3D;			// 04
		char	textureName[0x80];	// 08
	};	// there seem to be an array (length 6) post 0x88

	virtual void* Destroy(bool noDealloc);
	virtual char* GetPath(void);
	virtual void	SetPath(char* path);
	virtual void* Unk_07(void);

	BSSimpleList<Texture*> textureList;	// 018
};

ASSERT_SIZE(TESModelTextureSwap, 0x20);