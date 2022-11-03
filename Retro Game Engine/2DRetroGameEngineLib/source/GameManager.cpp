#include "..\include\GameManager.h"
#include "Graphics.h"
#include "Timer.h"
#include "GameObject.h"
#include "Texture.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Button.h"
#include "Menu.h"
#include "GameState.h"
#include <SDL_events.h>

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

	//Input Classes.

	//Spawner Pointers.

	//Timer float.
	m_fTimer = 0.0f;

	//Controls screen texture.
	std::string sPath = SDL_GetBasePath();
	RTMATH::Vector2 position = RTMATH::Vector2(0.0f, 0.0f);
	RTMATH::Vector2 dimensions = RTMATH::Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);

}

//Destructor.
GameManager::~GameManager()
{
	Graphics::Release();
	m_gGraphics = NULL;

	delete m_tTextureManager;
	m_tTextureManager = NULL;
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
