#pragma once

#include <d3d9.h>
#include "NiDynamicEffectState.hpp"
#include "NiDX9RenderState.hpp"
#include "NiVertexColorProperty.hpp"
#include "NiLight.hpp"
#include "NiTStringMap.hpp"

class NiDX9LightManager {
public:
	class LightEntry
	{
	public:
		D3DLIGHT9 m_kD3DLight;
		UInt32 m_uiRevID;
		int m_iIndex;
		bool m_bNeedsRemoval;
		bool m_bActive;
	};

	NiTPointerMap<NiLight*, LightEntry*> m_kLights;
	NiTPointerList<NiLight*> m_kDeviceLights;
	LPDIRECT3DDEVICE9 m_pkD3DDevice9;
	NiDX9RenderState* m_pkRenderState;
	const NiDynamicEffectState* const m_pkInvalidState;
	const NiDynamicEffectState* m_pkLastState;
	bool m_bLastAmbientDiffuse;
	bool m_bAmbientDiffuse;
	NiTexturingProperty::ApplyMode m_eApply;
	NiVertexColorProperty::SourceVertexMode m_eSourceMode;
	UInt32 m_uiNextAvailableIndex;
	UInt32 m_auiValidIndices[128];
};

ASSERT_SIZE(NiDX9LightManager, 0x23C);