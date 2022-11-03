///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:                 GameState.h
// Author:               Jack Kellett
// Date:                 07/05/2021
// Brief:                This contains all the game states for the game so that the commands can access the different states.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

enum GameStates
{
	MAIN_MENU,
	CONTROLS_SCREEN,
	GAME,
	DEFAULT,
	EXIT_GAME,
	GAME_OVER,
};

class GameState
{
private:
	//Variable Declarations.
	GameStates m_gGameState;
	GameStates m_gTransitionState;
	GameStates m_gLastGameState;

public:
	//Public Access Functions.
	//Constructor/Destructor.
	GameState();
	~GameState();

	//Getters.
	GameStates GetCurrentGameState();
	GameStates GetTransitionState();

	//Setters.
	void SetProperState(GameStates a_gGameState);
	void SetGameState(GameStates a_gGameState);
};

#endif // !_GAMESTATE_H_
