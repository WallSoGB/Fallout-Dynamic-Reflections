#pragma once

#include "NiPoint3.hpp"

class NiSphere {
	NiPoint3 m_kCenter;
	float m_fRadius;
};

ASSERT_SIZE(NiSphere, 0x10);