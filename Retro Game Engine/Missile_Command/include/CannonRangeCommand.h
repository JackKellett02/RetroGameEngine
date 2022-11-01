///////////////////////////////////////////////////////////////////////////////////////////
// File:          CannonRangeCommand.h
// Author:        Jack Kellett
// Date Created:  30/04/2021
// Brief:         This is what will increase or decrease how far the projectile will shoot.
///////////////////////////////////////////////////////////////////////////////////////////
#ifndef _CANNONRANGECOMMAND_H_
#define _CANNONRANGECOMMAND_H_
#include "Command.h"
#include "AntiAirCannon.h"
#include "Timer.h"

class CannonRangeCommand : public Command
{
private:
	//Pointer to the player's aa gun.
	AntiAirCannon* m_gCannon;
	Timer* m_tTimer = Timer::Instance();
	float m_fRangeTranformValue;

public:
	//Constructor/destructor.
	CannonRangeCommand(AntiAirCannon* a_gCannon, float a_fRangeTransformValue);
	~CannonRangeCommand();

	//Execute Method.
	void Execute();
};

#endif // !_CANNONRANGECOMMAND_H_
