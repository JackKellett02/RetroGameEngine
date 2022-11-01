#include "..\include\ExplosionManager.h"

//Constructor/Destructor.
ExplosionManager::ExplosionManager(TextureManager* a_tTextureManager, PlayerManager* a_pPlayerManager)
{
	m_pPlayerManager = a_pPlayerManager;
	m_tTextureManager = a_tTextureManager;
}

ExplosionManager::~ExplosionManager()
{
	for (int i = 0; i < m_gExploadableObjects.size(); i++)
	{
		delete m_gExploadableObjects[i];
	}
	m_gExploadableObjects.clear();

	for (int i = 0; i < m_eExplosions.size(); i++)
	{
		delete m_eExplosions[i];
	}
	m_eExplosions.clear();

	for (int i = 0; i < m_bBombsList.size(); i++)
	{
		delete m_bBombsList[i];
	}
	m_bBombsList.clear();
}

//General Functions.
//Update all the lists and check for collissions.
void ExplosionManager::Update(float a_fDeltaTime)
{
	//Update all the exploadables.
	for (int i = 0; i < m_gExploadableObjects.size(); i++)
	{
		if (m_gExploadableObjects[i])
		{
			m_gExploadableObjects[i]->Update(a_fDeltaTime);
		}
	}

	//Update all the bombs.
	for (int i = 0; i < m_bBombsList.size(); i++)
	{
		if (m_bBombsList[i])
		{
			//Check if bomb has hit ground.
			if (m_bBombsList[i]->GetPosition().y >= Graphics::SCREEN_HEIGHT - 25.0f)
			{
				m_bBombsList[i]->SetExplodeState(true);
			}

			//If not, update it.
			if (!m_bBombsList[i]->GetExplodeState())
			{
				m_bBombsList[i]->Update(a_fDeltaTime);
			}
			else if (m_bBombsList[i]->GetExplodeState())
			{
				//Else explode it.
				CreateExplosion(m_bBombsList[i]->GetPosition());
				delete m_bBombsList[i];
				m_bBombsList[i] = nullptr;
			}
		}
	}
	RemoveAllNullptrBombs();

	//Update all the explosions.
	for (int i = 0; i < m_eExplosions.size(); i++)
	{
		//If the current explosion exists.
		if (m_eExplosions[i])
		{
			//update it.
			m_eExplosions[i]->Update(m_tTextureManager, a_fDeltaTime);

			//If the explosion needs to be destroyed and hasn't already been destroyed.
			if (m_eExplosions[i]->GetDestructionState())
			{
				//delete it and remove it from the list.
				delete m_eExplosions[i];
				m_eExplosions[i] = nullptr;
			}
		}
	}
	RemoveAllNullptrExplosions();

	//For any explosions that still exist.
	CheckForCollisions();

	RemoveAllNullptrExploadables();
	RemoveAllNullptrBombs();
}

//Exploadable List Modification Functions.
//Add an exploadable object to the list.
void ExplosionManager::AddExplodable(GameObject* a_gExplodable)
{
	m_gExploadableObjects.push_back(a_gExplodable);
}

//Check to see if an exploadable is already in the list.
bool ExplosionManager::CheckForExploadable(GameObject* a_gExplodable)
{
	for (int i = 0; i < m_gExploadableObjects.size(); i++)
	{
		if (m_gExploadableObjects[i] == a_gExplodable)
		{
			return true;
		}
	}
	return false;
}

//Remove an exploadble from the end of the list.
void ExplosionManager::RemoveExploadbleFromEndOfList()
{
	m_gExploadableObjects.pop_back();
}

//Remove a specific exploadble.
void ExplosionManager::RemoveExploadble(GameObject* a_gExplodable)
{
	bool exploadableMovedToEnd = MoveExploadbleToEndOfList(a_gExplodable);
	if (exploadableMovedToEnd)
	{
		RemoveExploadbleFromEndOfList();
	}
}

//Clear the exploadable list of all objects.
void ExplosionManager::ClearExploadbleList()
{
	if (m_gExploadableObjects.size() > 0)
	{
		m_gExploadableObjects.clear();
	}
}

//Move a certain exploadable to the end of the list if it's already in the list.
bool ExplosionManager::MoveExploadbleToEndOfList(GameObject* a_gExplodable)
{
	//If the object exists.
	if (CheckForExploadable(a_gExplodable))
	{
		//Declare Temporary Variables.
		std::vector<GameObject*> tempGameObjectList;

		//Add all gameobjects from original list into new list in new order.
		for (int i = 0; i < m_gExploadableObjects.size(); i++)
		{
			if (m_gExploadableObjects[i] != a_gExplodable)
			{
				tempGameObjectList.push_back(a_gExplodable);
			}

			//Push gameobject onto the end.
			tempGameObjectList.push_back(a_gExplodable);

			//Set normal list to be new list.
			m_gExploadableObjects = tempGameObjectList;

			//Return success.
			return true;
		}
	}
	else
	{
		return false;
	}
}

