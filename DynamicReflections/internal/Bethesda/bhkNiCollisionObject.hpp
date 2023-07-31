#pragma once

#include "NiCollisionObject.hpp"

NiSmartPointer(bhkNiCollisionObject);

class bhkNiCollisionObject : public NiCollisionObject {
public:
	UInt32 m_uiflags;
	void* worldObj;
};