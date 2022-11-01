#include "Matrix4.h"

//A constant static variable to use to quickly set/get an identity matrix.
const Matrix4 Matrix4::IDENTITY = Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
	                                      0.0f, 1.0f, 0.0f, 0.0f,
	                                      0.0f, 0.0f, 1.0f, 0.0f,
	                                      0.0f, 0.0f, 0.0f, 1.0f);

//===================
//Default Constructor
//===================
Matrix4::Matrix4() : m_11(1.0f), m_21(0.0f), m_31(0.0f), m_41(0.0f),
                     m_12(0.0f), m_22(1.0f), m_32(0.0f), m_42(0.0f),
                     m_13(0.0f), m_23(0.0f), m_33(1.0f), m_43(0.0f),
	                 m_14(0.0f), m_24(0.0f), m_34(0.0f), m_44(0.0f)
{

}
//=======================================
//Constructor using pointer to float data
//=======================================
Matrix4::Matrix4(const float* a_mat) : m_11(a_mat[0]), m_21(a_mat[1]), m_31(a_mat[2]), m_41(a_mat[3]),
                                       m_12(a_mat[4]), m_22(a_mat[5]), m_32(a_mat[6]), m_42(a_mat[7]),
                                       m_13(a_mat[8]), m_23(a_mat[9]), m_33(a_mat[10]), m_43(a_mat[11]),
	                                   m_14(a_mat[12]), m_24(a_mat[13]), m_34(a_mat[14]), m_44(a_mat[15])
{

}
//==========================================================
//Constructor using all components of matrix data structure.
//==========================================================
Matrix4::Matrix4(float a_m11, float a_m21, float a_m31, float a_m41,
	             float a_m12, float a_m22, float a_m32, float a_m42,
	             float a_m13, float a_m23, float a_m33, float a_m43,
	             float a_m14, float a_m24, float a_m34, float a_m44) :
	m_11(a_m11), m_21(a_m21), m_31(a_m31), m_41(a_m41),
	m_12(a_m12), m_22(a_m22), m_32(a_m32), m_42(a_m42),
	m_13(a_m13), m_23(a_m23), m_33(a_m33), m_43(a_m43),
	m_14(a_m14), m_24(a_m24), m_34(a_m34), m_44(a_m44)
{

}
//==================================
//Construct from axis angle vectors.
//==================================
Matrix4::Matrix4(const Vector4& a_xAxis, const Vector4& a_yAxis, const Vector4& a_zAxis, const Vector4& a_wAxis) :
	m_xAxis(a_xAxis), m_yAxis(a_yAxis), m_zAxis(a_zAxis), m_wAxis(a_wAxis)
{

}
//=================
//Copy Constructor.
//=================
Matrix4::Matrix4(const Matrix4& a_m4) :
	m_11(a_m4.m_11), m_21(a_m4.m_21), m_31(a_m4.m_31), m_41(a_m4.m_41),
	m_12(a_m4.m_12), m_22(a_m4.m_22), m_32(a_m4.m_32), m_42(a_m4.m_42),
	m_13(a_m4.m_13), m_23(a_m4.m_23), m_33(a_m4.m_33), m_43(a_m4.m_43),
	m_14(a_m4.m_14), m_24(a_m4.m_24), m_34(a_m4.m_34), m_44(a_m4.m_44)
{

}
//=========================================
//Member variable access operator overload.
//=========================================
#include <cassert>
float& Matrix4::operator() (int a_iColumn, int a_iRow)
{
	//Make sure that column and row is within range.
	assert(a_iColumn >= 0 && a_iColumn < 4);
	assert(a_iRow >= 0 && a_iRow < 4);
	return m[a_iColumn - 1][a_iRow - 1];
}

float Matrix4::operator() (int a_iColumn, int a_iRow) const
{
	//Make sure that column and row is within range.
	assert(a_iColumn >= 0 && a_iColumn < 4);
	assert(a_iRow >= 0 && a_iRow < 4);
	return m[a_iColumn - 1][a_iRow - 1];
}
//======================
//Column and Row Access.
//======================
void Matrix4::SetColumn(int a_iCol, const Vector4& a_vCol)
{
	assert(a_iCol >= 0 && a_iCol < 4);
	m[a_iCol][0] = a_vCol.x;
	m[a_iCol][1] = a_vCol.y;
	m[a_iCol][2] = a_vCol.z;
	m[a_iCol][3] = a_vCol.w;
}

