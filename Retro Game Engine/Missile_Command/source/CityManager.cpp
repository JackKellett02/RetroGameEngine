#include "..\include\CityManager.h"

//Constructor with values.
CityManager::CityManager(TextureManager* a_tTextureManager, ExplosionManager* a_eExplosionManager, PlayerManager* a_pPlayerManager, Vector2 a_v2Dimensions, std::string a_sTexturePath)
{
	m_tTextureManager = a_tTextureManager;
	m_eExplosionManager = a_eExplosionManager;
	m_pPlayerManager = a_pPlayerManager;
	m_v2Dimensions = a_v2Dimensions;
	m_sTexturePath = a_sTexturePath;
}

//Destructor.
CityManager::~CityManager()
{
	m_eExplosionManager = nullptr;
	m_pPlayerManager = nullptr;
}

//Create a number of cities at regular intervals.
void CityManager::CreateCities(int a_iCityNumber)
{
	//Set Up base variables.
	float cityInterval = 2 * (Graphics::SCREEN_WIDTH / (float)a_iCityNumber);
	Vector2 position = Vector2(cityInterval - (m_v2Dimensions.x / 2) - 267.5, Graphics::SCREEN_HEIGHT - m_v2Dimensions.y);

	//Create the cities.
	for (int i = 0; i < a_iCityNumber; i++)
	{
		//Add the city.
		GameObject* newCity = new GameObject(position, m_v2Dimensions, 0.0f, true, nullptr, m_tTextureManager, m_sTexturePath);
		newCity->SetTag("City");
		m_eExplosionManager->AddExplodable(newCity);

		//Update position for next city.
		position.x += cityInterval / 2;

		//Increment city counter.
		m_pPlayerManager->IncrementCityCount();
	}
}