#pragma once

#include "NiKeyBasedInterpolator.hpp"
#include "NiColor.hpp"
#include "NiColorData.hpp"

NiSmartPointer(NiColorInterpolator);

class NiColorInterpolator : public NiKeyBasedInterpolator {
public:
	NiColorInterpolator();
	~NiColorInterpolator();

	NiColorA m_kColorValue;
	NiColorData* m_spColorData;
	UInt32 m_uiLastIdx;
};

ASSERT_SIZE(NiColorInterpolator, 0x24)