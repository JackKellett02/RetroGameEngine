/////////////////////////////////////////////////////////////////////////////////
// File:             InputManager.h
// Author:           Jack Kellett
// Date Created:     25/04/2021
// Brief:            This is the class that will deal with player input.
/////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_
#include "Command.h"
#include "AimCommand.h"
#include "FireCommand.h"
#include "CannonRangeCommand.h"
#include "ChangeButtonCommand.h"
#include "UseButtonCommand.h"
#include "ChangeStateCommand.h"

class InputManager
{
private:
	//Commands for keys to run.
	Command* m_kKeyW;
	Command* m_kKeyA;
	Command* m_kKeyS;
	Command* m_kKeyD;
	Command* m_kKeyE;
	Command* m_kKeySpace;

	//Whether or not a certain key has been pressed.
	bool m_kWPressed;
	bool m_kAPressed;
	bool m_kSPressed;
	bool m_kDPressed;
	bool m_kEPressed;
	bool m_kSpacePressed;

public:
	//Constructor/Destructor.
	InputManager();
	~InputManager();

	//Update function.
	void Update();

	//Check the inputs and decide whether or not a key has been pressed or released.
	void HandleInput(SDL_Event& a_SDLEVENT);

	//Set all commands to nullptr.
	void SetAllKeysToNullptr();

	//Assign a command to the keys.
	void AssignAKeyCommand(Command* a_cCommand);
	void AssignDKeyCommand(Command* a_cCommand);
	void AssignWKeyCommand(Command* a_cCommand);
	void AssignSKeyCommand(Command* a_cCommand);
	void AssignEKeyCommand(Command* a_cCommand);
	void AssignSpaceKeyCommand(Command* a_cCommand);
};
#endif // !_INPUTMANAGER_H_
