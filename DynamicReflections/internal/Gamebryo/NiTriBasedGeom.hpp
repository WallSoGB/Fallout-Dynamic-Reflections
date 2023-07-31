#pragma once

#include "NiGeometry.hpp"

class NiTriBasedGeomData;

class NiTriBasedGeom : public NiGeometry {
public:
	NiTriBasedGeomData* GetModelData();
};

ASSERT_SIZE(NiTriBasedGeom, 0xC4);