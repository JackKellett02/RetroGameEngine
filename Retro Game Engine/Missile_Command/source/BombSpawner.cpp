#include "..\include\BombSpawner.h"

//Constructor with values.
BombSpawner::BombSpawner(PlayerManager* a_pPlayerManager, GameState* a_gGameState, ExplosionManager* a_eExplosionManager, TextureManager* a_tTextureManager, Vector2 a_v2Accelleration, std::string a_sTexturePath, int a_iBombCount)
{
	m_bRoundOver = false;
	m_tTextureManager = a_tTextureManager;
	m_bBombPrototype = new Bomb(a_gGameState, a_tTextureManager, a_v2Accelleration, a_sTexturePath);
	m_fTimer = 0.0f;
	m_fTimerForSwitch = 0.0f;
	m_fTimeToSwitch = 20.0f;
	m_fTimeBetweenBombs = 1.5f;
	m_pPlayerManager = a_pPlayerManager;
	m_iBombCount = a_iBombCount;
	m_gGameState = a_gGameState;
	m_eExplosionManager = a_eExplosionManager;
	m_tRoundOverText = nullptr;
}

//Destructor.
BombSpawner::~BombSpawner()
{
	if (m_bBombPrototype)
	{
		delete m_bBombPrototype;
		m_bBombPrototype = nullptr;
	}

	if (m_tRoundOverText)
	{
		delete m_tRoundOverText;
		m_tRoundOverText = nullptr;
	}

	//I don't delete these values as they are deleted by the game manager.
	m_gGameState = nullptr;
	m_eExplosionManager = nullptr;
	m_pPlayerManager = nullptr;
	m_tTextureManager = nullptr;
}

//Check when a bomb should be spawned and when the round is over.
void BombSpawner::Update(float a_fDeltaTime)
{
	if (m_fTimer >= m_fTimeBetweenBombs)
	{
		m_fTimer = 0.0f;
		SpawnBomb();
	}
	m_fTimer += a_fDeltaTime;

	if (m_iBombCount <= 0)
	{
		if (!m_bRoundOver)
		{
			//Set round over to true.
			m_bRoundOver = true;

			//Set Up Text.
			Vector2 dimensions = Vector2(1000.0f, 200.0f);
			Vector2 position = Vector2((Graphics::SCREEN_WIDTH / 2) - (dimensions.x / 2), (Graphics::SCREEN_HEIGHT / 2) - (dimensions.y / 2));
			m_tRoundOverText = new Texture(std::string("Round Over, next round will load shortly.").c_str(), "arial.ttf", position, dimensions, 0.0f, "RoundOver");
			m_tTextureManager->AddTexture(m_tRoundOverText);
		}
		if (m_gGameState && m_pPlayerManager && m_fTimerForSwitch >= m_fTimeToSwitch)
		{
			m_fTimerForSwitch = 0.0f;
			m_pPlayerManager->CalculatePlayerScore();
			m_gGameState->SetGameState(GAME);
		}
		m_fTimerForSwitch += a_fDeltaTime;
	}
}

//Spawn a new bomb at a random position at the top of the screen.
void BombSpawner::SpawnBomb()
{
	if (m_iBombCount > 0)
	{
		m_iBombCount -= 1;
		Bomb* newBomb = m_bBombPrototype->Clone();
		newBomb->SetPosition(Vector2(Random::RandRange(20.0f, Graphics::SCREEN_WIDTH - 20.0f), 100.0f));
		newBomb->GetBombGameObjectPtr()->SetActiveState(true);
		m_eExplosionManager->AddBomb(newBomb);
	}
}