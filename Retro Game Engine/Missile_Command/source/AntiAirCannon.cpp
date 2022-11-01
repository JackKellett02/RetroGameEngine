#include "..\include\AntiAirCannon.h"

//Default Constructor.
AntiAirCannon::AntiAirCannon()
{
	//Set up game object parameters.
	m_pPlayer = nullptr;
	m_tTextureManager = nullptr;
	m_eExplosionManager = nullptr;
	m_gCannonGameObject = new GameObject();
	m_tTargetTexture = nullptr;
	m_fCurrentFiringDistance = 20.0f;
	m_fMinFiringDistance = 0.0f;
	m_fMaxFiringDistance = 0.0f;
	m_fTimer = 0.0f;
	m_bUpdateTimer = false;
}

//Constructor with values.
AntiAirCannon::AntiAirCannon(Vector2 a_v2Pos, Vector2 a_v2Dimensions, float a_fRotation, float a_fMinFireDist, float a_fMaxFireDist, bool a_bActiveState, GameObject* a_oParent, TextureManager* a_tTextureManager, PlayerManager* a_pPlayer, ExplosionManager* a_eExplosionManager, std::string cannonTexturePath, std::string targetTexturePath)
{
	//Set up gameobject parameters.
	m_pPlayer = a_pPlayer;
	m_tTextureManager = a_tTextureManager;
	Vector2 correctedPos = Vector2(a_v2Pos.x - (a_v2Dimensions.x / 2), a_v2Pos.y - (a_v2Dimensions.y / 2));
	m_gCannonGameObject = new GameObject(correctedPos, a_v2Dimensions, a_fRotation, a_bActiveState, a_oParent, m_tTextureManager, cannonTexturePath);
	m_fCurrentFiringDistance = a_fMinFireDist;
	m_fMinFiringDistance = a_fMinFireDist;
	m_fMaxFiringDistance = a_fMaxFireDist;
	m_eExplosionManager = a_eExplosionManager;
	m_fTimer = 0.0f;
	m_bUpdateTimer = false;

	//Set up Texture for target.
	Vector2 textureDimensions = Vector2(25.0f, 25.0f);
	Vector2 texturePos = Vector2(a_v2Pos.x, a_v2Pos.y - (25.0f / 2));
	std::string sPath = SDL_GetBasePath();
	m_tTargetTexture = new Texture(sPath.append(targetTexturePath), texturePos, textureDimensions, 0.0f);
}

//Constructor with floats.
AntiAirCannon::AntiAirCannon(float a_fX, float a_fY, float a_fWidth, float a_fHeight, float a_fRotation, float a_fMinFireDist, float a_fMaxFireDist, bool a_bActiveState, GameObject* a_oParent, TextureManager* a_tTextureManager, PlayerManager* a_pPlayer, ExplosionManager* a_eExplosionManager, std::string cannonTexturePath, std::string targetTexturePath)
{
	//Set up game object parameters.
	m_pPlayer = a_pPlayer;
	m_tTextureManager = a_tTextureManager;
	m_gCannonGameObject = new GameObject(a_fX - (a_fWidth / 2), a_fY - (a_fY / 2), a_fWidth, a_fHeight, a_fRotation, a_bActiveState, a_oParent, m_tTextureManager, cannonTexturePath);
	m_fCurrentFiringDistance = a_fMinFireDist;
	m_fMinFiringDistance = a_fMinFireDist;
	m_fMaxFiringDistance = a_fMaxFireDist;
	m_eExplosionManager = a_eExplosionManager;
	m_fTimer = 0.0f;
	m_bUpdateTimer = false;

	//Set up Texture for target.
	Vector2 texturePosition = Vector2(a_fX, a_fY);
	Vector2 textureDimensions = Vector2(25.0f, 25.0f);
	std::string sPath = SDL_GetBasePath();
	m_tTargetTexture = new Texture(sPath.append(targetTexturePath), texturePosition, textureDimensions, 0.0f);
}

