/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:             Menu.h
// Author:           Jack Kellett
// Date Created:     02/05/2021
// Brief:            Class to contain all the buttons on the menu and to track which button is currently selected.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _MENU_H_
#define _MENU_H_
#include <vector>
#include "Button.h"
#include "MathUtility.h"

class Menu
{
private:
	//Variable Declarations.
	int m_iIndex;
	std::vector<Button*> m_bButtonList;
	bool m_bIsOn;

	//Button Basic Texture.
	std::string m_sTexturePath;

	//Title Texture.
	Texture* m_tTitleTexture;
	Texture* m_tBackgroundTexture;

	//Texture Manager.
	TextureManager* m_tTextureManager;

	//Private Functions.

public:
	//Public Access Functions.
	//Constructor/Destructor.
	Menu(std::string a_sTexturePath, TextureManager* a_tTextureManager, std::string a_sTitlePath, std::string a_sBackgroundPath);
	~Menu();

	//Modify Button List.
	void CreateNewButton(Command* a_cCommand, float a_fX, float a_fY, float a_fWidth, float a_fHeight, std::string a_tButtonTextPath);
	void CreateNewButton(Command* a_cCommand, Vector2 a_v2Pos, Vector2 a_v2Dimensions, std::string a_tButtonTextPath);

	//Increment / Decrement index.
	void ChangeIndexByInt(int a_iChange);

	//Update Methods.
	void Update();

	//Getters.
	int GetIndexPos();
	std::vector<Button*> GetButtonList();
	Button* GetButtonAtIndex(int a_iIndex);
	bool GetActivationState();

	//Turn off menu.
	void SwitchMenuActivationState(bool a_bActivationState);
};

#endif // !_MENU_H_