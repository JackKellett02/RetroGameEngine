#include "GameManager.h"

int main(int argc, char* argv[])
{
	//Create a game manager instance.
	GameManager* game = GameManager::Instance();

	//Run the game.
	game->Run();

	//Destroy the game manager instance.
	GameManager::Release();
	game = NULL;

	//Exit the program.
	return 0;
}