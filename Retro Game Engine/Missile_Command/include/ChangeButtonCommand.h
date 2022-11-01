///////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:            ChangeButtonCommand.h
// Author:          Jack Kellett
// Date Created:    07/05/2021
// Brief:           This is the command that when run will increment or decrement the menu index.
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _CHANGEBUTTONCOMMAND_H_
#define _CHANGEBUTTONCOMMAND_H_
#include "MathUtility.h"
#include "Command.h"
#include "Menu.h"
#include "Timer.h"

class ChangeButtonCommand : public Command
{
private:
	//Menu Pointer
	Menu* m_mMenu;

	//Timer
	Timer* m_tTimer; //For timing how long till the player can change button again.
	float m_fTimer;
	float m_fTimeToChangeButton;

	//Increment or Decrement.
	bool m_bIncrement;

public:
	//Public Access Functions
	//Constructor/Destructor
	ChangeButtonCommand(Menu* a_mMenu, bool a_bIncrement, float a_fTimeToChangeButton);
	~ChangeButtonCommand();

	//Update
	void Update();

	//Execute Function.
	void Execute();
};
#endif // !_CHANGEBUTTONCOMMAND_H_
