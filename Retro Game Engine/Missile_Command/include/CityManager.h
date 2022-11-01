////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:            CityManager.h
// Author:          Jack Kellett
// Date Created:    13/05/2021
// Brief:           Spawns cities and adds them to the "exploadableList" in the explosion manager.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _CITYMANAGER_H_
#define _CITYMANAGER_H_
#include "MathUtility.h"
#include "GameObject.h"
#include "ExplosionManager.h"
#include "PlayerManager.h"
#include "Graphics.h"

class CityManager
{
private:
	//Member Variables.
	TextureManager* m_tTextureManager;
	ExplosionManager* m_eExplosionManager;
	PlayerManager* m_pPlayerManager;

	//City Variables.
	Vector2 m_v2Dimensions;
	std::string m_sTexturePath;

public:
	//Public access functions.
	//Constructor/Destructor.
	CityManager(TextureManager* a_tTextureManager, ExplosionManager* a_eExplosionManager, PlayerManager* a_pPlayerManager, Vector2 a_v2Dimensions, std::string a_sTexturePath);
	~CityManager();

	//Create cities at regular intervals.
	void CreateCities(int a_iCityNumber);
};

#endif // !_CITYMANAGER_H_
