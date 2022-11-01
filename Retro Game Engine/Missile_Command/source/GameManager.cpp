#include "..\include\GameManager.h"

GameManager* GameManager::m_sInstance = NULL;

//Returns the game manager's instance.
GameManager* GameManager::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new GameManager();
	}
	return m_sInstance;
}

//Deletes the game manager's instance.
void GameManager::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;

	Timer::Release();
}

//Default Constructor.
GameManager::GameManager()
{
	m_bQuit = false;
	m_gGraphics = Graphics::Instance();

	if (!Graphics::Initialised())
	{
		m_bQuit = true;
	}
	m_tTimer = Timer::Instance();

	//Game State class.
	m_gGameState = new GameState();
	m_gGameState->SetProperState(MAIN_MENU);

	//Set up game managers.
	m_tTextureManager = new TextureManager();
	m_iInputManager = new InputManager();
	m_hHighScoreManager = new HighScoreManager();
	m_pPlayerManager = new PlayerManager(m_hHighScoreManager, m_gGameState, 100);
	m_eExplosionManager = new ExplosionManager(m_tTextureManager, m_pPlayerManager);
	m_cCityManager = new CityManager(m_tTextureManager, m_eExplosionManager, m_pPlayerManager, Vector2(50.0f, 50.0f), "Assets/City.png");

	//Input Classes.
	m_cAimLeftCommand = nullptr;
	m_cAimRightCommand = nullptr;
	m_cFireCommand = nullptr;
	m_mCurrentMenu = nullptr;
	m_cDecrementMenuIndex = nullptr;
	m_cIncrementMenuIndex = nullptr;
	m_cUseButton = nullptr;
	m_cStartGameCommand = nullptr;
	m_cDecreaseRangeCommand = nullptr;
	m_cIncreaseRangeCommand = nullptr;
	m_cQuitGameCommand = nullptr;

	//Spawner Pointers.
	m_bBombSpawner = nullptr;
	m_iBombsToSpawn = 50;
	m_iRound = 0;

	//Timer float.
	m_fTimer = 0.0f;

	//Controls screen texture.
	std::string sPath = SDL_GetBasePath();
	Vector2 position = Vector2(0.0f, 0.0f);
	Vector2 dimensions = Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);
	m_tControlsTexture = new Texture(sPath.append("Assets/TutorialScreen.png"), position, dimensions, 0.0f);

	//Other variables.
	m_gAntiAirCannon = nullptr;
	m_tAmmoText = nullptr;
	m_tCitiesText = nullptr;
	m_tGameOverText = nullptr;
	m_tHighScoreText = nullptr;
	m_tScoreText = nullptr;
}

//Destructor.
GameManager::~GameManager()
{
	Graphics::Release();
	m_gGraphics = NULL;

	delete m_gAntiAirCannon;
	m_gAntiAirCannon = NULL;

	delete m_tTextureManager;
	m_tTextureManager = NULL;

	delete m_cAimLeftCommand;
	m_cAimLeftCommand = nullptr;

	delete m_cAimRightCommand;
	m_cAimRightCommand = nullptr;

	delete m_cFireCommand;
	m_cFireCommand = nullptr;

	delete m_cIncreaseRangeCommand;
	m_cIncreaseRangeCommand = nullptr;

	delete m_cDecreaseRangeCommand;
	m_cDecreaseRangeCommand = nullptr;

	delete m_cIncrementMenuIndex;
	m_cIncrementMenuIndex = nullptr;

	delete m_cDecrementMenuIndex;
	m_cDecrementMenuIndex = nullptr;

	delete m_cUseButton;
	m_cUseButton = nullptr;

	delete m_cStartGameCommand;
	m_cStartGameCommand = nullptr;

	delete m_eExplosionManager;
	m_eExplosionManager = nullptr;

	delete m_pPlayerManager;
	m_pPlayerManager = nullptr;

	delete m_cCityManager;
	m_cCityManager = nullptr;

	delete m_tCitiesText;
	m_tCitiesText = nullptr;

	delete m_tScoreText;
	m_tScoreText = nullptr;

	delete m_hHighScoreManager;
	m_hHighScoreManager = nullptr;

	delete m_tControlsTexture;
	m_tControlsTexture = nullptr;
}

