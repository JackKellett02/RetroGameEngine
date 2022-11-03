#include "..\include\GameObject.h"

//Constructors / Destructor.
GameObject::GameObject()
{
	m_tTextureManager = nullptr;
	m_v2Pos = Vector2();
	m_v2Dimensions = Vector2();
	m_fRotation = 0.0f;
	m_bActive = false;
	m_oParent = nullptr;
	m_sTag = "";
}

GameObject::GameObject(Vector2 a_v2Pos, Vector2 a_v2Dimensions, float a_fRotation, bool a_bActiveState, GameObject* a_oParent, TextureManager* a_tTextureManager, std::string texturePath)
{
	//Set the texture path.
	std::string sPath = SDL_GetBasePath();
	sPath.append(texturePath);

	//Set the other member variables
	m_tTextureManager = a_tTextureManager;
	m_v2Pos = a_v2Pos;
	m_v2Dimensions = a_v2Dimensions;
	m_fRotation = a_fRotation;
	m_bActive = a_bActiveState;
	m_oParent = a_oParent;
	m_tTexture = new Texture(sPath, m_v2Pos, m_v2Dimensions, m_fRotation);
	m_sTag = "";
	m_tTexture->SetTag(m_sTag);
}

GameObject::GameObject(float a_fX, float a_fY, float a_fWidth, float a_fHeight, float a_fRotation, bool a_bActiveState, GameObject* a_oParent, TextureManager* a_tTextureManager, std::string texturePath)
{
	//Set the texture path.
	std::string sPath = SDL_GetBasePath();
	sPath.append(texturePath);

	//Set the other member variables.
	m_tTextureManager = a_tTextureManager;
	m_v2Pos = Vector2(a_fX, a_fY);
	m_v2Dimensions = Vector2(a_fWidth, a_fHeight);
	m_fRotation = a_fRotation;
	m_bActive = a_bActiveState;
	m_oParent = a_oParent;
	m_tTexture = new Texture(sPath, m_v2Pos, m_v2Dimensions, m_fRotation);
	m_sTag = "";
}

GameObject::~GameObject()
{
	m_oParent = nullptr;

	if (m_tTexture)
	{
		m_tTextureManager->RemoveTexture(m_tTexture);
		delete m_tTexture;
		m_tTexture = NULL;
	}

	if (m_tTextureManager)
	{
		m_tTextureManager = nullptr;
	}
}

//Getters
Vector2 GameObject::GetPos()
{
	return m_v2Pos;
}

Vector2 GameObject::GetDimensions()
{
	return m_v2Dimensions;
}

float GameObject::GetRotation()
{
	return m_fRotation;
}

bool GameObject::GetActiveState()
{
	return m_bActive;
}

GameObject* GameObject::GetParentPtr()
{
	return m_oParent;
}

Texture* GameObject::GetTexturePtr()
{
	return m_tTexture;
}

TextureManager* GameObject::GetTextureManager()
{
	return m_tTextureManager;
}

std::string GameObject::GetTag()
{
	return m_sTag;
}

//Setters
void GameObject::SetPos(Vector2 a_v2Position)
{
	m_v2Pos = a_v2Position;
	if (m_tTexture)
	{
		m_tTexture->SetPos(m_v2Pos);
	}
}

void GameObject::SetDimensions(Vector2 a_v2Dimensions)
{
	m_v2Dimensions = a_v2Dimensions;
	if (m_tTexture)
	{
		m_tTexture->SetDimensions(m_v2Dimensions);
	}
}

void GameObject::SetRotation(float a_fRotation)
{
	m_fRotation = a_fRotation;
	if (m_tTexture)
	{
		m_tTexture->SetRotation(a_fRotation);
	}
}

void GameObject::SetActiveState(bool a_bActiveState)
{
	m_bActive = a_bActiveState;
}

void GameObject::SetParent(GameObject* a_oParent)
{
	m_oParent = a_oParent;
}

void GameObject::SetTexturePath(std::string texturePath)
{
	if (m_tTexture)
	{
		m_tTexture->SetTexturePath(texturePath);
	}
}

void GameObject::SetTag(std::string a_sTag)
{
	m_sTag = a_sTag;
	if (m_tTexture)
	{
		m_tTexture->SetTag(m_sTag);
	}
}

//Increase or decrease member variables by arguments.
//Change position relative to the current one.
void GameObject::TranslatePos(float a_fMovementX, float a_fMovementY)
{
	m_v2Pos.x += a_fMovementX;
	m_v2Pos.y -= a_fMovementY;
	if (m_tTexture)
	{
		m_tTexture->SetPos(m_v2Pos);
	}
}

//Change position relative to the current one.
void GameObject::TranslatePos(Vector2 a_v2Movement)
{
	m_v2Pos = m_v2Pos + a_v2Movement;
	if (m_tTexture)
	{
		m_tTexture->SetPos(m_v2Pos);
	}
}

//Change dimensions relative to the current dimensions.
void GameObject::TransformDimensions(Vector2 a_v2DimensionChange)
{
	m_v2Dimensions = m_v2Dimensions + a_v2DimensionChange;
	if (m_tTexture)
	{
		m_tTexture->SetDimensions(m_v2Dimensions);
	}
}

//Change dimensions relative to the current dimensions.
void GameObject::TransformDimensions(float a_fWidthChange, float a_fHeightChange)
{
	m_v2Dimensions.x += a_fWidthChange;
	m_v2Dimensions.y += a_fHeightChange;
	if (m_tTexture)
	{
		m_tTexture->SetDimensions(m_v2Dimensions);
	}
}

//Change rotation relative to the current rotation.
void GameObject::TransformRotation(float a_fRotationChange)
{
	m_fRotation += a_fRotationChange;
	if (m_tTexture)
	{
		m_tTexture->SetRotation(m_fRotation);
	}
}

//Other Methods
//Update the gameobject.
void GameObject::Update(float a_fDeltaTime)
{
	//Add texture to texture manager if it isn't already in it.
	if (m_tTexture && m_tTextureManager)
	{
		if (!m_tTexture->GetInTextureManager())
		{
			m_tTextureManager->AddTexture(m_tTexture);
		}

		//Remove texture from textureManager if game object is not active.
		if (!m_bActive)
		{
			m_tTextureManager->RemoveTexture(m_tTexture);
		}
	}

	//Update Delta TIme
	m_fDeltaTime = a_fDeltaTime;
}