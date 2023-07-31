#pragma once

#include "NiTexturingProperty.hpp"
#include "NiD3DTextureStageGroup.hpp"
#include "NiDX9RenderState.hpp"

class NiGlobalConstantEntry;

class NiD3DTextureStage {
public:
	NiTexturingProperty::FilterMode m_eFilter;
	UInt32 m_uiStage;
	NiTexture* m_pkTexture;
	UInt32 m_uiTextureFlags;
	NiD3DTextureStageGroup* m_pkTextureStageGroup;
	UInt32 m_uiTextureTransformFlags;
	NiGlobalConstantEntry* m_pkGlobalEntry;
	D3DMATRIX m_kTextureTransformation;
	UInt16 m_usObjTextureFlags;
	bool m_bTextureTransform;
	bool m_bRendererOwned;
	UInt32 m_uiRefCount;
	bool bUnk64;
	bool bUnk65;
	bool bUnk66;
};

ASSERT_SIZE(NiD3DTextureStage, 0x68);