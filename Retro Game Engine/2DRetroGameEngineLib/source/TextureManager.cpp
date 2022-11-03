#include "..\include\TextureManager.h"

//Default Constructor.
TextureManager::TextureManager()
{
	std::string sPath = SDL_GetBasePath();
	sPath.append("Assets/MissileCommandBG.png");
	Vector2 position = Vector2(0.0f, 0.0f);
	Vector2 dimensions = Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);
	m_tTextureBG = new Texture(sPath, position, dimensions, 0.0f);
}

//Destructor.
TextureManager::~TextureManager()
{
	if (!textureList.empty())
	{
		//Textures are deleted in their separate classes they are updated from so no need to delete them here.
		//Clear the list.
		textureList.clear();
	}

	if (m_tTextureBG)
	{
		delete m_tTextureBG;
		m_tTextureBG = nullptr;
	}
}

//Add a texture to the texture list.
void TextureManager::AddTexture(Texture* a_tTexture)
{
	if (a_tTexture != nullptr)
	{
		textureList.push_back(a_tTexture);
		a_tTexture->InvertInTextureManager();
	}
}

//Check to see if a texture is already in the list.
bool TextureManager::CheckForTexture(Texture* a_tTexture)
{
	for (int i = 0; i < textureList.size(); i++)
	{
		if (textureList[i] == a_tTexture)
		{
			return true;
		}
	}
	return false;
}

//Remove a texture from the end of the list.
void TextureManager::RemoveTextureFromEnd()
{
	textureList.pop_back();
}

//Render all textures.
void TextureManager::DisplayTextures()
{
	//Render background.
	m_tTextureBG->Render();

	//Render all textures in the texture list.
	for (int i = 0; i < textureList.size(); i++)
	{
		textureList[i]->Render();
	}
}

//Remove a texture from the list.
void TextureManager::RemoveTexture(Texture* a_tTexture)
{
	bool textureMovedToEnd = MoveTextureToEndOfList(a_tTexture);
	if (textureMovedToEnd)
	{
		RemoveTextureFromEnd();
		a_tTexture->InvertInTextureManager();
	}
}

//Move a texture to the end of the list.
bool TextureManager::MoveTextureToEndOfList(Texture* a_tTexture)
{
	//If the texture exists
	if (CheckForTexture(a_tTexture))
	{
		//Declare temporary variables.
		std::vector<Texture*> tempTextureList;

		//Add all textures from original list into new list in new order.
		for (int i = 0; i < textureList.size(); i++)
		{
			if (textureList[i] != a_tTexture)
			{
				tempTextureList.push_back(textureList[i]);
			}
		}

		//Push texture onto the end.
		tempTextureList.push_back(a_tTexture);

		//Set normal list to be new list.
		textureList = tempTextureList;

		//Return success.
		return true;
	}
	else
	{
		return false;
	}
}

//Get the texture list.
std::vector<Texture*> TextureManager::GetTextureList()
{
	return textureList;
}

//Clear the texture list.
void TextureManager::ClearTextureList()
{
	//Clear the list.
	textureList.clear();
}
