#pragma once

#include "NiObject.hpp"
#include "NiPalette.hpp"

NiSmartPointer(NiPixelData);

class NiPixelData : public NiObject {
public:
	NiPixelData();
	~NiPixelData();

	NiPixelFormat m_kPixelFormat;
	NiPalette* m_spPalette;
	UInt8* m_pucPixels;
	UInt32* m_puiWidth;
	UInt32* m_puiHeight;
	UInt32* m_puiOffsetInBytes;
	UInt32 m_uiMipmapLevels;
	UInt32 m_uiPixelStride;
	UInt32 m_uiRevID;
	UInt32 m_uiFaces;
	bool unk70;

	CREATE_OBJECT(NiPixelData, 0xA7C3F0)
};

ASSERT_SIZE(NiPixelData, 0x74)