Vector4 Matrix4::GetColumn(int a_iCol) const
{
	assert(a_iCol >= 0 && a_iCol < 3);
	return Vector4(m[a_iCol][0], m[a_iCol][1], m[a_iCol][2], m[a_iCol][3]);
}
//======================
//Equivalence Operators.
//======================
bool Matrix4::operator == (const Matrix4& a_m4) const
{
	if (m_11 != a_m4.m_11)
	{
		return false;
	}
	if (m_12 != a_m4.m_12)
	{
		return false;
	}
	if (m_13 != a_m4.m_13)
	{
		return false;
	}
	if (m_14 != a_m4.m_14)
	{
		return false;
	}
	if (m_21 != a_m4.m_21)
	{
		return false;
	}
	if (m_22 != a_m4.m_22)
	{
		return false;
	}
	if (m_23 != a_m4.m_23)
	{
		return false;
	}
	if (m_24 != a_m4.m_24)
	{
		return false;
	}
	if (m_31 != a_m4.m_31)
	{
		return false;
	}
	if (m_32 != a_m4.m_32)
	{
		return false;
	}
	if (m_33 != a_m4.m_33)
	{
		return false;
	}
	if (m_34 != a_m4.m_34)
	{
		return false;
	}
	if (m_41 != a_m4.m_41)
	{
		return false;
	}
	if (m_42 != a_m4.m_42)
	{
		return false;
	}
	if (m_43 != a_m4.m_43)
	{
		return false;
	}
	if (m_44 != a_m4.m_44)
	{
		return false;
	}
	return true;
}

bool Matrix4::operator != (const Matrix4& a_m4) const
{
	if (m_11 != a_m4.m_11)
	{
		return true;
	}
	if (m_12 != a_m4.m_12)
	{
		return true;
	}
	if (m_13 != a_m4.m_13)
	{
		return true;
	}
	if (m_14 != a_m4.m_14)
	{
		return true;
	}
	if (m_21 != a_m4.m_21)
	{
		return true;
	}
	if (m_22 != a_m4.m_22)
	{
		return true;
	}
	if (m_23 != a_m4.m_23)
	{
		return true;
	}
	if (m_24 != a_m4.m_24)
	{
		return true;
	}
	if (m_31 != a_m4.m_31)
	{
		return true;
	}
	if (m_32 != a_m4.m_32)
	{
		return true;
	}
	if (m_33 != a_m4.m_33)
	{
		return true;
	}
	if (m_34 != a_m4.m_34)
	{
		return true;
	}
	if (m_41 != a_m4.m_41)
	{
		return true;
	}
	if (m_42 != a_m4.m_42)
	{
		return true;
	}
	if (m_43 != a_m4.m_43)
	{
		return true;
	}
	if (m_44 != a_m4.m_44)
	{
		return true;
	}
	return false;
}
//================================
//Operator Overloads For Addition.
//================================
Matrix4 Matrix4::operator+(const Matrix4& a_m4) const
{
	return Matrix4(m_11 + a_m4.m_11, m_21 + a_m4.m_21, m_31 + a_m4.m_31, m_41 + a_m4.m_41,
		           m_12 + a_m4.m_12, m_22 + a_m4.m_22, m_32 + a_m4.m_32, m_42 + a_m4.m_42,
		           m_13 + a_m4.m_13, m_23 + a_m4.m_23, m_33 + a_m4.m_33, m_43 + a_m4.m_43,
		           m_14 + a_m4.m_14, m_24 + a_m4.m_24, m_34 + a_m4.m_34, m_44 + a_m4.m_44);
}

