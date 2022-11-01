#include "ChangeStateCommand.h"

//Constructor with values.
ChangeStateCommand::ChangeStateCommand(CityManager* a_cCityManager, GameState* a_gGameState, GameStates a_gNewState)
{
	m_cCityManager = a_cCityManager;
	m_gGameState = a_gGameState;
	m_gNewState = a_gNewState;
}

//Destructor.
ChangeStateCommand::~ChangeStateCommand()
{
	//I don't delete this as it's deleted by the game manager.
	m_gGameState = nullptr;
}

//Switch the game state to the new game state.
void ChangeStateCommand::Execute()
{
	if (m_gGameState)
	{
		if (m_gNewState == GAME)
		{
			//Create the cities but have them deactivated so that they can be activated when going into game.
			m_cCityManager->CreateCities(6);
		}
		m_gGameState->SetGameState(m_gNewState);
	}
}