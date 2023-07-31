#pragma once

#include "NiNode.hpp"

class BSTempNodeManager : public NiNode {
public:
	float fPrevTime;
};

ASSERT_SIZE(BSTempNodeManager, 0xB0);