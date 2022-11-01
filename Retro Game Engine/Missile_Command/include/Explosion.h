/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:              Explosion.h
// Author:            Jack Kellett
// Date Created:      11/05/2021
// Brief:             Explosion will spawn a sprite then check for any explodables in a radius and then destroy them.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "MathUtility.h"
#include "GameObject.h"

class Explosion : public GameObject
{
private:
	//Game object pointer.
	GameObject* m_gExplosionObject;

	//Variables.
	float m_fExplosionRadius;
	float m_fTimeTillDestruction;

	bool m_bDestroyThis;

	Vector2 m_v2ActualExplosionPos;

public:
	//Constructor/Destructor.
	Explosion();
	Explosion(Explosion* a_gExplosion);
	Explosion(Vector2 a_v2Pos, Vector2 a_v2Dimensions, float a_fRotation, bool a_bActiveState, GameObject* a_oParent, TextureManager* a_tTextureManager, std::string TexturePath, float a_fExplosionRadius);
	Explosion(float a_fX, float a_fY, float a_fWidth, float a_fHeight, float a_fRotation, bool a_bActiveState, GameObject* a_oParent, TextureManager* a_tTextureManager, std::string TexturePath, float a_fExplosionRadius);
	~Explosion();

	//Update the cannons variables.
	void Update(TextureManager* textureManager, float a_fDeltaTime);

	//Getters.
	float GetExplosionRadius();
	bool GetDestructionState();
	Vector2 GetPosition();
};

#endif // !_EXPLOSION_H_
