#pragma once

#include "NiTriBasedGeom.hpp"

NiSmartPointer(NiTriStrips);

class NiTriStrips : public NiTriBasedGeom {
public:
	NiTriStrips();
	~NiTriStrips();

	CREATE_OBJECT(NiTriStrips, 0xA71CE0);

	static void __fastcall RenderImmediateEx(NiTriStrips* apThis, void*, NiDX9Renderer* apRenderer);
	static void __fastcall RenderImmediateAltEx(NiTriStrips* apThis, void*, NiDX9Renderer* apRenderer);
};

ASSERT_SIZE(NiTriStrips, 0xC4)