#pragma once

#include "TESChildCell.hpp"
#include "TESForm.hpp"
#include "BSSimpleArray.hpp"
#include "NiPoint3.hpp"
#include "NiColor.hpp"
#include "NiLines.hpp"
#include "NiTPointerMap.hpp"

class TESObjectCELL;
class NiNode;
class NiObject;
class TESLandTexture;
class TESGrassAreaParam;

class TESObjectLAND : public TESForm, TESChildCell {
public:
	struct LoadedLandData
	{
		struct Geometry
		{
			NiPoint3 quad0Vertices[289];
		};

		struct Struct08
		{
			NiPoint3 quad0Unk[289];
		};

		struct Colors
		{
			NiColorA vertColor[289];
		};

		struct Textures
		{
			TESLandTexture* pLandTexture[5];
		};

		NiNode** ppMesh;
		Geometry** geometry;
		Struct08** spGeom;
		Colors** pColors;
		void** ptr10;
		NiLinesPtr spBorder;
		float minHeight;
		float maxHeight;
		TESLandTexture* pDefQuadTexture[4];
		Textures* pQuadTextureArray[4];
		void** pPercentArrays[4];
		UInt32 unk50;
		NiTPointerMap<UInt32, TESGrassAreaParam**> grassParams54[4];
		NiObject* object94;
		SInt32 iCellX;
		SInt32 iCellY;
		float fBaseHeight;
	};

	UInt32 iFlags;
	TESObjectCELL* pParentCell;
	void* spQueuedTextures;
	TESObjectLAND::LoadedLandData* pLoadedData;
};

ASSERT_SIZE(TESObjectLAND, 0x2C);
ASSERT_SIZE(TESObjectLAND::LoadedLandData, 0xA4);