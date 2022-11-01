///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:             ExplosionManager.h
// Author:           Jack Kellett
// Date Created:     11/05/2021
// Brief:            Does all collision checks for explosions and clones all explosions from here.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _EXPLOSIONMANAGER_H_
#define _EXPLOSIONMANAGER_H_
#include "Explosion.h"
#include "MathUtility.h"
#include "PlayerManager.h"
#include "Bomb.h"
#include <vector>

class ExplosionManager
{
private:
	//Member Variables.
	//List of all objects that can be exploded.
	std::vector<GameObject*> m_gExploadableObjects;
	std::vector<Explosion*> m_eExplosions;
	std::vector<Bomb*> m_bBombsList; //I didn't want to have this list but I couldn't find a way to trigger the explosions from the gameobject of the bomb so here this is.

	//Managers.
	TextureManager* m_tTextureManager;
	PlayerManager* m_pPlayerManager;

	//Private Functions
	Vector2 CalculateVectorBetweenExplosionAndGameobject(Vector2 a_v2A, Vector2 a_v2B);

public:
	//Public Access Functions.
	//Constructor/Destructor.
	ExplosionManager(TextureManager* a_tTextureManager, PlayerManager* a_pPlayerManager);
	~ExplosionManager();

	//General Functions
	void Update(float a_fDeltaTime);

	//Exploadable List Modification Functions.
	void AddExplodable(GameObject* a_gExplodable);
	bool CheckForExploadable(GameObject* a_gExplodable);
	void RemoveExploadbleFromEndOfList();
	void RemoveExploadble(GameObject* a_gExplodable);
	void ClearExploadbleList();
	bool MoveExploadbleToEndOfList(GameObject* a_gExplodable);
	void RemoveAllNullptrExploadables();
	void ReAddExploadablesToTextureManager();
	void TurnOnAllExploadables();

	//Explosion List ModificatioN Functions.
	void CreateExplosion(Vector2 a_v2Position);
	void CreateExplosion(Vector2 a_v2Position, float a_fRadius);
	bool CheckForExplosion(Explosion* a_gExplosion);
	void RemoveExplosionFromEndOfList();
	void RemoveExplosion(Explosion* a_gExplosion);
	void ClearExplosionList();
	bool MoveExplosionToEndOfList(Explosion* a_gExplosion);
	void RemoveAllNullptrExplosions();

	//Bomb List ModificatioN Functions.
	void AddBomb(Bomb* a_bBomb);
	bool CheckForBomb(Bomb* a_bBomb);
	void RemoveBombFromEndOfList();
	void RemoveBomb(Bomb* a_bBomb);
	void ClearBombList();
	bool MoveBombToEndOfList(Bomb* a_bBomb);
	void RemoveAllNullptrBombs();

	//Collision Functions
	void CheckForCollisions();
};

#endif // !_EXPLOSIONMANAGER_H_
