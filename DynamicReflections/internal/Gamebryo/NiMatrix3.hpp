#pragma once

#include "NiPoint3.hpp"

class NiMatrix3 {
public:
	float	m_pEntry[3][3];

	NiMatrix3() {}
	NiMatrix3(float m00, float m10, float m20, float m01, float m11, float m21, float m02, float m12, float m22)
	{
		m_pEntry[0][0] = m00;
		m_pEntry[0][1] = m10;
		m_pEntry[0][2] = m20;
		m_pEntry[1][0] = m01;
		m_pEntry[1][1] = m11;
		m_pEntry[1][2] = m21;
		m_pEntry[2][0] = m02;
		m_pEntry[2][1] = m12;
		m_pEntry[2][2] = m22;
	}

	bool operator==(const NiMatrix3& mat) const;
	NiMatrix3 operator+(const NiMatrix3& mat) const;
	NiMatrix3 operator-(const NiMatrix3& mat) const;
	NiMatrix3 operator*(const NiMatrix3& mat) const;
	NiMatrix3 operator*(float fScalar) const;
	NiPoint3 operator*(const NiPoint3& pt) const;
	friend NiPoint3 operator*(const NiPoint3& pt, const NiMatrix3& mat);

	NiMatrix3 operator/(float fScalar) const;

	void MakeXRotation(float fAngle);

	void MakeYRotation(float fAngle);

	void MakeZRotation(float fAngle);

	void MakeRotation(float fAngle, float x, float y, float z);

	void FromEulerAnglesXYZ(float fXAngle, float fYAngle, float fZAngle);

	__forceinline void SetCol(UInt32 uiCol, const NiPoint3& col) {
		m_pEntry[0][uiCol] = col.x;
		m_pEntry[1][uiCol] = col.y;
		m_pEntry[2][uiCol] = col.z;
	}
	__forceinline void GetCol(UInt32 uiCol, float& f0, float& f1, float& f2) const{
		f0 = m_pEntry[0][uiCol];
		f1 = m_pEntry[1][uiCol];
		f2 = m_pEntry[2][uiCol];
	}

	__forceinline void GetCol(UInt32 uiCol, NiPoint3& col) const {
		col.x = m_pEntry[0][uiCol];
		col.y = m_pEntry[1][uiCol];
		col.z = m_pEntry[2][uiCol];
	}

	NiPoint3* GetCol(UInt32 uiCol) const {
		static NiPoint3 col;
		col.x = m_pEntry[0][uiCol];
		col.y = m_pEntry[1][uiCol];
		col.z = m_pEntry[2][uiCol];
		return &col;
	}

	NiMatrix3(const NiPoint3& col0, const NiPoint3& col1, const NiPoint3& col2) {
		SetCol(0, col0);
		SetCol(1, col1);
		SetCol(2, col2);
	}

	__forceinline void GetRow(UInt32 uiRow, NiPoint3& row) const {
		row.x = m_pEntry[uiRow][0];
		row.y = m_pEntry[uiRow][1];
		row.z = m_pEntry[uiRow][2];
	}

	__forceinline void SetRow(UInt32 uiRow, float f0, float f1, float f2) {
		m_pEntry[uiRow][0] = f0;
		m_pEntry[uiRow][1] = f1;
		m_pEntry[uiRow][2] = f2;
	}

	NiMatrix3 Transpose()
	{
		NiPoint3 row[3];

		GetRow(0, row[0]);
		GetRow(1, row[1]);
		GetRow(2, row[2]);

		return NiMatrix3(row[0], row[1], row[2]);
	}

	NiMatrix3 TransposeTimes(const NiMatrix3& mat) const;
	bool Inverse(NiMatrix3& inv) const;
};

ASSERT_SIZE(NiMatrix3, 0x24);

typedef NiMatrix3 NiMatrix33;