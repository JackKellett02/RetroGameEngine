#include "Menu.h"

//Public Access Functions
//Constructor / Destructor.
Menu::Menu(std::string a_sTexturePath, TextureManager* a_tTextureManager, std::string a_sTitlePath, std::string a_sBackgroundPath)
{
	m_iIndex = 0;
	m_bIsOn = true;
	m_sTexturePath = a_sTexturePath;
	m_tTextureManager = a_tTextureManager;

	//Title Texture.
	std::string sPath = SDL_GetBasePath();
	Vector2 position = Vector2((Graphics::SCREEN_WIDTH / 2) - 350, 0.0f);
	Vector2 dimensions = Vector2(350, 100) * 2;
	if (a_sTitlePath == "")
	{
		m_tTitleTexture = nullptr;
	}
	else
	{
		m_tTitleTexture = new Texture(sPath.append(a_sTitlePath), position, dimensions, 0.0f);
		m_tTextureManager->AddTexture(m_tTitleTexture);
	}

	//Menu Texture;
	sPath = SDL_GetBasePath();
	sPath.append(a_sBackgroundPath);
	position = Vector2(0.0f, 0.0f);
	dimensions = Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);
	if (a_sBackgroundPath != "")
	{
		m_tBackgroundTexture = new Texture(sPath, position, dimensions, 0.0f);
		m_tTextureManager->AddTexture(m_tBackgroundTexture);
	}
}

Menu::~Menu()
{
	if (!m_bButtonList.empty())
	{
		m_bButtonList.clear();
	}
	if (m_tTextureManager)
	{
		m_tTextureManager = nullptr;
	}
	if (m_tTitleTexture)
	{
		delete m_tTitleTexture;
		m_tTitleTexture = nullptr;
	}
	if (m_tBackgroundTexture)
	{
		delete m_tBackgroundTexture;
		m_tBackgroundTexture = nullptr;
	}
}

//Create a new button with width and high at position (x,y).
void Menu::CreateNewButton(Command* a_cCommand, float a_fX, float a_fY, float a_fWidth, float a_fHeight, std::string a_tButtonTextPath)
{
	//Position and dimensions.
	Vector2 position = Vector2(a_fX - (a_fWidth / 2), a_fY - (a_fHeight / 2));
	Vector2 dimensions = Vector2(a_fWidth, a_fHeight);

	//Texture.
	std::string sPath = SDL_GetBasePath();
	Texture* newTexture = new Texture(sPath.append(m_sTexturePath), position, dimensions, 0.0f);

	//Text Texture.
	sPath = SDL_GetBasePath();
	Texture* textTexture = new Texture(sPath.append(a_tButtonTextPath), position, dimensions, 0.0f);

	//Push button to list.
	m_bButtonList.push_back(new Button(position, dimensions, newTexture, textTexture, m_tTextureManager, a_cCommand));
}

//Modify Button List.
//Create a new button with width and high at position (x,y).
void Menu::CreateNewButton(Command* a_cCommand, Vector2 a_v2Pos, Vector2 a_v2Dimensions, std::string a_tButtonTextPath)
{
	//Position and dimensions
	Vector2 texturePos = a_v2Pos - (a_v2Dimensions / 2);

	//Texture.
	std::string sPath = SDL_GetBasePath();
	Texture* newTexture = new Texture(sPath.append(m_sTexturePath), texturePos, a_v2Dimensions, 0.0f);

	//Text Texture.
	sPath = SDL_GetBasePath();
	Texture* textTexture = new Texture(sPath.append(a_tButtonTextPath), texturePos, a_v2Dimensions, 0.0f);

	//Push button to list.
	m_bButtonList.push_back(new Button(a_v2Pos, a_v2Dimensions, newTexture, textTexture, m_tTextureManager, a_cCommand));
}

//Increment / Decrement Counter.
//Increment button list index by int a_iChange
void Menu::ChangeIndexByInt(int a_iChange)
{
	m_iIndex += a_iChange;
	m_iIndex = ClampInt(m_iIndex, 0, m_bButtonList.size() - 1);
}

//Update Methods
//Update selection state of the menu and update the menu buttons.
void Menu::Update()
{
	if (!m_bButtonList.empty())
	{
		for (int i = 0; i < m_bButtonList.size(); i++)
		{
			if (i == m_iIndex)
			{
				m_bButtonList[i]->SetSelectionState(true);
			}
			else
			{
				m_bButtonList[i]->SetSelectionState(false);
			}
			m_bButtonList[i]->Update();
		}
	}
}

//Getters.
//Gets the current index the menu is on.
int Menu::GetIndexPos()
{
	return m_iIndex;
}

//Get the menu's button list.
std::vector<Button*> Menu::GetButtonList()
{
	return m_bButtonList;
}

//Get a button in the button list at index a_iIndex.
Button* Menu::GetButtonAtIndex(int a_iIndex)
{
	if (!m_bButtonList.empty())
	{
		return m_bButtonList[a_iIndex];
	}
	else
	{
		return nullptr;
	}
}

//Get the activation state of the menu.
bool Menu::GetActivationState()
{
	return m_bIsOn;
}

//Set the activation state of the menu.
void Menu::SwitchMenuActivationState(bool a_bActivationState)
{
	m_bIsOn = a_bActivationState;
}