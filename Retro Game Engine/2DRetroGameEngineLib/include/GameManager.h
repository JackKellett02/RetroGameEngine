#ifndef _GAMEMANAGE_H_
#define _GAMEMANAGE_H_

//Includes.

//Forward Declarations.
class Timer;
class Graphics;
class GameState;
class Texture;
class TextureManager;
class InputManager;
class Command;
class GameObject;
class SDL_Event;


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

	//Input Classes
	Command* command;

	//Game Objects.
	GameObject* object;

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

};

#endif // !_GAMEMANAGE_H_
