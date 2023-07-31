#pragma once

#include "NiNode.hpp"

class BSTempNode : public NiNode {
public:
	float fTime;

	static BSTempNode* Create(float afTime);
};

ASSERT_SIZE(BSTempNode, 0xB0);