#pragma once
//Ray  Class to store 3D Ray. Origin is start point of Ray. Direction is the direction of the ray. Max length is the max length the ray can project.
#include "Vector3.h"
#include <limits>

class Ray
{
private:
	//Member Variables
	Vector3 m_v3Origin;            //Ray Origin.
	Vector3 m_v3Direction;         //Ray Direction.
	float m_MaxLength;             //Max length of ray.
public:
#pragma region Constructors/Destructors.
	//Constructors
	Ray();
	Ray(const Ray& a_Ray);
	Ray(const Vector3& a_v3Origin, const Vector3& a_v3Direction);
	Ray(const Vector3& a_v3Origin, const Vector3& a_v3Direction, float a_maxLength);

	//Destructor
	~Ray();
#pragma endregion
#pragma region Getters
	//Getters
	Vector3 Origin() const
	{
		return m_v3Origin;
	}
	Vector3 Direction() const
	{
		return m_v3Direction;
	}
#pragma endregion
	//Get point along ray at distance.
	Vector3 PointAt(float a_distance);

	//Sphere intersection test.
	float IntersectSphere(const Vector3& a_center, const float a_radius);
};