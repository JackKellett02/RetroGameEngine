#include "..\include\PlayerManager.h"

//Default Constructor.
PlayerManager::PlayerManager()
{
	m_gGameState = nullptr;
	m_iScore = 0;
	m_iCityCount = 0;
	m_iMaxAmmo = 50;
	ResetAmmoCount();
}

//Constructor with values.
PlayerManager::PlayerManager(HighScoreManager* a_hHighScoreManager, GameState* a_gGameStateManager, int a_iAmmoCount)
{
	m_hHighScoreManager = a_hHighScoreManager;
	m_gGameState = a_gGameStateManager;
	m_iScore = 0;
	m_iCityCount = 0;
	m_iMaxAmmo = a_iAmmoCount;
	ResetAmmoCount();
}

//Destructor.
PlayerManager::~PlayerManager()
{
	//Nothing newed so nothing deleted.
	m_gGameState = nullptr;
}

//Updates the state of the player and switches the game state to "GAME_OVER" if the player has ran out of cities.
void PlayerManager::Update()
{
	//If the game state controller exists.
	if (m_gGameState)
	{
		//Change the game state to game over if the city count is equal to 0.
		if (m_iCityCount <= 0)
		{
			m_gGameState->SetGameState(GAME_OVER);
		}
	}
}

//Gets the current player score.
int PlayerManager::GetPlayerScore()
{
	return m_iScore;
}

//Gets the current city count.
int PlayerManager::GetCityCount()
{
	return m_iCityCount;
}

//Gets the current ammo count.
int PlayerManager::GetAmmoCount()
{
	return m_iAmmoCount;
}

//Gets the maximum amount of ammo possible.
int PlayerManager::GetMaxAmmo()
{
	return m_iMaxAmmo;
}

int PlayerManager::GetScoreMultiplier()
{
	return m_iScoreMultiplier;
}

void PlayerManager::SetRoundCount(int a_iRoundCount)
{
	m_iRoundCounter = a_iRoundCount;
}

//Increments the city counter by 1.
void PlayerManager::IncrementCityCount()
{
	m_iCityCount += 1;
}

//Decrements the city counter by 1.
void PlayerManager::DecrementCityCount()
{
	m_iCityCount -= 1;
}

//Increments the ammo count by 1.
void PlayerManager::IncrementAmmo()
{
	m_iAmmoCount += 1;
}

//Decrements the ammo count by 1.
void PlayerManager::DecrementAmmo()
{
	m_iAmmoCount -= 1;
}

//Resets the ammo count.
void PlayerManager::ResetAmmoCount()
{
	m_iAmmoCount = m_iMaxAmmo;
}

//Resets the score.
void PlayerManager::ResetScore()
{
	m_iScore = 0;
	m_iScoreMultiplier = 1;
}

//Calulates the new player score at the end of each round and updates the high score if it's a new high score.
void PlayerManager::CalculatePlayerScore()
{
	//Multiplier increases only every couple of rounds due to fact that 
	m_iScoreMultiplier = 1 + (m_iRoundCounter / 2);
	m_iScore += (((m_iAmmoCount * 5) + (m_iCityCount * 100)) * m_iScoreMultiplier);
	m_hHighScoreManager->CheckHighScore(m_iScore);
}