//Remove all nullptrs from the list.
void ExplosionManager::RemoveAllNullptrExploadables()
{
	//Variabele Declarations.
	std::vector<GameObject*> tempExploadables;
	for (int i = 0; i < m_gExploadableObjects.size(); i++)
	{
		if (m_gExploadableObjects[i] != nullptr)
		{
			tempExploadables.push_back(m_gExploadableObjects[i]);
		}
	}
	m_gExploadableObjects = tempExploadables;
}

//Readd all exploadable objects to the texture manager.
void ExplosionManager::ReAddExploadablesToTextureManager()
{
	for (int i = 0; i < m_gExploadableObjects.size(); i++)
	{
		if (!m_tTextureManager->CheckForTexture(m_gExploadableObjects[i]->GetTexturePtr()))
		{
			m_tTextureManager->AddTexture(m_gExploadableObjects[i]->GetTexturePtr());
		}
	}
}

//Make sure all exploable objects are active.
void ExplosionManager::TurnOnAllExploadables()
{
	for (int i = 0; i < m_gExploadableObjects.size(); i++)
	{
		m_gExploadableObjects[i]->SetActiveState(true);
	}
}

//Explosion List modification Functions.
//Create an explosion at position (x,y).
void ExplosionManager::CreateExplosion(Vector2 a_v2Position)
{
	Vector2 startingDimensions = Vector2(1.0f, 1.0f);
	Explosion* newExplosion = new Explosion(a_v2Position, startingDimensions, 0.0f, true, nullptr, m_tTextureManager, "Assets/Explosion.png", 37.5f);
	m_eExplosions.push_back(newExplosion);
}

//Create an explosion at position (x,y) with a radius of the float argument.
void ExplosionManager::CreateExplosion(Vector2 a_v2Position, float a_fRadius)
{
	Vector2 startingDimensions = Vector2(1.0f, 1.0f);
	Explosion* newExplosion = new Explosion(a_v2Position, startingDimensions, 0.0f, true, nullptr, m_tTextureManager, "Assets/Explosion.png", a_fRadius);
	m_eExplosions.push_back(newExplosion);
}

//Check for an explosion in the explosion list.
bool ExplosionManager::CheckForExplosion(Explosion* a_gExplosion)
{
	for (int i = 0; i < m_eExplosions.size(); i++)
	{
		if (m_eExplosions[i] == a_gExplosion)
		{
			return true;
		}
	}
	return false;
}

//Remove the explosion at the end of the list.
void ExplosionManager::RemoveExplosionFromEndOfList()
{
	m_eExplosions.pop_back();
}

//Remove a specific explosion.
void ExplosionManager::RemoveExplosion(Explosion* a_gExplosion)
{
	bool explosionMovedToEnd = MoveExplosionToEndOfList(a_gExplosion);
	if (explosionMovedToEnd)
	{
		RemoveExplosionFromEndOfList();
	}
}

//Clear the explosion list of all values.
void ExplosionManager::ClearExplosionList()
{
	if (m_eExplosions.size() > 0)
	{
		m_eExplosions.clear();
	}
}

//Remove all nullprt explosions from the list.
void ExplosionManager::RemoveAllNullptrExplosions()
{
	//Variabele Declarations.
	std::vector<Explosion*> tempExplosions;
	for (int i = 0; i < m_eExplosions.size(); i++)
	{
		if (m_eExplosions[i] != nullptr)
		{
			tempExplosions.push_back(m_eExplosions[i]);
		}
	}
	m_eExplosions = tempExplosions;
}

//Add a bomb to the list.
void ExplosionManager::AddBomb(Bomb* a_bBomb)
{
	m_bBombsList.push_back(a_bBomb);
}

//Check for a specific bomb in the list.
bool ExplosionManager::CheckForBomb(Bomb* a_bBomb)
{
	for (int i = 0; i < m_bBombsList.size(); i++)
	{
		if (m_bBombsList[i] == a_bBomb)
		{
			return true;
		}
	}
	return false;
}

//Remove a bomb from the end of the list.
void ExplosionManager::RemoveBombFromEndOfList()
{
	m_bBombsList.pop_back();
}

