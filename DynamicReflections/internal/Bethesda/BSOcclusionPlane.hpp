#pragma once

#include "NiObject.hpp"
#include "NiPoint2.hpp"
#include "NiPoint3.hpp"
#include "NiMatrix3.hpp"
#include "NiFrustumPlanes.hpp"
#include "BSMultiBoundShape.hpp"

class BSOcclusionPlane : public NiObject {
public:
	NiPoint3 kCenter;
	NiPoint2 kHalfExtents;
	NiMatrix3 kRotation;
	BSMultiBoundShape::BSMBCullResult kCullResult;
	NiFrustumPlanes kCachedPlanes;
	NiPoint3 kCachedVertices[4];
	NiPoint3 kViewPoint;
	bool bDirtyVertices;
	bool UnkE5;
	bool bDisabledPlanes[4];
	bool bTwoSided;
	bool UnkEB;
	BSOcclusionPlane* pLinkedPlanes[4];

	void UpdateFrustumPlanes(NiPoint3 akViewPoint, NiFrustumPlanes* apPlanes);
};