//Run the game.
void GameManager::Run()
{
	//Whilst the game is active.
	while (!m_bQuit)
	{
		//Update the timer.
		bool timerUpdated = m_tTimer->Update();

		//Run Game Logic
		if (m_tTimer->DeltaTime() >= 1.0f / FRAME_RATE && timerUpdated)
		{
			//Check for any events.
			while (SDL_PollEvent(&m_sdlEvent) != 0)
			{
				if (m_sdlEvent.type == SDL_QUIT)
				{
					m_bQuit = true;
				}

				//Handle user input.
				m_iInputManager->HandleInput(m_sdlEvent);
			}

			//Clear the back buffer.
			m_gGraphics->ClearBackBuffer();

			//Update commands.
			m_iInputManager->Update();

			//Run the correct state logic.
			switch (m_gGameState->GetCurrentGameState())
			{
				case MAIN_MENU:
				{
					if (m_bEnteringState)
					{
						SwitchToMainMenu();
						m_bEnteringState = false;
					}

					//Update the main menu.
					m_cIncrementMenuIndex->Update();
					m_cDecrementMenuIndex->Update();
					m_cUseButton->Update();
					m_mCurrentMenu->Update();

					break;
				}
				case CONTROLS_SCREEN:
				{
					if (m_bEnteringState)
					{
						SwitchToControlsScreen();
						m_bEnteringState = false;
					}
					m_cUseButton->Update();
					m_mCurrentMenu->Update();

					break;
				}
				case GAME:
				{
					if (m_bEnteringState)
					{
						SwitchToGame();
						m_bEnteringState = false;
					}

					//Update Game Objects.
					m_gAntiAirCannon->Update(m_tTimer->DeltaTime());

					//Update Game Managers.
					m_eExplosionManager->Update(m_tTimer->DeltaTime());
					m_pPlayerManager->Update();

					//Update Bomb Spawner.
					m_bBombSpawner->Update(m_tTimer->DeltaTime());

					//Update UI.
					UpdateText();

					break;
				}
				case GAME_OVER:
				{
					if (m_bEnteringState)
					{
						SwitchToGameOver();
						m_bEnteringState = false;
					}
					//Check if timer is finished.
					if (m_fTimer >= 15.0f)
					{
						//If it has go to the main menu.
						m_gGameState->SetGameState(MAIN_MENU);
					}
					else
					{
						//Increment timer.
						m_fTimer += m_tTimer->DeltaTime();

						//Update Game Managers.
						m_eExplosionManager->Update(m_tTimer->DeltaTime());
					}

					break;
				}
				case EXIT_GAME:
				{
					m_bQuit = true;
					break;
				}
				default:
				{
					//Reset all the game variables.
					ResetGameVariables();

					//Tell the game to run any functions needed to set up a state upon entering it.
					m_bEnteringState = true;
					
					//Set the state to the next state.
					m_gGameState->SetProperState(m_gGameState->GetTransitionState());
					break;
				}
			}

			//Render Textures.
			m_tTextureManager->DisplayTextures();
			m_gGraphics->Render();

			//Reset Timer.
			m_tTimer->Reset();
		}
	}
}

