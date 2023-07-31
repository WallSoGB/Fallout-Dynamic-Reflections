#pragma once

#include "TESBoundObject.hpp"
#include "TESModelTextureSwap.hpp"

class TESSound;

class BGSAddonNode : public TESBoundObject {
public:
	BGSAddonNode();
	~BGSAddonNode();

	struct ADDON_DATA
	{
		UInt16 usMasterParticleCap;
		char cFlags;
	};

	TESModelTextureSwap textureSwap;
	UInt32 iIndex;
	TESSound* pSound;
	ADDON_DATA Data;
	UInt32 MasterParticleLock;
};

ASSERT_SIZE(BGSAddonNode, 0x60);