//Remove a specific bomb.
void ExplosionManager::RemoveBomb(Bomb* a_bBomb)
{
	bool bombMovedToEnd = MoveBombToEndOfList(a_bBomb);
	if (bombMovedToEnd)
	{
		RemoveBombFromEndOfList();
	}
}

//Clear the bomb list.
void ExplosionManager::ClearBombList()
{
	for (int i = 0; i < m_bBombsList.size(); i++)
	{
		delete m_bBombsList[i];
	}
	m_bBombsList.clear();
}

//Move a specific bomb to the end of the list.
bool ExplosionManager::MoveBombToEndOfList(Bomb* a_bBomb)
{
	if (CheckForBomb(a_bBomb))
	{
		//Declare Temporary Variables.
		std::vector<Bomb*> tempBombList;

		//Add all textures from original list into new list in new order.
		for (int i = 0; i < m_bBombsList.size(); i++)
		{
			if (m_bBombsList[i] != a_bBomb)
			{
				tempBombList.push_back(m_bBombsList[i]);
			}
		}

		//Push explosion onto the end.
		tempBombList.push_back(a_bBomb);

		//Return Success.
		return true;
	}
	else
	{
		return false;
	}
}

//Remove all values from the list that are nullptr.
void ExplosionManager::RemoveAllNullptrBombs()
{
	//Variabele Declarations.
	std::vector<Bomb*> tempBombs;
	for (int i = 0; i < m_bBombsList.size(); i++)
	{
		if (m_bBombsList[i] != nullptr)
		{
			tempBombs.push_back(m_bBombsList[i]);
		}
	}
	m_bBombsList = tempBombs;
}

//Move a specific explosion to the end of the list.
bool ExplosionManager::MoveExplosionToEndOfList(Explosion* a_gExplosion)
{
	if (CheckForExplosion(a_gExplosion))
	{
		//Declare Temporary Variables.
		std::vector<Explosion*> tempExplosionList;

		//Add all textures from original list into new list in new order.
		for (int i = 0; i < m_eExplosions.size(); i++)
		{
			if (m_eExplosions[i] != a_gExplosion)
			{
				tempExplosionList.push_back(m_eExplosions[i]);
			}
		}

		//Push explosion onto the end.
		tempExplosionList.push_back(a_gExplosion);

		//Return Success.
		return true;
	}
	else
	{
		return false;
	}
}

//Collision Functions.
//Check for collisions between explosions and exploadable objects (cities and bombs).
void ExplosionManager::CheckForCollisions()
{
	//For every explosion.
	for (int i = 0; i < m_eExplosions.size(); i++)
	{
		//Check every city for collisions.
		for (int j = 0; j < m_gExploadableObjects.size(); j++)
		{
			Vector2 explosionToObject = CalculateVectorBetweenExplosionAndGameobject(m_eExplosions[i]->GetPosition(), m_gExploadableObjects[j]->GetPos());
			float explosionLengthSqr = explosionToObject.LengthSqr();
			float explosionRadiusSquared = m_eExplosions[i]->GetExplosionRadius() * m_eExplosions[i]->GetExplosionRadius() * 2;
			if (explosionLengthSqr <= explosionRadiusSquared)
			{
				if (m_gExploadableObjects[j]->GetTag() == "City")
				{
					m_pPlayerManager->DecrementCityCount();
				}
				//Destroy gameobject.
				delete m_gExploadableObjects[j];
				m_gExploadableObjects[j] = nullptr;
			}
		}

		//Check every bomb for collisions.
		for (int k = 0; k < m_bBombsList.size(); k++)
		{
			Vector2 explosionToBomb = CalculateVectorBetweenExplosionAndGameobject(m_eExplosions[i]->GetPosition(), m_bBombsList[k]->GetPosition());
			float explosionVectorSqr = explosionToBomb.LengthSqr();
			float explosionRadiSquared = m_eExplosions[i]->GetExplosionRadius() * m_eExplosions[i]->GetExplosionRadius();
			if (explosionVectorSqr <= explosionRadiSquared)
			{
				//Destroy gameobject.
				m_bBombsList[k]->SetExplodeState(true);
			}
		}
	}
}

//Calculate the resultant vector from vector "A" to vector "B".
Vector2 ExplosionManager::CalculateVectorBetweenExplosionAndGameobject(Vector2 a_v2A, Vector2 a_v2B)
{
	Vector2 v2A = Vector2(a_v2A.x, a_v2A.y);
	Vector2 v2B = Vector2(a_v2B.x, a_v2B.y);
	Vector2 v2C = v2B - v2A;
	return v2C;
}