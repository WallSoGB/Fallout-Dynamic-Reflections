#pragma once

#include "NiPoint3.hpp"
#include "NiPlane.hpp"

class NiCamera;

class NiBound {
public:
	NiBound() : m_kCenter(NiPoint3(0.0f,0.0f,0.0f)) , m_fRadius(0.0f) {};
	~NiBound() {};

	NiPoint3 m_kCenter;
	float m_fRadius;

	static float ms_fFuzzFactor;
	static float ms_fTolerance;
	static NiBound ms_kDefaultBound;

	int WhichSide(const NiPlane& Plane);
	void Merge(const NiBound* pBound);
	static void __fastcall MergeEx(NiBound* apThis, void*, const NiBound* apBound);
	static NiBound* GetGlobalWorldBound();
	bool IsInFrustum(NiCamera* apCamera);
};

ASSERT_SIZE(NiBound, 0x010);