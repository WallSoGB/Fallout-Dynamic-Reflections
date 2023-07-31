#pragma once

#include "NiProperty.hpp"

NiSmartPointer(NiPropertyState);

class NiAlphaProperty;
class NiCullingProperty;
class NiMaterialProperty;
class NiShadeProperty;
class NiStencilProperty;
class NiTexturingProperty;

class NiPropertyState {
public:
	NiPropertyState();
	~NiPropertyState();

	enum PropertyID {
		ALPHA = 0,
		CULLING = 1,
		MATERIAL = 2,
		SHADE = 3,
		STENCIL = 4,
		TEXTURING = 5,
		UNK = 6, // Never seen this one used - maybe I could add custom properties here?
		MAX = 7,
	};

	struct Properties {
		NiPointer<NiAlphaProperty> m_spAlphaProperty;
		NiPointer<NiCullingProperty> m_spCullingProperty;
		NiPointer<NiMaterialProperty> m_spMaterialProperty;
		NiPointer<NiShadeProperty> m_spShadeProperty;
		NiPointer<NiStencilProperty> m_spStencilProperty;
		NiPointer<NiTexturingProperty> m_spTextureProperty;
		UInt32 unk;
	};

	union {
		Properties m_aspProperties;
		NiPropertyPtr m_aspProps[MAX];
	};

	__forceinline NiAlphaProperty* GetAlphaProperty() const { return m_aspProperties.m_spAlphaProperty.m_pObject; };

	__forceinline NiCullingProperty* GetCullingProperty() const { return m_aspProperties.m_spCullingProperty.m_pObject; };

	__forceinline NiMaterialProperty* GetMaterialProperty() const { return m_aspProperties.m_spMaterialProperty.m_pObject; };

	__forceinline NiShadeProperty* GetShadeProperty() const { return m_aspProperties.m_spShadeProperty.m_pObject; };

	__forceinline NiStencilProperty* GetStencilProperty() const { return m_aspProperties.m_spStencilProperty.m_pObject; };

	__forceinline NiTexturingProperty* GetTexturingProperty() const { return m_aspProperties.m_spTextureProperty.m_pObject; };
};

ASSERT_SIZE(NiPropertyState, 0x1C);