const Matrix4& Matrix4::operator+=(const Matrix4& a_m4)
{
	    m_11 += a_m4.m_11, m_21 += a_m4.m_21, m_31 += a_m4.m_31, m_41 += a_m4.m_41,
		m_12 += a_m4.m_12, m_22 += a_m4.m_22, m_32 += a_m4.m_32, m_42 += a_m4.m_42,
		m_13 += a_m4.m_13, m_23 += a_m4.m_23, m_33 += a_m4.m_33, m_43 += a_m4.m_43,
		m_14 += a_m4.m_14, m_24 += a_m4.m_24, m_34 += a_m4.m_34, m_44 += a_m4.m_44;
	    return *this;
}
//===================================
//Operator Overloads For Subtraction.
//===================================
Matrix4 Matrix4::operator-(const Matrix4& a_m4) const
{
	return Matrix4(m_11 - a_m4.m_11, m_21 - a_m4.m_21, m_31 - a_m4.m_31, m_41 - a_m4.m_41,
		           m_12 - a_m4.m_12, m_22 - a_m4.m_22, m_32 - a_m4.m_32, m_42 - a_m4.m_42,
		           m_13 - a_m4.m_13, m_23 - a_m4.m_23, m_33 - a_m4.m_33, m_43 - a_m4.m_43,
		           m_14 - a_m4.m_14, m_24 - a_m4.m_24, m_34 - a_m4.m_34, m_44 - a_m4.m_44);
}

const Matrix4& Matrix4::operator-=(const Matrix4& a_m4)
{
	    m_11 -= a_m4.m_11, m_21 -= a_m4.m_21, m_31 -= a_m4.m_31, m_41 -= a_m4.m_41,
		m_12 -= a_m4.m_12, m_22 -= a_m4.m_22, m_32 -= a_m4.m_32, m_42 -= a_m4.m_42,
		m_13 -= a_m4.m_13, m_23 -= a_m4.m_23, m_33 -= a_m4.m_33, m_43 -= a_m4.m_43,
		m_14 -= a_m4.m_14, m_24 -= a_m4.m_24, m_34 -= a_m4.m_34, m_44 -= a_m4.m_44;
	return *this;
}
//======================================
//Operator Overloads For Multiplication.
//======================================
Matrix4 Matrix4::operator*(const float a_scalar) const
{
	return Matrix4(m_11 * a_scalar, m_21 * a_scalar, m_31 * a_scalar, m_41 * a_scalar,
		           m_12 * a_scalar, m_22 * a_scalar, m_32 * a_scalar, m_42 * a_scalar,
		           m_13 * a_scalar, m_23 * a_scalar, m_33 * a_scalar, m_43 * a_scalar,
		           m_14 * a_scalar, m_24 * a_scalar, m_34 * a_scalar, m_44 * a_scalar);
}

const Matrix4& Matrix4::operator*=(const float a_scalar)
{
	    m_11 *= a_scalar, m_21 *= a_scalar, m_31 *= a_scalar, m_41 *= a_scalar;
		m_12 *= a_scalar, m_22 *= a_scalar, m_32 *= a_scalar, m_42 *= a_scalar;
		m_13 *= a_scalar, m_23 *= a_scalar, m_33 *= a_scalar, m_43 *= a_scalar;
		m_14 *= a_scalar, m_24 *= a_scalar, m_34 *= a_scalar, m_44 *= a_scalar;
	return *this;
}
//==========================================================
//Operator Overloads For Multiplications By A Vector4 Value.
//==========================================================
Vector4 Matrix4::operator*(const Vector4& a_v4) const
{
	return Vector4(m_11 * a_v4.x + m_12 * a_v4.y + m_13 * a_v4.z + m_14 * a_v4.w,
		           m_21 * a_v4.x + m_22 * a_v4.y + m_23 * a_v4.z + m_24 * a_v4.w,
		           m_31 * a_v4.x + m_32 * a_v4.y + m_33 * a_v4.z + m_24 * a_v4.w,
		           m_41 * a_v4.x + m_42 * a_v4.y + m_43 * a_v4.z + m_44 * a_v4.w);
}
//=================================================
//Operator Overloads For Multiplication By Matrix4.
//=================================================
Matrix4 Matrix4::operator*(const Matrix4& a_m4) const
{
	return Matrix4(
		//First Column.
		Dot(Vector4(m_11, m_12, m_13, m_14), Vector4(a_m4.m_11, a_m4.m_21, a_m4.m_31, a_m4.m_41)),
		Dot(Vector4(m_21, m_22, m_23, m_24), Vector4(a_m4.m_11, a_m4.m_21, a_m4.m_31, a_m4.m_41)),
		Dot(Vector4(m_31, m_32, m_33, m_34), Vector4(a_m4.m_11, a_m4.m_21, a_m4.m_31, a_m4.m_41)),
		Dot(Vector4(m_41, m_42, m_43, m_44), Vector4(a_m4.m_11, a_m4.m_21, a_m4.m_31, a_m4.m_41)),

		//Second Column.
		Dot(Vector4(m_11, m_12, m_13, m_14), Vector4(a_m4.m_12, a_m4.m_22, a_m4.m_32, a_m4.m_42)),
		Dot(Vector4(m_21, m_22, m_23, m_24), Vector4(a_m4.m_12, a_m4.m_22, a_m4.m_32, a_m4.m_42)),
		Dot(Vector4(m_31, m_32, m_33, m_34), Vector4(a_m4.m_12, a_m4.m_22, a_m4.m_32, a_m4.m_42)),
		Dot(Vector4(m_41, m_42, m_43, m_44), Vector4(a_m4.m_12, a_m4.m_22, a_m4.m_32, a_m4.m_42)),

		//Third Column.
		Dot(Vector4(m_11, m_12, m_13, m_14), Vector4(a_m4.m_13, a_m4.m_23, a_m4.m_33, a_m4.m_43)),
		Dot(Vector4(m_21, m_22, m_23, m_24), Vector4(a_m4.m_13, a_m4.m_23, a_m4.m_33, a_m4.m_43)),
		Dot(Vector4(m_31, m_32, m_33, m_34), Vector4(a_m4.m_13, a_m4.m_23, a_m4.m_33, a_m4.m_43)),
		Dot(Vector4(m_41, m_42, m_43, m_44), Vector4(a_m4.m_13, a_m4.m_23, a_m4.m_33, a_m4.m_43)),

		//Fourth Column.
		Dot(Vector4(m_11, m_12, m_13, m_14), Vector4(a_m4.m_14, a_m4.m_24, a_m4.m_34, a_m4.m_44)),
		Dot(Vector4(m_21, m_22, m_23, m_24), Vector4(a_m4.m_14, a_m4.m_24, a_m4.m_34, a_m4.m_44)),
		Dot(Vector4(m_31, m_32, m_33, m_34), Vector4(a_m4.m_14, a_m4.m_24, a_m4.m_34, a_m4.m_44)),
		Dot(Vector4(m_41, m_42, m_43, m_44), Vector4(a_m4.m_14, a_m4.m_24, a_m4.m_34, a_m4.m_44))
	              );
}

