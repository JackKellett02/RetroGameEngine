#include "..\include\HighScoreManager.h"

//Default constructor.
HighScoreManager::HighScoreManager()
{
	GetHighScoreFromFile();
}

//Destructor.
HighScoreManager::~HighScoreManager()
{
	WriteHighScoreToFile();
}

//Clamps the current high score to between what the high score was before and the maximum possible integer. So if a_iScore is higher than the high score, a_iScore becomes the high score.
void HighScoreManager::CheckHighScore(int a_iScore)
{
	m_iCurrentHighScore = ClampFloat(a_iScore, m_iCurrentHighScore, INT_MAX);
}

//Gets the current high score.
int HighScoreManager::GetHighScore()
{
	return m_iCurrentHighScore;
}

//Retrieves the current high score from "HighScore.txt".
void HighScoreManager::GetHighScoreFromFile()
{
	std::string spath = SDL_GetBasePath();
	ifstream highScoreFile{ spath.append("HighScore.txt"), ios::in };
	//Exit program if unable to create file.
	if (!highScoreFile)
	{
		exit(EXIT_FAILURE);
	}

	//Get high score from file.
	highScoreFile >> m_iCurrentHighScore;
}

//When the program closes, overwrite the value in "HighScore.txt" with the current high score.
void HighScoreManager::WriteHighScoreToFile()
{
	//Set the high score in the file to the current high score.
	std::string spath = SDL_GetBasePath();
	ofstream highScoreFile{ spath.append("HighScore.txt"), ios::out };

	//Exit program if unable to create file.
	if (!highScoreFile)
	{
		exit(EXIT_FAILURE);
	}

	//Change value in text file to current high score.
	highScoreFile << m_iCurrentHighScore;
	//Close the file.
	highScoreFile.close();
}