//Destructor.
AntiAirCannon::~AntiAirCannon()
{
	delete m_gCannonGameObject;
	m_gCannonGameObject = nullptr;

	delete m_tTargetTexture;
	m_tTargetTexture = nullptr;

	m_tTextureManager = nullptr;
}

//Update the state of the cannon.
void AntiAirCannon::Update(float a_fDeltaTime)
{
	if (m_bUpdateTimer)
	{
		//Update Delta Time.
		m_fTimer += a_fDeltaTime;
	}

	//Add texture to texture manager if it isn't already in it and if the object has access to the texture manager.
	if (m_tTextureManager)
	{
		if (!m_tTargetTexture->GetInTextureManager())
		{
			m_tTextureManager->AddTexture(m_tTargetTexture);
		}

		//Remove texture from textureManager if game object is not active.
		if (!m_gCannonGameObject->GetActiveState())
		{
			m_tTextureManager->RemoveTexture(m_tTargetTexture);
		}
		else
		{
			//If the game object is active.
			//Update the base gameobject
			m_gCannonGameObject->Update(a_fDeltaTime);

			//Calculate the direction of the cannon.
			m_vFiringVector = CalculateFiringVector();

			//Calculate the position the player is targetting.
			m_vTargetPosition = CalculateTargetPosition();

			//Clamp it to the screen.
			m_vTargetPosition.x = ClampFloat(m_vTargetPosition.x, 0.0f, Graphics::SCREEN_WIDTH - 25.0f);
			m_vTargetPosition.y = ClampFloat(m_vTargetPosition.y, 0.0f, Graphics::SCREEN_HEIGHT);

			//Set the position of the target texture to the target position.
			m_tTargetTexture->SetPos(m_vTargetPosition);
		}
	}
}

//Spawn an explosion at the position of the target.
void AntiAirCannon::Fire()
{
	if (m_fTimer >= 0.5f)
	{
		//Reset Timer.
		m_fTimer = 0.0f;
		m_bUpdateTimer = false;
	}

	//Fire or not fire gun.
	if (m_pPlayer->GetAmmoCount() > 0 && !m_bUpdateTimer)
	{
		m_bUpdateTimer = true;
		m_pPlayer->DecrementAmmo();
		Vector2 actualTargetPos = m_vTargetPosition + Vector2(12.5f, 12.5f);
		m_eExplosionManager->CreateExplosion(actualTargetPos);
	}
}

//Get the max distance the cannon can fire.
float AntiAirCannon::GetMaxFiringDistance()
{
	return m_fMaxFiringDistance;
}

//Get the minimum distance the cannon can fire.
float AntiAirCannon::GetMinFiringDistance()
{
	return m_fMinFiringDistance;
}

//Get the current distance the cannon will fire.
float AntiAirCannon::GetCurrentFiringDistance()
{
	return m_fCurrentFiringDistance;
}

//Set the position of the game object to the parameter vector 2.
void AntiAirCannon::SetPos(Vector2 a_v2Position)
{
	m_gCannonGameObject->SetPos(a_v2Position);
}

//Set the dimensions of the game object to the parameter vector 2.
void AntiAirCannon::SetDimensions(Vector2 a_v2Dimensions)
{
	m_gCannonGameObject->SetDimensions(a_v2Dimensions);
}

//Set the rotation to the parameter float.
void AntiAirCannon::SetRotation(float a_fRotation)
{
	m_gCannonGameObject->SetRotation(a_fRotation);
}

//Turn the cannon on or off.
void AntiAirCannon::SetActiveState(bool a_bActiveState)
{
	m_gCannonGameObject->SetActiveState(a_bActiveState);
}

//Tell the cannon what it's parent object is.
void AntiAirCannon::SetParent(GameObject* a_oParent)
{
	m_gCannonGameObject->SetParent(a_oParent);
}

//Tell the cannon where it's texture is located.
void AntiAirCannon::SetTexturePath(std::string texturePath)
{
	m_gCannonGameObject->SetTexturePath(texturePath);
}

