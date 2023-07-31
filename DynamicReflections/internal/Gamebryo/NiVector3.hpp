#pragma once

class NiVector3 {
public:
	float x, y, z;

	NiVector3() : x(0), y(0), z(0) {}
	NiVector3(float x, float y, float z) : x(x), y(y), z(z) {}

	NiVector3 operator+(const NiVector3& rhs) const {
		return NiVector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	NiVector3 operator-(const NiVector3& rhs) const {
		return NiVector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	NiVector3 operator*(const float& rhs) const {
		return NiVector3(x * rhs, y * rhs, z * rhs);
	}

	NiVector3 operator/(const float& rhs) const {
		return NiVector3(x / rhs, y / rhs, z / rhs);
	}

	NiVector3& operator+=(const NiVector3& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	NiVector3& operator-=(const NiVector3& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	NiVector3& operator*=(const float& rhs) {
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	NiVector3& operator/=(const float& rhs) {
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	bool operator==(const NiVector3& rhs) const {
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	bool operator!=(const NiVector3& rhs) const {
		return x != rhs.x || y != rhs.y || z != rhs.z;
	}

	NiVector3& operator=(const NiVector3& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
};