#pragma once

#include "NiTriBasedGeom.hpp"

NiSmartPointer(NiTriShape);

class NiTriShape : public NiTriBasedGeom {
public:
	NiTriShape();
	~NiTriShape();

	CREATE_OBJECT(NiTriShape, 0xA744D0);

	static void __fastcall RenderImmediateEx(NiTriShape* apThis, void*, NiDX9Renderer* apRenderer);
	static void __fastcall RenderImmediateAltEx(NiTriShape* apThis, void*, NiDX9Renderer* apRenderer);
};

ASSERT_SIZE(NiTriShape, 0xC4);