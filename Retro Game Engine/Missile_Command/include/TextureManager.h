///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:           TextureManager.h
// Author:         Jack Kellett
// Date Created:   05/04/2021
// Brief:          This is a class to add textures to that need to be displayed so that only one render function needs to be called in GameManager.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "Texture.h"
#include <vector>

class TextureManager
{
private:
	std::vector<Texture*> textureList;
	Texture* m_tTextureBG;

public:
	TextureManager();
	~TextureManager();

	void AddTexture(Texture* a_tTexture);
	bool CheckForTexture(Texture* a_tTexture);
	void RemoveTextureFromEnd();
	void DisplayTextures();
	void RemoveTexture(Texture* a_tTexture);
	void ClearTextureList();
	bool MoveTextureToEndOfList(Texture* a_tTexture);
	std::vector<Texture*> GetTextureList();
};

#endif // !_TEXTUREMANAGER_H_