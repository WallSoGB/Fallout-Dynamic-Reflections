#pragma once

#include "NiNode.hpp"

class Sky;

NiSmartPointer(SkyObject);

class SkyObject {
public:
	virtual SkyObject* Destroy(bool doFree);
	virtual NiNode* GetNiNode(void);
	virtual void		InitNiNode(NiNode* node);
	virtual void		Update(Sky* sky, float value);

	NiNodePtr spRoot;
};

ASSERT_SIZE(SkyObject, 0x8)