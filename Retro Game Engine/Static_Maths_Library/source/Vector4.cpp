#include "Vector4.h"
#include <math.h>

//Default Constructor
Vector4::Vector4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

//Constructor with X, Y, Z Values.
Vector4::Vector4(const float a_x, const float a_y, const float a_z, const float a_w)
{
	x = a_x;
	y = a_y;
	z = a_z;
	w = a_w;
}

//Copy Constructor
Vector4::Vector4(const Vector4& a_v4)
{
	x = a_v4.x;
	y = a_v4.y;
	z = a_v4.z;
	w = a_v4.w;
}

//Destructor
Vector4::~Vector4()
{
	//Nothing newed so nothing deleted!
}

//Equivalence operators.
bool Vector4::operator ==(const Vector4& a_v4) const
{
	return (x == a_v4.x && y == a_v4.y && z == a_v4.z && w == a_v4.w);
}

bool Vector4::operator !=(const Vector4& a_v4) const
{
	return (x != a_v4.x || y != a_v4.y || z != a_v4.z || w != a_v4.w);
}

//Negative Operator
const Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, w);
}

//Overload Operators For Vector4 addition
Vector4 Vector4::operator+(const Vector4& a_v4) const
{
	return Vector4(x + a_v4.x, y + a_v4.y, z + a_v4.z, w + a_v4.w);
}

Vector4 Vector4::operator+(const float a_f) const
{
	return Vector4(x + a_f, y + a_f, z + a_f, w + a_f);
}

//Subtraction Operators
Vector4 Vector4::operator-(const float a_f) const
{
	return Vector4(x - a_f, y - a_f, z - a_f, w - a_f);
}

Vector4 Vector4::operator-(const Vector4& a_v4) const
{
	return Vector4(x - a_v4.x, y - a_v4.y, z - a_v4.z, w);
}

Vector4 Vector4::operator*(const float& a_f) const
{
	return Vector4(x * a_f, y * a_f, z * a_f, w);
}

//Dot Product Functionality.
float Vector4::Dot(const Vector4& a_v4) const
{
	return (x * a_v4.x + y * a_v4.y + z * a_v4.z + w * a_v4.w);
}

float Dot(const Vector4& a_v4A, const Vector4& a_v4B)
{
	return a_v4A.Dot(a_v4B);
}

//Cross Product functionality.
Vector4 Vector4::CrossProduct(const Vector4& a_v4) const
{
	return Vector4(y * a_v4.z - z * a_v4.y, z * a_v4.x - x * a_v4.z, x * a_v4.y - y * a_v4.x, 0);
}

Vector4 CrossProduct(const Vector4& a_v4A, const Vector4& a_v4B)
{
	return a_v4A.CrossProduct(a_v4B);
}

//Get the length of the vector
float Vector4::Length() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

//Normalise the vector
void Vector4::Normalize()
{
	float length = Length();
	if (length > 0.0f) // if this is false vector has no length.
	{
		float invLen = 1.0f / length;
		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;
	}
}

//Linear Interpolate
Vector4 Lerp(const Vector4& a_v3A, const Vector4& a_v3B, const float a_t)
{
	return (a_v3B - a_v3A) * a_t + a_v3A;
}