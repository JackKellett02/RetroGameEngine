///////////////////////////////////////////////////////////////////////////////////////////////////////
// File:            Button.h
// Author:          Jack Kellett
// Date Created:    02/05/2020
// Brief:           This is a class that will run a command when it is selected and the user presses e.
///////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <vector>
#include "MathUtility.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Command.h"

class Button
{
private:
	//Button Command
	Command* m_cCommand;

	//Variable Declarations.
	RTMATH::Vector2 m_v2UnmodifiedPos;
	RTMATH::Vector2 m_v2Pos;
	RTMATH::Vector2 m_v2Dimensions;
	bool m_bIsSelected;

	//Button Texture.
	Texture* m_tTexture;
	Texture* m_tTextTexture;

	//Texture Manager
	TextureManager* m_tTextureManager;

	//Private Functions.

public:
	//Public Access Functions.
	//Constructor/Destructor.
	Button();
	Button(float a_fX, float a_fY, float a_fWidth, float a_fHeight, Texture* a_tTexture, Texture* a_tTextTexture, TextureManager* a_tTextureManager, Command* a_cCommand);
	Button(RTMATH::Vector2 a_v2Pos, RTMATH::Vector2 a_v2Dimensions, Texture* a_tTexture, Texture* a_tTextTexture, TextureManager* a_tTextureManager, Command* a_cCommand);
	~Button();

	//Getters.
	RTMATH::Vector2 GetUnmodifiedPos();
	RTMATH::Vector2 GetPos();
	RTMATH::Vector2 GetDimensions();
	bool GetSelectionState();

	//Setters
	void SetSelectionState(bool a_bSelectionState);

	//Other Methods.
	void Update();
	void RunCommand();
	void RemoveButtonTextureFromManager();
};
#endif // !_BUTTON_H_
