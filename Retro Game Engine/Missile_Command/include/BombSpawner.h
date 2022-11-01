////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:          BombSpawner.h
// Author:        Jack Kellett
// Date Created:  14/05/2021
// Brief:         This uses the prototype pattern to spawn a bomb then it randomly moves them to a position at the top of the screen.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _BOMBSPAWNER_H_
#define _BOMBSPAWNER_H_
#include "ExplosionManager.h"
#include "Bomb.h"
#include "MathUtility.h"
#include "PlayerManager.h"

class BombSpawner
{
private:
	//Manager Pointers.
	GameState* m_gGameState;
	ExplosionManager* m_eExplosionManager;
	PlayerManager* m_pPlayerManager;
	TextureManager* m_tTextureManager;

	//Member Variables.
	Bomb* m_bBombPrototype;

	//Timer Variable.
	float m_fTimer;
	float m_fTimerForSwitch;
	float m_fTimeToSwitch;
	float m_fTimeBetweenBombs;

	//Total Bomb Count.
	int m_iBombCount;

	//Round Over Variables.
	bool m_bRoundOver;
	Texture* m_tRoundOverText;

public:
	//Public Access Functions.
	//Constructor/Destructor.
	BombSpawner(PlayerManager* a_pPlayerManager, GameState* a_gGameState, ExplosionManager* a_eExplosionManager, TextureManager* a_tTextureManager, Vector2 a_v2Accelleration, std::string a_sTexturePath, int a_iBombCount);
	~BombSpawner();

	//General Update Function.
	void Update(float a_fDeltaTime);

	//Spawn Function.
	void SpawnBomb();

};

#endif // !_BOMBSPAWNER_H_
