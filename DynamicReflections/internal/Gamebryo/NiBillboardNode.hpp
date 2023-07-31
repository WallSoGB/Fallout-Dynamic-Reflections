#pragma once

#include "NiNode.hpp"

NiSmartPointer(NiBillboardNode);

class NiBillboardNode : public NiNode {
public:
	NiBillboardNode();
	~NiBillboardNode();

	UInt16 m_usFlags;
	float m_fSavedTime;

	CREATE_OBJECT(NiBillboardNode, 0xA7E770);

	void RotateToCamera(NiCamera* apCamera);
	static void __fastcall OnVisibleEx(NiBillboardNode* apThis, void*, NiCullingProcess* apCuller);
};

ASSERT_SIZE(NiBillboardNode, 0xB4);