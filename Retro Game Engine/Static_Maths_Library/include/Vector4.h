#pragma once
//Vector4 - 4 dimensional vector class

class Vector4
{
public:
	//Member variables
	float x;
	float y;
	float z;
	float w;
#pragma region Constructors/Destructors
	//Constructors
	Vector4();
	Vector4(const float a_x, const float a_y, const float a_z, const float a_w);
	Vector4(const Vector4& a_v4);
	//Destructor
	~Vector4();
#pragma endregion

#pragma region Operator Overloads.
	//Equivalence Operators
	bool operator == (const Vector4& a_v4) const;
	bool operator != (const Vector4& a_v4) const;

	//Negate Operator
	const Vector4 operator - () const;

	//Addition Operators
	Vector4 operator + (const Vector4& a_v4) const;
	Vector4 operator + (const float a_f) const;

	//Subtraction Operators
	Vector4 operator - (const float a_f) const;
	Vector4 operator - (const Vector4& a_v4) const;

	//Multiplication Operators
	Vector4 operator * (const Vector4& a_v4) const;
	Vector4 operator * (const float& a_f) const;

	//Dot Product Functionality
	float Dot(const Vector4& a_v4) const;
	friend float Dot(const Vector4& a_v4A, const Vector4& a_v4B);

	//Cross Product Functionality
	Vector4 CrossProduct(const Vector4& a_v4A) const;
	friend Vector4 CrossProduct(const Vector4& a_v4A, const Vector4& a_v4B, const Vector4& a_v4C);
#pragma endregion 
	//Get length of vector
	float Length() const;

	//Normalise the vector - modifies member variables (non const function)
	void Normalize();

	//Linear Interpolate
	friend Vector4 Lerp(const Vector4& a_v4A, const Vector4& a_v4B, const float a_t);
};