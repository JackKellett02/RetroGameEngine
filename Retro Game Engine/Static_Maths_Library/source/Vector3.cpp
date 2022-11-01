#include "Vector3.h"
#include <math.h>

//Default Constructor
Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

//Constructor with X, Y, Z Values.
Vector3::Vector3(const float a_x, const float a_y, const float a_z)
{
	x = a_x;
	y = a_y;
	z = a_z;
}

//Copy Constructor
Vector3::Vector3(const Vector3& a_v3)
{
	x = a_v3.x;
	y = a_v3.y;
	z = a_v3.z;
}

//Destructor
Vector3::~Vector3()
{
	//Nothing newed so nothing deleted!
}

//Equivalence operators.
bool Vector3::operator ==(const Vector3& a_v3) const
{
	return (x == a_v3.x && y == a_v3.y && z == a_v3.z);
}

bool Vector3::operator !=(const Vector3& a_v3) const
{
	return (x != a_v3.x || y != a_v3.y || z != a_v3.z);
}

//Negative Operator
const Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

//Overload Operators For Vector3 addition
Vector3 Vector3::operator+(const Vector3& a_v3) const
{
	return Vector3(x + a_v3.x, y + a_v3.y, z + a_v3.z);
}

Vector3 Vector3::operator+(const float a_f) const
{
	return Vector3(x + a_f, y + a_f, z + a_f);
}

//Subtraction Operators
Vector3 Vector3::operator-(const float a_f) const
{
	return Vector3(x - a_f, y - a_f, z - a_f);
}

Vector3 Vector3::operator-(const Vector3& a_v3) const
{
	return Vector3(x - a_v3.x, y - a_v3.y, z - a_v3.z);
}

//Multiplication Operator
//Vector3 Vector3::operator*(const Vector3& a_v3) const
//{
//	return Vector3(x * a_v3.x, y * a_v3.y, z * a_v3.z);
//}

Vector3 Vector3::operator*(const float& a_f) const
{
	return Vector3(x * a_f, y * a_f, z * a_f);
}

//Dot Product Functionality.
float Vector3::Dot(const Vector3& a_v3) const
{
	return (x * a_v3.x + y * a_v3.y + z * a_v3.z);
}

float Dot(const Vector3& a_v3A, const Vector3& a_v3B)
{
	return a_v3A.Dot(a_v3B);
}

//Cross Product functionality.
Vector3 Vector3::CrossProduct(const Vector3& a_v3) const
{
	return Vector3(y * a_v3.z - z * a_v3.y, z * a_v3.x - x * a_v3.z, x * a_v3.y - y * a_v3.x);
}

Vector3 CrossProduct(const Vector3& a_v3A, const Vector3& a_v3B)
{
	return a_v3A.CrossProduct(a_v3B);
}

//Get the length of the vector
float Vector3::Length() const
{
	return sqrtf(x * x + y * y + z * z);
}

//Normalise the vector
void Vector3::Normalize()
{
	float length = Length();
	if (length > 0.0f) // if this is false vector has no length.
	{
		float invLen = 1.0f / length;
		x *= invLen;
		y *= invLen;
		z *= invLen;
	}
}

//Linear Interpolate
Vector3 Lerp(const Vector3& a_v3A, const Vector3& a_v3B, const float a_t)
{
	return (a_v3B - a_v3A) * a_t + a_v3A;
}