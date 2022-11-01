///////////////////////////////////////////////////////////////////////////////////////////
// File:                   AntiAirCannon.h
// Author:                 Jack Kellett
// Date Created:           29/04/2021
// Brief:                  This will be the cannon that fires projectiles to destroy bombs.
///////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ANTIAIRCANNON_H_
#define _ANTIAIRCANNON_H_
#include "MathUtility.h"
#include "GameObject.h"
#include "ExplosionManager.h"
#include "PlayerManager.h"

class AntiAirCannon : public GameObject
{
private:
	//Game object pointer.
	GameObject* m_gCannonGameObject;
	ExplosionManager* m_eExplosionManager;
	TextureManager* m_tTextureManager;

	//Player manager used to check whether or not the cannon can be fired.
	PlayerManager* m_pPlayer;

	//Variables to control firing the projectile.
	Vector2 m_vFiringVector;
	Vector2 m_vTargetPosition;
	float m_fCurrentFiringDistance;
	float m_fMinFiringDistance;
	float m_fMaxFiringDistance;
	float m_fTimer;
	bool m_bUpdateTimer;

	//Target point texture.
	Texture* m_tTargetTexture;

	//Private Functions
	Vector2 CalculateFiringVector();
	Vector2 CalculateTargetPosition();

public:
	//Constructor/Destructor.
	AntiAirCannon();
	AntiAirCannon(Vector2 a_v2Pos, Vector2 a_v2Dimensions, float a_fRotation, float a_fMinFireDist, float a_fMaxFireDist, bool a_bActiveState, GameObject* a_oParent, TextureManager* a_tTextureManager, PlayerManager* a_pPlayer, ExplosionManager* a_eExplosionManager, std::string cannonTexturePath, std::string targetTexturePath);
	AntiAirCannon(float a_fX, float a_fY, float a_fWidth, float a_fHeight, float a_fRotation, float a_fMinFireDist, float a_fMaxFireDist, bool a_bActiveState, GameObject* a_oParent, TextureManager* a_tTextureManager, PlayerManager* a_pPlayer, ExplosionManager* a_eExplosionManager, std::string cannonTexturePath, std::string targetTexturePath);
	~AntiAirCannon();

	//Update the cannons variables.
	void Update(float a_fDeltaTime);
	void Fire();

	//Getters.
	float GetMaxFiringDistance();
	float GetMinFiringDistance();
	float GetCurrentFiringDistance();

	//Setters
	void SetPos(Vector2 a_v2Position);
	void SetDimensions(Vector2 a_v2Dimensions);
	void SetRotation(float a_fRotation);
	void SetActiveState(bool a_bActiveState);
	void SetParent(GameObject* a_oParent);
	void SetTexturePath(std::string texturePath);

	//Increase or decrease member variables by arguments.
	void TranslatePos(float a_fMovementX, float a_fMovementY);
	void TransformDimensions(float a_fWidthChange, float a_fHeightChange);
	void TransformRotation(float a_fRotationChange);

	//Set max/min/current firing distances to float. These have to be public as I need to modify the firing distance variables from another class.
	void SetMaxFiringDistance(float a_fDistance);
	void SetMinFiringDistance(float a_fDistance);

	//Transform current firing distance by float. These have to be public as I need to modify the firing distance variables from another class.
	void TransformFiringDistance(float a_fDistance);
};
#endif // !_ANTIAIRCANNON_H_
