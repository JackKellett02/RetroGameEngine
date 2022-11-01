/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:           PlayerManager.h
// Author:         Jack Kellett
// Date Created:   13/05/2021
// Brief:          This class will track the player's cities and bullets and give them a score at the end of each round based on those variables.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _PLAYERMANAGER_H_
#define _PLAYERMANAGER_H_
#include "GameState.h"
#include "HighScoreManager.h"

class PlayerManager
{
private:
	//Member variables.
	int m_iScore;
	int m_iCityCount;
	int m_iScoreMultiplier;

	//Pointer to game managers controller.
	GameState* m_gGameState;
	HighScoreManager* m_hHighScoreManager;

	//Ammo variables.
	int m_iMaxAmmo;
	int m_iAmmoCount;

	//Round counter.
	int m_iRoundCounter;

public:
	//Public access functions.
	//Constructor/Destructor.
	PlayerManager();
	PlayerManager(HighScoreManager* a_hHighScoreManager, GameState* a_gGameStateManager, int a_iAmmoCount);
	~PlayerManager();

	//General Update Function.
	void Update();

	//Getters.
	int GetPlayerScore();
	int GetCityCount();
	int GetAmmoCount();
	int GetMaxAmmo();
	int GetScoreMultiplier();

	//Setters.
	void SetRoundCount(int a_iRoundCount);

	//Increment/Decrement city count by 1.
	void IncrementCityCount();
	void DecrementCityCount();

	//Change Ammo Count By 1.
	void IncrementAmmo();
	void DecrementAmmo();

	//Reset Functions.
	void ResetAmmoCount();
	void ResetScore();

	//Calculate the player score from the number of cities and amount of ammo left.
	void CalculatePlayerScore();
};

#endif // !_PLAYERMANAGER_H_
