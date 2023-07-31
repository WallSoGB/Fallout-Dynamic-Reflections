#pragma once

#include "NiPoint2.hpp"
#include "NiPoint3.hpp"
#include "NiPoint4.hpp"

#include "NiVector3.hpp"

class NiVector4 {
public:
	float x, y, z, w;
	NiVector4() : x(0), y(0), z(0), w(0) {}
	NiVector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	NiVector4(float f) : x(f), y(f), z(f), w(f) {}

	NiVector4 operator=(const NiVector4& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

	NiVector4 operator=(const float& rhs) {
		x = rhs;
		y = rhs;
		z = rhs;
		w = rhs;
		return *this;
	}

	NiVector4 operator=(const NiPoint3& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = 0.0f;
		return *this;
	}

	NiVector4 operator=(const NiVector3& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = 0.0f;
		return *this;
	}

	NiVector4 operator=(const NiPoint4& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.r;
		return *this;
	}

	NiVector4 operator+(const NiVector4& rhs) const {
		return NiVector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	NiVector4 operator-(const NiVector4& rhs) const {
		return NiVector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	NiVector4 operator*(const float& rhs) const {
		return NiVector4(x * rhs, y * rhs, z * rhs, w * rhs);
	}

	NiVector4 operator/(const float& rhs) const {
		return NiVector4(x / rhs, y / rhs, z / rhs, w / rhs);
	}

	NiVector4& operator+=(const NiVector4& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	NiVector4& operator-=(const NiVector4& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	NiVector4& operator*=(const float& rhs) {
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	NiVector4& operator/=(const float& rhs) {
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;
		return *this;
	}

	bool operator==(const NiVector4& rhs) const {
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}

	bool operator!=(const NiVector4& rhs) const {
		return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
	}

	float Length() const {
		return sqrt(x * x + y * y + z * z + w * w);
	}

	float LengthSquared() const {
		return x * x + y * y + z * z + w * w;
	}

	NiVector4 Normalize() const {
		float len = Length();
		if (len == 0.0f)
			return NiVector4(0, 0, 0, 0);
		return NiVector4(x / len, y / len, z / len, w / len);
	}

	float Dot(const NiVector4& rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	}

	NiVector4 Cross(const NiVector4& rhs) const {
		return NiVector4(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x, 0);
	}

	NiVector4 Lerp(const NiVector4& rhs, float t) const {
		return NiVector4(x + (rhs.x - x) * t, y + (rhs.y - y) * t, z + (rhs.z - z) * t, w + (rhs.w - w) * t);
	}

	NiVector4 Slerp(const NiVector4& rhs, float t) const {
		float dot = Dot(rhs);
		if (dot < 0.0f) {
			return NiVector4(-x, -y, -z, -w).Slerp(rhs, t);
		}
		if (dot > 0.9995f) {
			return Lerp(rhs, t);
		}
		float theta = acos(dot);
		float sinTheta = sin(theta);
		float a = sin((1.0f - t) * theta) / sinTheta;
		float b = sin(t * theta) / sinTheta;
		return NiVector4(x * a + rhs.x * b, y * a + rhs.y * b, z * a + rhs.z * b, w * a + rhs.w * b);
	}
};