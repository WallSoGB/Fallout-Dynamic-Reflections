#pragma once

#include "NiMemObject.hpp"

class NiRTTI : public NiMemObject {
public:
	NiRTTI() { m_pcName = NULL; m_pkBaseRTTI = NULL; }
	NiRTTI(const char* name, const NiRTTI* base) { m_pcName = name; m_pkBaseRTTI = base; }

	const char* m_pcName;
	const NiRTTI* m_pkBaseRTTI;
};

ASSERT_SIZE(NiRTTI, 0x8);

#define NiImplementRootRTTI(rootclassname) \
    NiRTTI rootclassname::ms_RTTI(#rootclassname, 0);

#define NiImplementRTTI(classname, baseclassname) \
    NiRTTI classname##__ms_RTTI = NiRTTI(#classname, &baseclassname);

#define NiImplementGetRTTI(classname) \
	NiRTTI* __fastcall classname##__GetRTTI() {return &classname##__ms_RTTI;}

#define NiRTTIAddress(classname, address) \
	static const NiRTTI * classname##__ms_RTTI = (NiRTTI*)address;