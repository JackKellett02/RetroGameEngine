#pragma once
//Vector3 - 3 dimensional vector class

class Vector3
{
public:
	//Member variables
	float x;
	float y;
	float z;
#pragma region Constructors/Destructors
	//Constructors
	Vector3();
	Vector3(const float a_x, const float a_y, const float a_z);
	Vector3(const Vector3& a_v3);
	//Destructor
	~Vector3();
#pragma endregion

#pragma region Operator Overloads.
	//Equivalence Operators
	bool operator == (const Vector3& a_v3) const;
	bool operator != (const Vector3& a_v3) const;

	//Negate Operator
	const Vector3 operator - () const;

	//Addition Operators
	Vector3 operator + (const Vector3& a_v3) const;
	Vector3 operator + (const float a_f) const;

	//Subtraction Operators
	Vector3 operator - (const float a_f) const;
	Vector3 operator - (const Vector3& a_v3) const;

	//Multiplication Operators
	Vector3 operator * (const Vector3& a_v3) const;
	Vector3 operator * (const float& a_f) const;

	//Dot Product Functionality
	float Dot(const Vector3& a_v3) const;
	friend float Dot(const Vector3& a_v3A, const Vector3& a_v3B);

	//Cross Product Functionality
	Vector3 CrossProduct(const Vector3& a_v3) const;
	friend Vector3 CrossProduct(const Vector3& a_v3A, const Vector3& a_v3B);
#pragma endregion 
	//Get length of vector
	float Length() const;
	
	//Normalise the vector - modifies member variables (non const function)
	void Normalize();

	//Linear Interpolate
	friend Vector3 Lerp(const Vector3& a_v3A, const Vector3& a_v3B, const float a_t);
};