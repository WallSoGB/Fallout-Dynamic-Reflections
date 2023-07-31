#pragma once

#include "NiLight.hpp"
#include "NiVector3.hpp"

NiSmartPointer(NiDirectionalLight)
NiRTTIAddress(NiDirectionalLight, 0x11F4A68)

class NiDirectionalLight : public NiLight {
public:
	NiDirectionalLight();
	~NiDirectionalLight();

	NiVector3 m_kWorldDir;

	CREATE_OBJECT(NiDirectionalLight, 0xA75D50)
};

ASSERT_SIZE(NiDirectionalLight, 0xFC);