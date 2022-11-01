/////////////////////////////////////////////////////////////////////
// File:           FireCommmand.h
// Author:         Jack Kellett
// Date Created:   23/04/2021
// Brief:          Launchs projectile in vector of aiming angle.
/////////////////////////////////////////////////////////////////////
#ifndef _FIRECOMMAND_H_
#define _FIRECOMMAND_H_
#include "Command.h"
#include "MathUtility.h"
#include "AntiAirCannon.h"

class FireCommand : public Command
{
private:
	AntiAirCannon* m_gCannon; //This is the player's cannon gameobject.

public:
	//==================================
	// Constructor/Destructor.
	//==================================
	FireCommand(AntiAirCannon* a_gCannon);
	~FireCommand();
	//==================================
	// Execute Function.
	//==================================
	void Execute();
};


#endif // !_FIRECOMMAND_H_