//Set up all the variables needed for the main menu.
void GameManager::SwitchToMainMenu()
{
	//Reset Player Score.
	m_pPlayerManager->ResetScore();

	//Reset bomb count back to normal.
	m_iBombsToSpawn = 50;
	m_iRound = 0;
	m_pPlayerManager->SetRoundCount(m_iRound);

	//Set up and assign menu values.
	m_mCurrentMenu = new Menu("Assets/WhiteSquare.png", m_tTextureManager, "Assets/MissileCommandText.png", "Assets/Stars.png");
	m_cDecrementMenuIndex = new ChangeButtonCommand(m_mCurrentMenu, false, 0.25f);
	m_cIncrementMenuIndex = new ChangeButtonCommand(m_mCurrentMenu, true, 0.25f);
	m_cUseButton = new UseButtonCommand(m_mCurrentMenu, 0.25f);

	//Assign commands to correct keys.
	m_iInputManager->AssignWKeyCommand(m_cDecrementMenuIndex);
	m_iInputManager->AssignSKeyCommand(m_cIncrementMenuIndex);
	m_iInputManager->AssignEKeyCommand(m_cUseButton);

	//Create buttons for menu.
	m_cStartGameCommand = new ChangeStateCommand(m_cCityManager, m_gGameState, GAME);
	m_cControlsCommand = new ChangeStateCommand(m_cCityManager, m_gGameState, CONTROLS_SCREEN);
	m_cQuitGameCommand = new ChangeStateCommand(m_cCityManager, m_gGameState, EXIT_GAME);
	m_mCurrentMenu->CreateNewButton(m_cStartGameCommand, Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2 - 125), Vector2(200, 100), "Assets/StartGameText.png");
	m_mCurrentMenu->CreateNewButton(m_cControlsCommand, Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2 + 25), Vector2(200, 100), "Assets/Controls.png");
	m_mCurrentMenu->CreateNewButton(m_cQuitGameCommand, Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2 + 175), Vector2(200, 100), "Assets/QuitGameText.png");

	//Show the current high score at the bottom of the screen.
	Vector2 dimensions = Vector2(200, 20.0f);
	Vector2 position = Vector2((Graphics::SCREEN_WIDTH / 2) - (dimensions.x / 2), Graphics::SCREEN_HEIGHT - (dimensions.y * 2));
	m_tHighScoreText = new Texture(std::string("High Score: ").append(std::to_string(m_hHighScoreManager->GetHighScore())).c_str(), "arial.ttf", position, dimensions, 0.0f, "HighScore");
	m_tTextureManager->AddTexture(m_tHighScoreText);
}

//Set up all the variables needed for the options screen.
void GameManager::SwitchToControlsScreen()
{
	//Add in the controls texture back to the manager.
	m_tTextureManager->AddTexture(m_tControlsTexture);

	//Set up and assign menu values.
	m_mCurrentMenu = new Menu("Assets/Empty.png", m_tTextureManager, "", "");
	m_cUseButton = new UseButtonCommand(m_mCurrentMenu, 0.25f);
	m_iInputManager->AssignEKeyCommand(m_cUseButton);

	//Set up command to return to menu.
	m_cStartGameCommand = new ChangeStateCommand(m_cCityManager, m_gGameState, MAIN_MENU);
	m_mCurrentMenu->CreateNewButton(m_cStartGameCommand, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), "Assets/Empty.png");

	
	//Assign return to menu command to button "E".
	m_iInputManager->AssignEKeyCommand(m_cUseButton);
}

//Set up all the variables needed for the game over state.
void GameManager::SwitchToGameOver()
{
	//Create an explosion at the center of the screen.
	if (m_eExplosionManager)
	{
		m_eExplosionManager->CreateExplosion(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2), 10000.0f);
	}

	//Set Up Game Over Text.
	Vector2 dimensions = Vector2(1000.0f, 200.0f);
	Vector2 position = Vector2((Graphics::SCREEN_WIDTH / 2) - (dimensions.x / 2), (Graphics::SCREEN_HEIGHT / 2) - (dimensions.y / 2));
	m_tGameOverText = new Texture(std::string("Game Over, the main menu will load shortly.").c_str(), "arial.ttf", position, dimensions, 0.0f, "RoundOver");
	m_tTextureManager->AddTexture(m_tGameOverText);

	//Start timer.
	m_fTimer = 0.0f;
}