const Matrix4& Matrix4::operator*=(const Matrix4& a_m3)
{
	*this = (*this) * a_m3;
	return *this;
}
//================================================
//Transpose Matrix - Transform From Row To Column.
//================================================
void Matrix4::Transpose()
{
	float k;
	k = m_12; m_12 = m_21; m_21 = k;
	k = m_13; m_13 = m_31; m_31 = k;
	k = m_14; m_14 = m_41; m_41 = k;
	k = m_23; m_23 = m_32; m_32 = k;
	k = m_24; m_24 = m_42; m_42 = k;
	k = m_34; m_34 = m_43; m_43 = k;
}

Matrix4 Matrix4::GetTranspose() const
{
	return Matrix4(m_11, m_12, m_13, m_14,
		           m_21, m_22, m_23, m_24,
		           m_31, m_32, m_33, m_34,
		           m_41, m_42, m_43, m_44);
}
//====================
//Scale Functionality.
//====================
void Matrix4::Scale(const Vector4& a_v4)
{
	m_11 = a_v4.x; m_12 = 0.0f; m_13 = 0.0f; m_14 = 0.0f;
	m_21 = 0.0f; m_22 = a_v4.y; m_23 = 0.0f; m_24 = 0.0f;
	m_31 = 0.0f; m_32 = 0.0f; m_33 = a_v4.z; m_34 = 0.0f;
	m_41 = 0.0f; m_42 = 0.0f; m_43 = 0.0f; m_44 = a_v4.w;
}

void Matrix4::Scale(float a_fScalar)
{
	Scale(Vector4(a_fScalar, a_fScalar, a_fScalar, 0));
}
//=========================
//General Matrix Functions.
//=========================
void Matrix4::Identity()
{
	    m_11 = 1.0f; m_12 = 0.0f; m_13 = 0.0f; m_14 = 0.0f;
		m_21 = 0.0f; m_22 = 1.0f; m_23 = 0.0f; m_24 = 0.0f;
		m_31 = 0.0f; m_32 = 0.0f; m_33 = 1.0f; m_34 = 0.0f;
		m_41 = 0.0f; m_42 = 0.0f; m_43 = 0.0f; m_44 = 1.0f;
}
