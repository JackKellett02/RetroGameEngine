////////////////////////////////////////////////////////////////////////////
// File:               AimCommand.h
// Author:             Jack Kellett
// Date Created:       23/04/2021
// Brief:              The command class that when used controls gun aiming.
////////////////////////////////////////////////////////////////////////////
#ifndef _AIMLEFTCOMMAND_H_
#define _AIMLEFTCOMMAND_H_
#include "Command.h"
#include "AntiAirCannon.h"
#include "MathUtility.h"
#include "Timer.h"

class AimCommand : public Command
{
private:
	//Variables
	Timer* m_tTimer = Timer::Instance();
	AntiAirCannon* m_gCannon;
	float m_fRotationAmmount;

public:
	//=======================
	//Constructor/Destructor.
	//=======================
	AimCommand(AntiAirCannon* a_gCannon, float a_fAmmountToRotate);
	~AimCommand();
	//=======================
	//Execute function.
	//=======================
	void Execute();
};

#endif // !_AIMLEFTCOMMAND_H_