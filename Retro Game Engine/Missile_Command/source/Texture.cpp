#include "..\include\Texture.h"

//Image Constructor.
Texture::Texture(std::string a_sPath, Vector2& a_vPos, Vector2& a_v2Dimensions, float a_fRot)
{
	m_gGraphics = Graphics::Instance();

	m_v2Pos = a_vPos;
	m_v2Dimension = a_v2Dimensions;
	m_fRotation = a_fRot;

	m_tTexture = m_gGraphics->LoadTexture(a_sPath);
	m_sTexturePath = a_sPath;
	m_sTag = "";

	inTextureManager = false;
}

//Text Constructor.
Texture::Texture(const char* a_tText, const char* font, Vector2& a_v2Pos, Vector2 a_v2Dimensions, float a_fRot, std::string a_sTag)
{
	m_sTag = a_sTag;
	m_gGraphics = Graphics::Instance();
	m_v2Pos = a_v2Pos;
	m_v2Dimension = a_v2Dimensions;
	m_fRotation = a_fRot;
	m_sTexturePath = std::string(a_tText);

	m_tTexture = m_gGraphics->LoadText(a_tText, font);
}

//Destructor.
Texture::~Texture()
{
	SDL_DestroyTexture(m_tTexture);
	m_tTexture = NULL;
	m_gGraphics = NULL;
}

//Render the texture image.
void Texture::Render()
{
	m_gGraphics->DrawTexture(m_tTexture, m_v2Pos, m_v2Dimension.x, m_v2Dimension.y, m_fRotation);
}

/// <summary>
/// This function and the boolean it inverts allows me to check if a texture is in the texture manager or not
/// without having to check through every single texture in the texture manager as when a texture is added this is
/// inverted to true and when it is removed this is inverted to false.
/// </summary>
void Texture::InvertInTextureManager()
{
	inTextureManager = !inTextureManager;
}

//Get whether or not the texture has been added to the texture manager.
bool Texture::GetInTextureManager()
{
	return inTextureManager;
}

std::string Texture::GetTexturePath()
{
	return m_sTexturePath;
}

std::string Texture::GetTag()
{
	return m_sTag;
}

//Make the image text.
void Texture::SetText(const char* a_tText, const char* font, Vector2& a_v2Pos, Vector2 a_v2Dimensions, float a_fRot, std::string a_sTag)
{
	m_sTag = a_sTag;
	m_gGraphics = Graphics::Instance();
	m_v2Pos = a_v2Pos;
	m_v2Dimension = a_v2Dimensions;
	m_fRotation = a_fRot;
	m_sTexturePath = std::string(a_tText);

	m_tTexture = m_gGraphics->LoadText(a_tText, font);
}

void Texture::SetPos(Vector2& a_v2Pos)
{
	m_v2Pos = a_v2Pos;
}

void Texture::SetDimensions(Vector2& a_v2Dimensions)
{
	m_v2Dimension = a_v2Dimensions;
}

void Texture::SetRotation(float a_fRotation)
{
	m_fRotation = a_fRotation;
}

void Texture::SetTexturePath(std::string texturePath)
{
	m_tTexture = m_gGraphics->LoadTexture(texturePath);
}

void Texture::SetTag(std::string a_sTag)
{
	m_sTag = a_sTag;
}