//Move the cannon relative to it's current pos.
void AntiAirCannon::TranslatePos(float a_fMovementX, float a_fMovementY)
{
	m_gCannonGameObject->TranslatePos(a_fMovementX, a_fMovementY);
}

//Stretch the cannon relative to it's current dimensions.
void AntiAirCannon::TransformDimensions(float a_fWidthChange, float a_fHeightChange)
{
	m_gCannonGameObject->TransformDimensions(a_fWidthChange, a_fHeightChange);
}

//Rotate the cannon relative to it's current rotation.
void AntiAirCannon::TransformRotation(float a_fRotationChange)
{
	m_gCannonGameObject->TransformRotation(a_fRotationChange);
	m_gCannonGameObject->SetRotation(ClampFloat(m_gCannonGameObject->GetRotation(), -90.0f, 90.0f));
}

void AntiAirCannon::SetMaxFiringDistance(float a_fDistance)
{
	m_fMaxFiringDistance = a_fDistance;
}

void AntiAirCannon::SetMinFiringDistance(float a_fDistance)
{
	m_fMinFiringDistance = a_fDistance;
}

//Change the firing distance relative to the current firing distance.
void AntiAirCannon::TransformFiringDistance(float a_fDistance)
{
	m_fCurrentFiringDistance += a_fDistance;

	//Clamp it.
	if (m_fCurrentFiringDistance <= m_fMinFiringDistance)
	{
		m_fCurrentFiringDistance = m_fMinFiringDistance;
	}
	else if (m_fCurrentFiringDistance >= m_fMaxFiringDistance)
	{
		m_fCurrentFiringDistance = m_fMaxFiringDistance;
	}
	else
	{
		m_fCurrentFiringDistance = m_fCurrentFiringDistance;
	}
}

//Calculate the vector of the rotation of the cannon.
Vector2 AntiAirCannon::CalculateFiringVector()
{
	//Variable Declarations.
	Vector2 vectorToFireIn;
	float cannonRotation = m_gCannonGameObject->GetRotation();
	float xComponent;
	float yComponent;

	//Calculate Vector to fire in.
	if (cannonRotation < 0.0f)
	{
		cannonRotation = (-90.0f) - cannonRotation;
		cannonRotation = -cannonRotation;
		xComponent = -cosf(cannonRotation * DEG_TO_RAD);
		yComponent = sinf(cannonRotation * DEG_TO_RAD);
		vectorToFireIn = Vector2(xComponent, yComponent);
	}
	else
	{
		cannonRotation = 90 - cannonRotation;
		xComponent = cosf(cannonRotation * DEG_TO_RAD);
		yComponent = sinf(cannonRotation * DEG_TO_RAD);
		vectorToFireIn = Vector2(xComponent, yComponent);
	}

	//Make sure it's magnitude is 1.
	vectorToFireIn.Normalize();

	//Clamp y component to positive as that should only be ever facing up, or horizontal.
	vectorToFireIn.y = ClampFloat(vectorToFireIn.y, 0.0f, 1.0f);

	return vectorToFireIn;
}

//Calculate where the target point should be based on the firing distance and firing vector.
Vector2 AntiAirCannon::CalculateTargetPosition()
{
	//Make sure the y component is set to negative itself as sdl has y(0) at the top rather than the bottom.
	m_vFiringVector.y = -m_vFiringVector.y;

	//Multiply the vector to make it travel the firing distance in length.
	m_vFiringVector = m_vFiringVector * m_fCurrentFiringDistance;

	//Add the firing vector to the position then return it.
	Vector2 position = m_gCannonGameObject->GetPos();
	Vector2 cannonDimesions = m_gCannonGameObject->GetDimensions();
	cannonDimesions.x = cannonDimesions.x / 4;
	cannonDimesions.y = cannonDimesions.y / 4;
	return (position + m_vFiringVector + cannonDimesions);
}