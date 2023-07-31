#pragma once

#include "NiObject.hpp"

NiSmartPointer(BSMultiBoundShape);

class BSMultiBoundShape : public NiObject {
public:
	enum BSMBCullResult
	{
		BS_CULL_UNTESTED = 0x0,
		BS_CULL_VISIBLE = 0x1,
		BS_CULL_CULLED = 0x2,
		BS_CULL_OCCLUDED = 0x3,
	};

	BSMultiBoundShape::BSMBCullResult kCullResult;
};

ASSERT_SIZE(BSMultiBoundShape, 0xC)