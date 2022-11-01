#include "..\include\Explosion.h"

//Default Constructor.
Explosion::Explosion()
{
	//Set up game object parameters.
	m_gExplosionObject = new GameObject();
	m_v2ActualExplosionPos = Vector2();
	m_fTimeTillDestruction = 0.0f;
	m_fExplosionRadius = 0.0f;
	m_bDestroyThis = false;
}

//Copy Constructor.
Explosion::Explosion(Explosion* a_gExplosion)
{
	m_gExplosionObject = new GameObject(a_gExplosion->m_gExplosionObject->GetPos(), a_gExplosion->m_gExplosionObject->GetDimensions(), a_gExplosion->m_gExplosionObject->GetRotation(), a_gExplosion->m_gExplosionObject->GetActiveState(), a_gExplosion->m_gExplosionObject->GetParentPtr(), a_gExplosion->m_gExplosionObject->GetTextureManager(), a_gExplosion->m_gExplosionObject->GetTexturePtr()->GetTexturePath());
	m_gExplosionObject->SetTag("Explosion");
	m_fTimeTillDestruction = 0.0f;
	m_fExplosionRadius = a_gExplosion->GetExplosionRadius();
	m_bDestroyThis = false;
	m_v2ActualExplosionPos = a_gExplosion->m_gExplosionObject->GetPos();
}

//Constructor with vectors.
Explosion::Explosion(Vector2 a_v2Pos, Vector2 a_v2Dimensions, float a_fRotation, bool a_bActiveState, GameObject* a_oParent, TextureManager* a_tTextureManager, std::string TexturePath, float a_fExplosionRadius)
{
	//Set up gameobject parameters.
	Vector2 correctedPos = Vector2(a_v2Pos.x - (a_v2Dimensions.x / 2), a_v2Pos.y - (a_v2Dimensions.y / 2));
	m_gExplosionObject = new GameObject(correctedPos, a_v2Dimensions, a_fRotation, a_bActiveState, a_oParent, a_tTextureManager, TexturePath);
	m_gExplosionObject->SetTag("Explosion");
	m_fTimeTillDestruction = 0.0f;
	m_fExplosionRadius = a_fExplosionRadius;
	m_bDestroyThis = false;
	m_v2ActualExplosionPos = a_v2Pos;
}

//Constructor with floats.
Explosion::Explosion(float a_fX, float a_fY, float a_fWidth, float a_fHeight, float a_fRotation, bool a_bActiveState, GameObject* a_oParent, TextureManager* a_tTextureManager, std::string TexturePath, float a_fExplosionRadius)
{
	//Set up game object parameters.
	m_gExplosionObject = new GameObject(a_fX - (a_fWidth / 2), a_fY - (a_fY / 2), a_fWidth, a_fHeight, a_fRotation, a_bActiveState, a_oParent, a_tTextureManager, TexturePath);
	m_gExplosionObject->SetTag("Explosion");
	m_fTimeTillDestruction = 0.0f;
	m_fExplosionRadius = a_fExplosionRadius;
	m_bDestroyThis = false;
	m_v2ActualExplosionPos = Vector2(a_fX, a_fY);
}

//Destructor.
Explosion::~Explosion()
{
	if (m_gExplosionObject)
	{
		delete m_gExplosionObject;
		m_gExplosionObject = nullptr;
	}
}

//Update the explosion size and whether or not it's finished.
void Explosion::Update(TextureManager* textureManager, float a_fDeltaTime)
{
	if (m_gExplosionObject)
	{
		//Increment Timer.
		m_fTimeTillDestruction += a_fDeltaTime;

		//Update the base game object.
		m_gExplosionObject->Update(a_fDeltaTime);
		Vector2 dimensionChange = m_gExplosionObject->GetDimensions();
		dimensionChange.Normalize();
		dimensionChange = dimensionChange * a_fDeltaTime * 150.0f;
		m_gExplosionObject->TransformDimensions(dimensionChange);

		//Modify the position of the object so that the center is on the position.
		Vector2 modifiedPos = m_v2ActualExplosionPos - m_gExplosionObject->GetDimensions() / 2;
		m_gExplosionObject->SetPos(modifiedPos);

		//Check if the explosion is over.
		if ((m_gExplosionObject->GetDimensions().x / 2) >= m_fExplosionRadius)
		{
			//Destroy the explosion object.
			m_bDestroyThis = true;
		}

	}
}

//Get the max radius of the explosion.
float Explosion::GetExplosionRadius()
{
	return m_fExplosionRadius;
}

//Get the destruction state of the explosion.
bool Explosion::GetDestructionState()
{
	return m_bDestroyThis;
}

//Get the position of the explosion.
Vector2 Explosion::GetPosition()
{
	return m_gExplosionObject->GetPos();
}