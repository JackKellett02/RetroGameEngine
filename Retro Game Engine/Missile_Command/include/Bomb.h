/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:           Bomb.h
// Author:         Jack Kellett
// Date Created:   13/05/2021
// Brief:          Spawned at position x,y and when active it falls down to the bottom of the screen and blows up upon reaching the bottom.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _BOMB_H_
#define _BOMB_H_
#include "MathUtility.h"
#include "GameState.h"
#include "GameObject.h"
#include "Graphics.h"

class Bomb : public GameObject
{
private:
	//Manager Pointers.
	GameState* m_gGameState;

	//Bomb Gameobject.
	GameObject* m_gBomb;

	//Bomb transform variables.
	Vector2 m_v2Position;
	Vector2 m_v2Velocity;
	Vector2 m_v2Accelleration;

	//Texture Path.
	std::string m_sTexturePath;

	//Explode?
	bool m_bExplode;

public:
	//Public Access Functions
	//Constructor/Destructor.
	Bomb(GameState* a_gGameState, TextureManager* a_tTextureManager, Vector2 a_v2Accelleration, std::string a_sTexturePath);
	Bomb(Bomb* a_bBombPrototype);
	~Bomb();

	//General Update Function.
	void Update(float a_fDeltaTime);

	//Movement Functions.
	void Accelerate(float a_fDeltaTime);
	void Move(float a_fDeltaTime);

	//Getters.
	GameObject* GetBombGameObjectPtr();
	GameState* GetGameStatePtr();
	Vector2 GetPosition();
	Vector2 GetVelocity();
	Vector2 GetAcceleration();
	std::string GetTexturePath();
	bool GetExplodeState();

	//Setters.
	void SetExplodeState(bool a_bExplode);
	void SetPosition(Vector2 a_v2Pos);

	//Clone Function.
	Bomb* Clone();
};


#endif // !_BOMB_H_
