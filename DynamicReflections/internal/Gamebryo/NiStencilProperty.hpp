#pragma once

#include "NiProperty.hpp"

NiSmartPointer(NiStencilProperty);

class NiStencilProperty : public NiProperty {
public:
	NiStencilProperty();
	~NiStencilProperty();

	enum {
		ENABLE_MASK = 0x1,
		FAILACTION_MASK = 0xE,
		FAILACTION_POS = 0x1,
		ZFAILACTION_MASK = 0x70,
		ZFAILACTION_POS = 0x4,
		PASSACTION_MASK = 0x380,
		PASSACTION_POS = 0x7,
		DRAWMODE_MASK = 0xC00,
		DRAWMODE_POS = 0xA,
		TESTFUNC_MASK = 0xF000,
		TESTFUNC_POS = 0xC,
	};


	UInt16 m_usFlags;
	UInt32 m_uiRef;
	UInt32 m_uiMask;

	CREATE_OBJECT(NiStencilProperty, 0xA6F410)
};

ASSERT_SIZE(NiStencilProperty, 0x24);