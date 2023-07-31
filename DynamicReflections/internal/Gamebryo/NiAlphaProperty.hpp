#pragma once

#include "NiProperty.hpp"

NiSmartPointer(NiAlphaProperty);

class NiAlphaProperty : public NiProperty {
public:
	NiAlphaProperty();
	~NiAlphaProperty();

	enum AlphaFlags {
		ALPHA_BLEND_MASK = 0x0001,
		SRC_BLEND_MASK = 0x001e,
		SRC_BLEND_POS = 1,
		DEST_BLEND_MASK = 0x01e0,
		DEST_BLEND_POS = 5,
		TEST_ENABLE_MASK = 0x0200,
		TEST_FUNC_MASK = 0x1c00,
		TEST_FUNC_POS = 10,
		ALPHA_NOSORTER_MASK = 0x2000
	};

	enum AlphaFunction
	{
		ALPHA_ONE = 0x0,
		ALPHA_ZERO = 0x1,
		ALPHA_SRCCOLOR = 0x2,
		ALPHA_INVSRCCOLOR = 0x3,
		ALPHA_DESTCOLOR = 0x4,
		ALPHA_INVDESTCOLOR = 0x5,
		ALPHA_SRCALPHA = 0x6,
		ALPHA_INVSRCALPHA = 0x7,
		ALPHA_DESTALPHA = 0x8,
		ALPHA_INVDESTALPHA = 0x9,
		ALPHA_SRCALPHASAT = 0xA,
		ALPHA_MAX_MODES = 0xB,
	};


	UInt16 m_usFlags;
	UInt8 m_ucAlphaTestRef;

	CREATE_OBJECT(NiAlphaProperty, 0xA5CEB0);
};

ASSERT_SIZE(NiAlphaProperty, 0x01C);