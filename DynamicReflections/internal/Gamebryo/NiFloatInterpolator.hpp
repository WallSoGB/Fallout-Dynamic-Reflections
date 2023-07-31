#pragma once

#include "NiKeyBasedInterpolator.hpp"
#include "NiFloatData.hpp"

class NiFloatInterpolator : public NiKeyBasedInterpolator {
public:
	float m_fFloatValue;
	NiFloatData* m_spFloatData;
	UInt32 m_uiLastIdx;
};