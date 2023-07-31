#pragma once

#include "NiDynamicEffect.hpp"
#include "NiColor.hpp"

NiSmartPointer(NiLight);

class NiLight : public NiDynamicEffect {
public:
	NiLight();
	~NiLight();

	float m_fDimmer;
	NiColor m_kAmb;
	NiColor m_kDiff;
	NiColor m_kSpec;
	void* m_pvRendererData;
};

ASSERT_SIZE(NiLight, 0xF0)