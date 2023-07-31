#pragma once

#include "NiTriShape.hpp"
#include "SkyObject.hpp"
#include "NiBillboardNode.hpp"
#include "BSShaderAccumulator.hpp"
#include "NiDirectionalLight.hpp"

class Sun : public SkyObject {
public:
	NiBillboardNodePtr spSunBaseNode;
	NiBillboardNodePtr spSunGlareNode;
	NiTriShapePtr spSunBase;
	NiTriShapePtr spSunQuery;
	NiTriShapePtr spSunGlare;
	NiDirectionalLightPtr spLight;
	float fGlareScale;
	bool bDoOcclusionTests;
	BSShaderAccumulatorPtr spSunAccumulator;
};

ASSERT_SIZE(Sun, 0x2C);