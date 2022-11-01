///////////////////////////////////////////////////////////////////////
// File:            LibMath.h
// Author:          Jack Kellett
// Date Created:    23/04/2021
// Brief:           contains all the includes for the math library.
///////////////////////////////////////////////////////////////////////
#ifndef _LIBMATH_H_
#define _LIBMATH_H_

#include "Random.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Ray.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

static float ClampFloat(float a_fValue, float a_fMinvalue, float a_fMaxValue)
{
	if (a_fValue <= a_fMinvalue)
	{
		return a_fMinvalue;
	}
	else if (a_fValue >= a_fMaxValue)
	{
		return a_fMaxValue;
	}
	else
	{
		return a_fValue;
	}
}

static int ClampInt(int a_iValue, int a_iMinValue, int a_iMaxValue)
{
	if (a_iValue <= a_iMinValue)
	{
		return a_iMinValue;
	}
	else if (a_iValue >= a_iMaxValue)
	{
		return a_iMaxValue;
	}
	else
	{
		return a_iValue;
	}
}

#endif // !_LIBMATH_H_
