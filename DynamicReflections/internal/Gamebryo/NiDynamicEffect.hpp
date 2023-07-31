#pragma once

#include "NiAVObject.hpp"
#include "NiTPointerList.hpp"

class NiNode;

typedef NiTPointerList<NiNode*> NiNodeList;

class NiDynamicEffect : public NiAVObject {
public:
	bool m_bOn;
	UInt8 m_ucEffectType;
	bool bCastShadows;
	bool bCanCarry;
	SInt32 m_iIndex;
	UInt32 m_uiPushCount;
	UInt32 m_uiRevID;
	NiNodeList m_pkShadowGenerator;
	NiNodeList m_kUnaffectedNodeList;
};

ASSERT_SIZE(NiDynamicEffect, 0xC4)