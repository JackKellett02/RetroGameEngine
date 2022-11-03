#include "GameManager.h"
#include <iostream>

int main(int argc, char* argv[])
{
	//Create a game manager instance.
	GameManager* game = GameManager::Instance();

	//Run the game.
	game->Run();

	//Destroy the game manager instance.
	GameManager::Release();
	game = nullptr;

	//Exit the program.
	std::cout << "Program Compiled And Exited Successfully" << std::endl;
	std::cin.get();
	return 0;
}