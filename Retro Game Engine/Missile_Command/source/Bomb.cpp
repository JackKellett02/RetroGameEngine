#include "..\include\Bomb.h"

//Constructor with values.
Bomb::Bomb(GameState* a_gGameState, TextureManager* a_tTextureManager, Vector2 a_v2Accelleration, std::string a_sTexturePath)
{
	//Set texture path.
	m_sTexturePath = a_sTexturePath;

	//Explode?
	m_bExplode = false;

	//Set Up Movement Variables.
	m_v2Position = Vector2();
	m_v2Velocity = Vector2(0.0f, 50.0f);
	m_v2Accelleration = a_v2Accelleration;

	//Assign Manager Variables.
	m_gGameState = a_gGameState;

	//Set up bomb gameobject.
	m_gBomb = new GameObject(m_v2Position - Vector2(5.0f, 12.5f), Vector2(10.0f, 25.0f), 0.0f, false, this, a_tTextureManager, a_sTexturePath);
	m_gBomb->SetTag("Bomb");
}

//Copy Constructor.
Bomb::Bomb(Bomb* a_bBombPrototype)
{
	//Set texture path.
	m_sTexturePath = a_bBombPrototype->GetTexturePath();

	//Explode?
	m_bExplode = false;

	//Set up movement variables.
	m_v2Position = a_bBombPrototype->GetPosition();
	m_v2Velocity = a_bBombPrototype->GetVelocity();
	m_v2Accelleration = a_bBombPrototype->GetAcceleration();

	//Assign manager variables.
	m_gGameState = a_bBombPrototype->GetGameStatePtr();

	//Set up bomb gameobject.
	Bomb* bomb = this;
	m_gBomb = new GameObject(a_bBombPrototype->GetBombGameObjectPtr()->GetPos(), a_bBombPrototype->GetBombGameObjectPtr()->GetDimensions(), a_bBombPrototype->GetBombGameObjectPtr()->GetRotation(), a_bBombPrototype->GetBombGameObjectPtr()->GetActiveState(), bomb, a_bBombPrototype->GetBombGameObjectPtr()->GetTextureManager(), a_bBombPrototype->GetTexturePath());
	m_gBomb->SetTag("Bomb");
}

//Destructor.
Bomb::~Bomb()
{
	m_gGameState = nullptr;

	if (m_gBomb)
	{
		delete m_gBomb;
		m_gBomb = nullptr;
	}
}

//Update the bomb's position and gameobject.
void Bomb::Update(float a_fDeltaTime)
{
	//Calculate Movement.
	Accelerate(a_fDeltaTime);
	Move(a_fDeltaTime);

	m_gBomb->Update(a_fDeltaTime);
}

//Accelerate the bomb's velocity.
void Bomb::Accelerate(float a_fDeltaTime)
{
	m_v2Velocity.x += m_v2Accelleration.x * a_fDeltaTime;
	m_v2Velocity.y += m_v2Accelleration.y * a_fDeltaTime;
}

//Move the bombs position.
void Bomb::Move(float a_fDeltaTime)
{
	m_v2Position.x += m_v2Velocity.x * a_fDeltaTime;
	m_v2Position.y += m_v2Velocity.y * a_fDeltaTime;

	//Adjust the position of the bomb based on the dimensions then set the pos.
	Vector2 adjustedPos = m_v2Position;
	Vector2 dimensions = m_gBomb->GetDimensions();
	adjustedPos = adjustedPos - (dimensions / 2);
	m_gBomb->SetPos(adjustedPos);
	SetPos(m_v2Position);
}

//Get the bomb's gameobject pointer.
GameObject* Bomb::GetBombGameObjectPtr()
{
	return m_gBomb;
}

//Get the game state manager's pointer.
GameState* Bomb::GetGameStatePtr()
{
	return m_gGameState;
}

//Get the position of the bomb.
Vector2 Bomb::GetPosition()
{
	return m_v2Position;
}

//Get the velocity of the bomb.
Vector2 Bomb::GetVelocity()
{
	return m_v2Velocity;
}

//Get the acceleration of the bomb.
Vector2 Bomb::GetAcceleration()
{
	return m_v2Accelleration;
}

//Get the current explode state of the bomb.
bool Bomb::GetExplodeState()
{
	return m_bExplode;
}

//Get the bomb's texture path.
std::string Bomb::GetTexturePath()
{
	return m_sTexturePath;
}

//Set the explode state of the bomb.
void Bomb::SetExplodeState(bool a_bExplode)
{
	m_bExplode = a_bExplode;
}

//Set the position of the bomb.
void Bomb::SetPosition(Vector2 a_v2Pos)
{
	m_v2Position = a_v2Pos;
}

//Create a new bomb from the current one.
Bomb* Bomb::Clone()
{
	return new Bomb(this);
}