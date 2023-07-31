#pragma once

#include "NiPoint3.hpp"

class NiPoint2 {
public:
	float x, y;

	NiPoint2() : x(0.0f), y(0.0f) {};
	NiPoint2(float x, float y) : x(x), y(y) {};
	NiPoint2(float xy) : x(xy), y(xy) {};
	NiPoint2(const NiPoint3& point) : x(point.x), y(point.y) {};
	NiPoint2(const NiPoint3* point) : x(point->x), y(point->y) {};

	NiPoint2 operator+(const NiPoint2& other) const {
		return NiPoint2(x + other.x, y + other.y);
	}

	NiPoint2 operator+(float other) const {
		return NiPoint2(x + other, y + other);
	}

	NiPoint2 operator-(const NiPoint2& other) const {
		return NiPoint2(x - other.x, y - other.y);
	}

	NiPoint2 operator-(float other) const {
		return NiPoint2(x - other, y - other);
	}

	NiPoint2 operator*(float other) const {
		return NiPoint2(x * other, y * other);
	}

	NiPoint2 operator/(float other) const {
		return NiPoint2(x / other, y / other);
	}

	NiPoint2 operator-() const {
		return NiPoint2(-x, -y);
	}

	NiPoint2& operator+=(const NiPoint2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	NiPoint2& operator-=(const NiPoint2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	NiPoint2& operator*=(float other) {
		x *= other;
		y *= other;
		return *this;
	}

	NiPoint2& operator/=(float other) {
		x /= other;
		y /= other;
		return *this;
	}
};