#include "GameState.h"

//Default constructor.
GameState::GameState()
{
	m_gGameState = MAIN_MENU;
	m_gLastGameState = DEFAULT;
	m_gTransitionState = DEFAULT;
}

//Destructor.
GameState::~GameState()
{
	//nothing newed so nothing deleted.
}

//Gets the current state of the game.
GameStates GameState::GetCurrentGameState()
{
	return m_gGameState;
}

//Brings the state of the game directly to the target state.
void GameState::SetProperState(GameStates a_gGameState)
{
	m_gGameState = a_gGameState;
}

//Brings the state of the game to a transition state before going to the target state.
void GameState::SetGameState(GameStates a_gGameState)
{
	m_gLastGameState = m_gGameState;
	m_gGameState = DEFAULT;
	m_gTransitionState = a_gGameState;
}

//Gets the state that the program will be switching to.
GameStates GameState::GetTransitionState()
{
	return m_gTransitionState;
}