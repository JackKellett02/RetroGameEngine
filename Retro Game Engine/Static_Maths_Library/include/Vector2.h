#ifndef _VECTOR2_H_
#define _VECTOR2_H_

//Vector 2 - 2 dimensional vector class.
class Vector2
{
public:
	//Member Variables.
	float x;
	float y;
#pragma region Constructors/Destructors
	//Constructors.
	Vector2();
	Vector2(const float a_x, const float a_y);
	Vector2(const Vector2& a_v2);

	//Destructor.
	~Vector2();
#pragma endregion
#pragma region Operator Overloads
	//Equivalence operators.
	bool operator == (const Vector2& a_v2) const;
	bool operator != (const Vector2& a_v2) const;

	//Negate Operator
	const Vector2 operator - () const;

	//Addition Operators.
	Vector2 operator + (const Vector2& a_v2) const;

	//Subtraction Operators.
	Vector2 operator - (const Vector2& a_v2) const;

	//Multiplication Operators.
	Vector2 operator * (const float& a_f) const;

	//Division Operators.
	Vector2 operator / (const float& a_f) const;

	//Dot Product Functionality.
	float Dot(const Vector2& a_v2) const;
	friend float Dot(const Vector2& a_v2B);
#pragma endregion
	//Normalize Vector
	void Normalize();
	float Length();
	float LengthSqr();
};

#endif // !_VECTOR2_H_
