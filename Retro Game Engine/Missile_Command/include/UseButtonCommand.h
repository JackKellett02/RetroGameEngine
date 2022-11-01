/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:                      UseButtonCommand.h
// Author:                    Jack Kellett
// Date Created:              02/05/2021
// Brief:                     This is the command that when executed will run whatever command is on the currently selected button.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _USEBUTTONCOMMAND_H_
#define _USEBUTTONCOMMAND_H_
#include "MathUtility.h"
#include "Command.h"
#include "Menu.h"
#include "Timer.h"

class UseButtonCommand : public Command
{
private:
	//Variable Declarations.
	Button* m_bCurrentlySelectedButton;
	Menu* m_mMenu;

	//Timer
	Timer* m_tTimer; //For timing how long till the player can change button again.
	float m_fTimer;
	float m_fTimeToChangeButton;

	//Private Functions
	void SetSelectedButton();

public:
	//Public Access Functions
	UseButtonCommand(Menu* a_mMenu, float a_fTimeToChange);
	~UseButtonCommand();

	//Update timer.
	void Update();

	//Execute Function.
	void Execute();
};

#endif // !_USEBUTTONCOMMAND_H_
