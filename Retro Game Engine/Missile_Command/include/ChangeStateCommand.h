///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:             ChangeStateCommand.h
// Author:           Jack Kellett
// Date Created:     07/05/2021
// Brief:            Switches game state to GAME.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _CHANGESTATECOMMAND_H_
#define _CHANGESTATECOMMAND_H_
#include "MathUtility.h"
#include "Command.h"
#include "GameState.h"
#include "CityManager.h"

class ChangeStateCommand : public Command
{
private:
	GameState* m_gGameState; //This is the game state manager that stores what state the game is currently in.
	GameStates m_gNewState; //This is the state that this command should set the game to when run.

	//City Manager.
	CityManager* m_cCityManager;

public:
	//==================================
	// Constructor/Destructor.
	//==================================
	ChangeStateCommand(CityManager* a_cCityManager, GameState* a_gGameState, GameStates a_gNewState);
	~ChangeStateCommand();
	//==================================
	// Execute Function.
	//==================================
	void Execute();
};
#endif // !_CHANGESTATECOMMAND_H_
