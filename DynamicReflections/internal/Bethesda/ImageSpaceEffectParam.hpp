#pragma once

#include "NiTArray.hpp"
#include "NiTexturingProperty.hpp"

class ImageSpaceEffectParam {
public:
	ImageSpaceEffectParam() {ThisStdCall(0x4EBA20, this); }
	virtual void Destroy(bool bFreeMemory);

	NiTPrimitiveArray<UInt32> eTextureType;
	NiTPrimitiveArray<NiTexturingProperty::FilterMode> FilterMode;

	static ImageSpaceEffectParam* Create(ImageSpaceEffectParam* apISParam) {
		ThisStdCall(0x4EBA20, apISParam);
		return apISParam;
	};

	void Free() { ThisStdCall(0x4EBA90, this); }
};

ASSERT_SIZE(ImageSpaceEffectParam, 0x24);