//Set up all the variables needed for the game state.
void GameManager::SwitchToGame()
{
	//Create the bomb spawner.
	m_bBombSpawner = new BombSpawner(m_pPlayerManager, m_gGameState, m_eExplosionManager, m_tTextureManager, Vector2(0.0f, 9.81f), "Assets/Bomb.png", m_iBombsToSpawn);
	m_iBombsToSpawn += 2; //Increment this so that when the game state is loaded next from the game state (aka next round) there should be more bombs to spawn with a maxmimum number of bombs of 100 (aka so it doesn't go above ammo).
	m_iRound += 1;
	m_pPlayerManager->SetRoundCount(m_iRound);
	m_iBombsToSpawn = ClampInt(m_iBombsToSpawn, 0, 100);


	//Create the cannon.
	m_gAntiAirCannon = new AntiAirCannon(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT), Vector2(50.0f, 50.0f), 0.0f, 30.0f, 1000.0f, true, nullptr, m_tTextureManager, m_pPlayerManager, m_eExplosionManager, "Assets/Cannon.png", "Assets/Crosshair.png");

	//Reset Player ammo.
	m_pPlayerManager->ResetAmmoCount();

	//Set up game commands.
	float rotation = 50.0f;
	float rangeChange = 170.0f;
	m_cAimLeftCommand = new AimCommand(m_gAntiAirCannon, -rotation);
	m_cAimRightCommand = new AimCommand(m_gAntiAirCannon, rotation);
	m_cIncreaseRangeCommand = new CannonRangeCommand(m_gAntiAirCannon, rangeChange);
	m_cDecreaseRangeCommand = new CannonRangeCommand(m_gAntiAirCannon, -rangeChange);
	m_cFireCommand = new FireCommand(m_gAntiAirCannon);

	//Assign commands to correct keys.
	m_iInputManager->AssignAKeyCommand(m_cAimLeftCommand);
	m_iInputManager->AssignDKeyCommand(m_cAimRightCommand);
	m_iInputManager->AssignSKeyCommand(m_cDecreaseRangeCommand);
	m_iInputManager->AssignWKeyCommand(m_cIncreaseRangeCommand);
	m_iInputManager->AssignEKeyCommand(m_cFireCommand);
	m_iInputManager->AssignSpaceKeyCommand(m_cFireCommand);

	//Set up the game text.
	SetUpGameText();
}

//Set up all the game text.
void GameManager::SetUpGameText()
{
	//Set Up Round Text.
	Vector2 dimensions = Vector2(100.0f, 20.0f);
	Vector2 position = Vector2(Graphics::SCREEN_WIDTH - 125.0f, 20.0f);
	m_tRoundText = new Texture(std::string("Round: ").append(std::to_string(m_iRound)).c_str(), "arial.ttf", position, dimensions, 0.0f, "Round");
	m_tTextureManager->AddTexture(m_tRoundText);

	//Set Up Score Multiplier Text.
	dimensions = Vector2(200.0f, 20.0f);
	position = Vector2(Graphics::SCREEN_WIDTH - 225.0f, 60.0f);
	m_tScoreMultiplierText = new Texture(std::string("Score Multiplier: ").append(std::to_string(m_pPlayerManager->GetScoreMultiplier())).c_str(), "arial.ttf", position, dimensions, 0.0f, "Multiplier");
	m_tTextureManager->AddTexture(m_tScoreMultiplierText);

	//Set Up Score Text.
	position = Vector2(20.0f, 20.0f);
	dimensions = Vector2(100.0f, 20.0f);
	m_tScoreText = new Texture(std::string("Score: ").append(std::to_string(m_pPlayerManager->GetPlayerScore())).c_str(), "arial.ttf", position, dimensions, 0.0f, "Score");
	m_tTextureManager->AddTexture(m_tScoreText);

	//Set Up Cities Left Text.
	dimensions = Vector2(120.0f, 20.0f);
	position = Vector2(20.0f, 60.0f);
	m_tCitiesText = new Texture(std::string("Cities Left: ").append(std::to_string(m_pPlayerManager->GetCityCount())).c_str(), "arial.ttf", position, dimensions, 0.0f, "City");
	m_tTextureManager->AddTexture(m_tCitiesText);

	//Set Up Ammo Left Text.
	dimensions = Vector2(120.0f, 20.0f);
	position = Vector2(20.0f, 100.0f);
	m_tAmmoText = new Texture(std::string("Ammo: ").append(std::to_string(m_pPlayerManager->GetAmmoCount())).c_str(), "arial.ttf", position, dimensions, 0.0f, "Ammo");
	m_tTextureManager->AddTexture(m_tAmmoText);
}

