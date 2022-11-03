///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:             Texture.h
// Author:           Dan M and myself for the text part.
// Date Created:     When the tutorials were created.
// Brief:            A class to display an image or text onto the screen.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "MathUtility.h"
#include "Graphics.h"

class Texture
{
private:
	SDL_Texture* m_tTexture;
	Graphics* m_gGraphics;

	std::string m_sTexturePath;
	std::string m_sTag;

	RTMATH::Vector2 m_v2Dimension;
	RTMATH::Vector2 m_v2Pos;

	float m_fRotation;

	bool inTextureManager;

public:
	//Constructor/Destructor.
	Texture(std::string a_sPath, RTMATH::Vector2& a_vPos, RTMATH::Vector2& a_v2Dimensions, float a_fRot);
	Texture(const char* a_tText, const char* font, RTMATH::Vector2& a_v2Pos, RTMATH::Vector2 a_v2Dimensions, float a_fRot, std::string a_sTag);
	~Texture();

	virtual void Render();
	void InvertInTextureManager();

	//Getters
	bool GetInTextureManager();
	std::string GetTexturePath();
	std::string GetTag();

	//Setters
	void SetText(const char* a_tText, const char* font, RTMATH::Vector2& a_v2Pos, RTMATH::Vector2 a_v2Dimensions, float a_fRot, std::string a_sTag);
	void SetPos(RTMATH::Vector2& a_v2Pos);
	void SetDimensions(RTMATH::Vector2& a_v2Dimensions);
	void SetRotation(float a_fRotation);
	void SetTexturePath(std::string texturePath);
	void SetTag(std::string a_sTag);
};
#endif // !_TEXTURE_H_
