////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:           HighScoreManager.h
// Author:         Jack Kellett
// Date Created:   16/05/2021
// Brief:          Stores the current high score and whenever the score is calculated it checks that score vs the current high score and swaps if necessary.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HIGHSCOREMANAGER_H_
#define _HIGHSCOREMANAGER_H_
#include "MathUtility.h"
#include <iostream>
#include <fstream>
#include <SDL.h>
using namespace std;

class HighScoreManager
{
private:
	//Member Variables.
	int m_iCurrentHighScore;

	//Private Functions
	//Read/Write From/To file functions.
	void GetHighScoreFromFile();
	void WriteHighScoreToFile();
public:
	//Public Access Functions.
	//Constructor/Destructor.
	HighScoreManager();
	~HighScoreManager();

	//Check High Score Functions.
	void CheckHighScore(int a_iScore);

	//Getters.
	int GetHighScore();
};

#endif // !_HIGHSCOREMANAGER_H_
