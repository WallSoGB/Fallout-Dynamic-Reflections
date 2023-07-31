#pragma once

#include "NiRect.hpp"

class NiPoint4 {
public:
	float x, y, z, r;

	NiPoint4() : x(0.f), y(0.f), z(0.f), r(0.f)
	{
	};

	NiPoint4(const float x, const float y, const float z, const float r) : x(x), y(y), z(z), r(r)
	{
	};

	NiPoint4(const NiPoint3& src) : x(src.x), y(src.y), z(src.z), r(0.f)
	{
	};

	operator NiRect<float>() const
	{
		return NiRect<float>(x, y, z, r);
	};
};