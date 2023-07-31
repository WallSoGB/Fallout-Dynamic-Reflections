#pragma once

#include "NiNode.hpp"

class BSCullingProcess;
class NiCamera;
class NiVisibleArray;

class BSSceneGraph : public NiNode {
public:
	virtual double CalculateNoLODFarDist();
	virtual void   SetViewDistanceBasedOnFrameRate(float afTime);

	NiPointer<NiCamera> spCamera;
	NiVisibleArray* pVisArray;
	BSCullingProcess* pCuller;
	bool bMenuSceneGraph;
	float fCurrentFOV;
};

ASSERT_SIZE(BSSceneGraph, 0xC0);