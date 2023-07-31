#pragma once

#include "NiPoint3.hpp"

class NiPlane {
public:
	NiPlane() : m_kNormal(0.0f, 0.0f, 0.0f), m_fConstant(0.0f) {}
	NiPlane(const NiPoint3& kNormal, float fConstant) : m_kNormal(kNormal), m_fConstant(fConstant) {}
	NiPlane(const NiPoint3& kNormal, const NiPoint3& kPoint) : m_kNormal(kNormal), m_fConstant(kNormal.Dot(kPoint)) {}
	~NiPlane() {}

	NiPoint3 m_kNormal;
	float m_fConstant;

	enum Sides {
		NO_SIDE = 0x0,
		POSITIVE_SIDE = 0x1,
		NEGATIVE_SIDE = 0x2,
	};

	UInt32 WhichSide(NiPoint3* kPoint);
	static UInt32 __fastcall WhichSide_Hook(NiPlane* pThis, void*, NiPoint3* kPoint);
};

ASSERT_SIZE(NiPlane, 0x10);