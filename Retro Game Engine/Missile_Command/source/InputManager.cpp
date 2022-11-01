#include "..\include\InputManager.h"

//Default constructor.
InputManager::InputManager()
{
	m_kWPressed = false;
	m_kAPressed = false;
	m_kSPressed = false;
	m_kDPressed = false;
	m_kEPressed = false;
	SetAllKeysToNullptr();
}

//Destructor.
InputManager::~InputManager()
{
	//Nothing newed so nothing deleted.
}

//Whilst a key is pressed execute it's function.
void InputManager::Update()
{
	if (m_kKeyW && m_kWPressed)
	{
		m_kKeyW->Execute();
	}

	if (m_kKeyA && m_kAPressed)
	{
		m_kKeyA->Execute();
	}

	if (m_kKeyS && m_kSPressed)
	{
		m_kKeyS->Execute();
	}

	if (m_kKeyD && m_kDPressed)
	{
		m_kKeyD->Execute();
	}

	if (m_kKeyE && m_kEPressed)
	{
		m_kKeyE->Execute();
	}
	if (m_kKeySpace && m_kSpacePressed)
	{
		m_kKeySpace->Execute();
	}
}

//Update the keys pressed state to match what keys have been pressed.
void InputManager::HandleInput(SDL_Event& a_SDLEVENT)
{
	if (a_SDLEVENT.type == SDL_KEYDOWN)
	{
		switch (a_SDLEVENT.key.keysym.sym)
		{
			//I do "if(key)" as a null check to make sure the execute function isn't called when one of the keys is null.
			case SDLK_w:
			{
				m_kWPressed = true;
				break;
			}

			case SDLK_a:
			{
				m_kAPressed = true;
				break;
			}

			case SDLK_s:
			{
				m_kSPressed = true;
				break;
			}

			case SDLK_d:
			{
				m_kDPressed = true;
				break;
			}

			case SDLK_e:
			{
				m_kEPressed = true;
				break;
			}
			case SDLK_SPACE:
			{
				m_kSpacePressed = true;
				break;
			}

			default:
			{
				break;
			}
		}
	}

	if (a_SDLEVENT.type == SDL_KEYUP)
	{
		switch (a_SDLEVENT.key.keysym.sym)
		{
			case SDLK_w:
			{
				m_kWPressed = false;
				break;
			}

			case SDLK_a:
			{
				m_kAPressed = false;
				break;
			}

			case SDLK_s:
			{
				m_kSPressed = false;
				break;
			}

			case SDLK_d:
			{
				m_kDPressed = false;
				break;
			}

			case SDLK_e:
			{
				m_kEPressed = false;
				break;
			}
			case SDLK_SPACE:
			{
				m_kSpacePressed = false;
				break;
			}

			default:
			{
				break;
			}
		}
	}
}

//Sets the command for all the keys to nullptr to signify that the key shouldn't run any command at that time.
void InputManager::SetAllKeysToNullptr()
{
	AssignAKeyCommand(nullptr);
	AssignDKeyCommand(nullptr);
	AssignEKeyCommand(nullptr);
	AssignSKeyCommand(nullptr);
	AssignWKeyCommand(nullptr);
	AssignSpaceKeyCommand(nullptr);
}

void InputManager::AssignAKeyCommand(Command* a_cCommand)
{
	m_kKeyA = a_cCommand;
}

void InputManager::AssignDKeyCommand(Command* a_cCommand)
{
	m_kKeyD = a_cCommand;
}

void InputManager::AssignWKeyCommand(Command* a_cCommand)
{
	m_kKeyW = a_cCommand;
}

void InputManager::AssignSKeyCommand(Command* a_cCommand)
{
	m_kKeyS = a_cCommand;
}

void InputManager::AssignEKeyCommand(Command* a_cCommand)
{
	m_kKeyE = a_cCommand;
}

void InputManager::AssignSpaceKeyCommand(Command* a_cCommand)
{
	m_kKeySpace = a_cCommand;
}