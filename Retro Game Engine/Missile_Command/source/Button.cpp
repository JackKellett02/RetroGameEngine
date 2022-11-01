#include "Button.h"

//Default Constructor.
Button::Button()
{
	m_v2UnmodifiedPos = Vector2();
	m_v2Pos = Vector2();
	m_v2Dimensions = Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);
	m_bIsSelected = false;
	m_tTexture = nullptr;
	m_tTextTexture = nullptr;
	m_tTextureManager = nullptr;
	m_cCommand = nullptr;
}

//Constructor with floats.
Button::Button(float a_fX, float a_fY, float a_fWidth, float a_fHeight, Texture* a_tTexture, Texture* a_tTextTexture, TextureManager* a_tTextureManager, Command* a_cCommand)
{
	m_v2UnmodifiedPos = Vector2(a_fX, a_fY);
	m_v2Pos = Vector2(a_fX - a_fWidth / 2, a_fY - a_fHeight / 2);
	m_v2Dimensions = Vector2(a_fWidth, a_fHeight);
	m_bIsSelected = false;
	m_tTexture = a_tTexture;
	m_tTextTexture = a_tTextTexture;
	m_tTextureManager = a_tTextureManager;
	m_tTextureManager->AddTexture(m_tTexture);
	m_tTextureManager->AddTexture(m_tTextTexture);
	m_cCommand = a_cCommand;
}

//Constructor with Vector 2's.
Button::Button(Vector2 a_v2Pos, Vector2 a_v2Dimensions, Texture* a_tTexture, Texture* a_tTextTexture, TextureManager* a_tTextureManager, Command* a_cCommand)
{
	m_v2UnmodifiedPos = a_v2Pos;
	m_v2Pos = Vector2(a_v2Pos.x - a_v2Dimensions.x / 2, a_v2Pos.y - a_v2Dimensions.y / 2);
	m_v2Dimensions = a_v2Dimensions;
	m_bIsSelected = false;
	m_tTexture = a_tTexture;
	m_tTextTexture = a_tTextTexture;
	m_tTextureManager = a_tTextureManager;
	m_tTextureManager->AddTexture(m_tTexture);
	m_tTextureManager->AddTexture(m_tTextTexture);
	m_cCommand = a_cCommand;
}

//Destructor.
Button::~Button()
{
	delete m_cCommand;
	m_cCommand = nullptr;

	delete m_tTexture;
	m_tTexture = nullptr;

	m_tTextureManager = nullptr;
}

//Get the unmodified position of the button (pos is modified when scaled.)
Vector2 Button::GetUnmodifiedPos()
{
	return m_v2UnmodifiedPos;
}

//Getters.
//Get the position of the button.
Vector2 Button::GetPos()
{
	return m_v2Pos;
}

//Get the current dimensions of the button.
Vector2 Button::GetDimensions()
{
	return m_v2Dimensions;
}

//Get whether or not the button is currently selected.
bool Button::GetSelectionState()
{
	return m_bIsSelected;
}

//Setters.
//Set whether or not the button is currently selected.
void Button::SetSelectionState(bool a_bSelectionState)
{
	m_bIsSelected = a_bSelectionState;
}

//Other Methods.
//Update the scale and position of the button based on whether or not it's currently selected.
void Button::Update()
{
	Vector2 modifiedDimensions = m_v2Dimensions;
	Vector2 modifiedPos = m_v2Pos;
	if (m_bIsSelected)
	{
		modifiedDimensions = modifiedDimensions * 1.5;
		modifiedPos = modifiedPos - (m_v2Dimensions / 4);
	}
	else
	{
		modifiedDimensions = modifiedDimensions;
	}
	m_tTexture->SetPos(modifiedPos);
	m_tTexture->SetDimensions(modifiedDimensions);
}

//Run the command stored inside this button.
void Button::RunCommand()
{
	if (m_cCommand)
	{
		m_cCommand->Execute();
	}
}

void Button::RemoveButtonTextureFromManager()
{
	m_tTextureManager->RemoveTexture(m_tTexture);
}