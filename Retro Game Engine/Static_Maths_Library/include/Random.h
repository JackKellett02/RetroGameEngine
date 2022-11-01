/////////////////////////////////////////////////////////////////////////////////////
// Class that implements a random number generator
// that uses the following rule:
//                             seed = (a*seed + c) & m;
//                             randomInt = seed & L;
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _RANDOM_H_
#define _RANDOM_H_

namespace Random
{
	//Gets current seed.
	int GetSeed();
	//Sets current seed.
	void SetSeed(const int& iSeed);
	//Gets max allowed integer.
	int RandMax();

	//Random integer number generator.
	int RandInt();
	int RandRange(const int& iMin, const int& iMax);
	//Random float number generator from 0.0f to 1.0f.
	float RandFloat();
	//Random float number generator from interval [x0,x1].
	float RandRange(const float& fx0, const float& fx1);
}
#endif // !_RANDOM_H_
