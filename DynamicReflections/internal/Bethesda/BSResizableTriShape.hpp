#pragma once

#include "NiTriShape.hpp"

NiSmartPointer(BSResizableTriShape);

class BSResizableTriShape : public NiTriShape {
public:
	UInt32 activePrimitives;
	NiBound LocalBound;
};