//Update the game text.
void GameManager::UpdateText()
{
	Vector2 dimensions = Vector2(120.0f, 20.0f);
	Vector2 position = Vector2(20.0f, 60.0f);
	//Update the cities text if it has changed..
	bool cityTextChanged = std::string(std::string("Cities Left: ").append(std::to_string(m_pPlayerManager->GetCityCount())).c_str()) != m_tCitiesText->GetTexturePath();
	if (cityTextChanged)
	{
		m_tCitiesText->SetText(std::string("Cities Left: ").append(std::to_string(m_pPlayerManager->GetCityCount())).c_str(), "arial.ttf", position, dimensions, 0.0f, "City");
	}

	//Update Ammo Text.
	dimensions = Vector2(120.0f, 20.0f);
	position = Vector2(20.0f, 100.0f);
	bool ammoTextChanged = std::string(std::string("Ammo: ").append(std::to_string(m_pPlayerManager->GetAmmoCount())).c_str()) != m_tAmmoText->GetTexturePath();
	if (ammoTextChanged)
	{
		m_tAmmoText->SetText(std::string("Ammo: ").append(std::to_string(m_pPlayerManager->GetAmmoCount())).c_str(), "arial.ttf", position, dimensions, 0.0f, "Ammo");
	}
}

//Deletes all the game variables so that the next state can be set up without trouble.
void GameManager::ResetGameVariables()
{
	//Variables to reset.
	//Input Classes.
	delete m_cAimLeftCommand;
	m_cAimLeftCommand = nullptr;
	delete m_cAimRightCommand;
	m_cAimRightCommand = nullptr;
	delete m_cFireCommand;
	m_cFireCommand = nullptr;
	delete m_cIncreaseRangeCommand;
	m_cIncreaseRangeCommand = nullptr;
	delete m_cDecreaseRangeCommand;
	m_cDecreaseRangeCommand = nullptr;
	delete m_cIncrementMenuIndex;
	m_cIncrementMenuIndex = nullptr;
	delete m_cDecrementMenuIndex;
	m_cDecrementMenuIndex = nullptr;
	delete m_cUseButton;
	m_cUseButton = nullptr;

	//Menu Variables.
	delete m_mCurrentMenu;
	m_mCurrentMenu = nullptr;

	//Game object variables.
	delete m_gAntiAirCannon;
	m_gAntiAirCannon = nullptr;

	//Clear Textures.
	m_tTextureManager->ClearTextureList();

	//Set all keys to nullptr.
	m_iInputManager->SetAllKeysToNullptr();

	//Reset explosion manager.
	if (m_eExplosionManager)
	{
		m_eExplosionManager->ReAddExploadablesToTextureManager();
		m_eExplosionManager->ClearExplosionList();
		m_eExplosionManager->ClearBombList();
	}

	//Reset Bomb Spawner.
	if (m_bBombSpawner)
	{
		delete m_bBombSpawner;
		m_bBombSpawner = nullptr;
	}

	//Reset Game Text.
	delete m_tScoreText;
	m_tScoreText = nullptr;
	delete m_tCitiesText;
	m_tCitiesText = nullptr;
	delete m_tAmmoText;
	m_tAmmoText = nullptr;
	delete m_tGameOverText;
	m_tGameOverText = nullptr;
	delete m_tHighScoreText;
	m_tHighScoreText = nullptr;
	delete m_tScoreMultiplierText;
	m_tScoreMultiplierText = nullptr;
	delete m_tRoundText;
	m_tRoundText = nullptr;
}