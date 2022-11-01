#ifndef _GAMEMANAGE_H_
#define _GAMEMANAGE_H_
#include "Graphics.h"
#include "Timer.h"
#include "GameObject.h"
#include "Texture.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "ExplosionManager.h"
#include "PlayerManager.h"
#include "CityManager.h"
#include "Button.h"
#include "BombSpawner.h"
#include "HighScoreManager.h"

class GameManager
{
private:
	static GameManager* m_sInstance; //This is the game manager's instance.

	const int FRAME_RATE = 60;
	Timer* m_tTimer;

	bool m_bQuit = false;//Whether or not the game should be quit.
	bool m_bEnteringState = true;//Whether or not the game is entering a state.
	Graphics* m_gGraphics;//A pointer to the graphics class.

	SDL_Event m_sdlEvent;

	//Game State Variables.
	GameState* m_gGameState;

	//Menu Variables.
	Menu* m_mCurrentMenu;

	//Managers
	TextureManager* m_tTextureManager;
	InputManager* m_iInputManager;
	ExplosionManager* m_eExplosionManager;
	PlayerManager* m_pPlayerManager;
	CityManager* m_cCityManager;
	HighScoreManager* m_hHighScoreManager;

	//Input Classes
	AimCommand* m_cAimLeftCommand;
	AimCommand* m_cAimRightCommand;
	FireCommand* m_cFireCommand;
	CannonRangeCommand* m_cIncreaseRangeCommand;
	CannonRangeCommand* m_cDecreaseRangeCommand;
	ChangeButtonCommand* m_cIncrementMenuIndex;
	ChangeButtonCommand* m_cDecrementMenuIndex;
	UseButtonCommand* m_cUseButton;

	//Menu Button Commands.
	ChangeStateCommand* m_cStartGameCommand;
	ChangeStateCommand* m_cControlsCommand;
	ChangeStateCommand* m_cQuitGameCommand;

	//Game Objects.
	AntiAirCannon* m_gAntiAirCannon;

	//Spawners.
	BombSpawner* m_bBombSpawner;
	int m_iBombsToSpawn;
	int m_iRound;

	//Text Stuff.
	Texture* m_tControlsTexture;
	Texture* m_tScoreText;
	Texture* m_tCitiesText;
	Texture* m_tAmmoText;
	Texture* m_tGameOverText;
	Texture* m_tHighScoreText;
	Texture* m_tRoundText;
	Texture* m_tScoreMultiplierText;

	//Timer float.
	float m_fTimer;

public:
	static GameManager* Instance();
	static void Release();

	void Run();

private:
	//Constructor/Destructor.
	GameManager();
	~GameManager();

	//Scene Switch Functions. These will be accessed from the GameState class when the state changes.
	void SwitchToMainMenu();
	void SwitchToControlsScreen();
	void SwitchToGameOver();
	void SwitchToGame();
	void SetUpGameText();


	//Text Functions.
	void UpdateText();

	//Reset main game variables and commands.
	void ResetGameVariables();
};

#endif // !_GAMEMANAGE_H_
