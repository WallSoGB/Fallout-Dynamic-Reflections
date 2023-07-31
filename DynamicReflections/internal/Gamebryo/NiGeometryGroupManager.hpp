#pragma once

class NiGeometryGroup;
class NiScreenTexture;
class NiSkinInstance;
class NiGeometryData;

class NiGeometryGroupManager {
	enum RepackingBehavior
	{
		STATIC = 0x0,
		UNSHARED = 0x1,
		DYNAMIC = 0x2,
	};

	void Destroy(bool);
	NiGeometryGroup* CreateGroup(NiGeometryGroupManager::RepackingBehavior eBehavior);
	bool DestroyGroup(NiGeometryGroup* pkGroup);
	bool IsGroupEmpty(NiGeometryGroup* pkGroup);
	bool AddObjectToGroup(NiGeometryGroup* pkGroup, NiScreenTexture* pkScreenTexture);
	bool AddObjectToGroup0(NiGeometryGroup* pkGroup, NiGeometryData* pkData, NiSkinInstance* pkSkinInstance);
	bool RemoveObjectFromGroup(NiScreenTexture* pkScreenTexture);
	bool RemoveObjectFromGroup0(NiGeometryData* pkData, NiSkinInstance* pkSkinInstance);
};