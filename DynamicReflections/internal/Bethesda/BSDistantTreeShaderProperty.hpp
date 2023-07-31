#pragma once

#include "BSShaderProperty.hpp"

NiSmartPointer(BSDistantTreeShaderProperty);

class BSDistantTreeShaderProperty : public BSShaderProperty {
public:
	BSDistantTreeShaderProperty();
	~BSDistantTreeShaderProperty();

	UInt32 dword60;
	DWORD dword68;

	CREATE_OBJECT(BSDistantTreeShaderProperty, 0xBB7300);
};

ASSERT_SIZE(BSDistantTreeShaderProperty, 0x68);