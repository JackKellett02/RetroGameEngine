#include "Vector2.h"
#include <math.h>

//Default Constructor.
Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

//Constructor with x and y values.
Vector2::Vector2(const float a_x, const float a_y)
{
	x = a_x;
	y = a_y;
}

//Copy Constructor.
Vector2::Vector2(const Vector2& a_v2)
{
	x = a_v2.x;
	y = a_v2.y;
}

//Destructor.
Vector2::~Vector2()
{
	//Nothing newed so nothing needs to be deleted.
}

//Equivalence operators.
bool Vector2::operator ==(const Vector2& a_v2) const
{
	return (x == a_v2.x && y == a_v2.y);
}

bool Vector2::operator !=(const Vector2& a_v2) const
{
	return (x != a_v2.x || y != a_v2.y);
}

//Negative Operator
const Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

//Overload Operators for Vector2 addition.
Vector2 Vector2::operator+(const Vector2& a_v2) const
{
	return Vector2(x + a_v2.x, y + a_v2.y);
}

//Subtraction Operators.
Vector2 Vector2::operator-(const Vector2& a_v2) const
{
	return Vector2(x - a_v2.x, y - a_v2.y);
}

//Multiplication Operators.
Vector2 Vector2::operator*(const float& a_f) const
{
	return Vector2(x * a_f, y * a_f);
}

//Divison Operators.
Vector2 Vector2::operator/(const float& a_f) const
{
	return Vector2(x / a_f, y / a_f);
}

//Dot Product - Projection of one vector along another or the cosine value of the angle between two vectors.
float Vector2::Dot(const Vector2& a_v2) const
{
	return (x * a_v2.x + y * a_v2.y);
}

//Dot Product - Friend function allows use to do the following in code.
//              Vector2 result = Dot(vec2A, vec2B);
//              notice the lack of "Vector2::" prior to the function name.
float Dot(const Vector2& a_v2A, const Vector2& a_v2B)
{
	return a_v2A.Dot(a_v2B);
}

//Get Length
float Vector2::Length()
{
	return sqrtf(x * x + y * y);
}

float Vector2::LengthSqr()
{
	return (x * x + y * y);
}

//Normalise the vector
void Vector2::Normalize()
{
	float length = Length();
	if (length > 0.0f) // if this is false vector has no length.
	{
		float invLen = 1.0f / length;
		x *= invLen;
		y *= invLen;
	}
}