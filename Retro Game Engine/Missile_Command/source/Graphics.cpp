#include "..\include\Graphics.h"

Graphics* Graphics::m_sInstance = NULL;
bool Graphics::m_bInitialised = false;

//Gets the graphics instance and creates one if one hasn't been created already.
Graphics* Graphics::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new Graphics();
	}
	return m_sInstance;
}

//Deletes the graphics instance.
void Graphics::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
	m_bInitialised = false;
}

//Returns whether or not the graphics has been initialised.
bool Graphics::Initialised()
{
	return m_bInitialised;
}

//Renders the renderer.
void Graphics::Render()
{
	SDL_RenderPresent(m_rRenderer);
}

//Adds a texture to the renderer.
SDL_Texture* Graphics::LoadTexture(std::string a_sPath)
{
	SDL_Texture* tTexture = NULL;

	SDL_Surface* sSurface = IMG_Load(a_sPath.c_str());
	if (sSurface == NULL)
	{
		printf("Image Load Error: Path(%s), Error(%s)\n", a_sPath.c_str(), IMG_GetError());

		return tTexture;
	}

	tTexture = SDL_CreateTextureFromSurface(m_rRenderer, sSurface);
	if (tTexture == NULL)
	{
		printf("Texture Create Error: 5s\n", IMG_GetError());
	}

	SDL_FreeSurface(sSurface);
	return tTexture;
}

//Loads text onto the renderer.
SDL_Texture* Graphics::LoadText(const char* text, const char* font)
{
	SDL_Texture* texture = NULL;
	TTF_Font* textFont = TTF_OpenFont(std::string(SDL_GetBasePath()).append(font).c_str(), 24);
	SDL_Color textColour = { 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(textFont, text, textColour);

	if (surface == NULL)
	{
		printf("Text Load Error: Error: (%s)\n", text);
		return texture;
	}

	texture = SDL_CreateTextureFromSurface(m_rRenderer, surface);
	if (texture == NULL)
	{
		printf("Text Create Error: %s\n", IMG_GetError());
	}
	SDL_FreeSurface(surface);
	return texture;
}

//Clears the renderer.
void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(m_rRenderer);
}

//Draws a texture.
void Graphics::DrawTexture(SDL_Texture* a_tTexture, Vector2& a_vPos, int a_iWidth, int a_iHeight, float a_fRot)
{
	SDL_Rect renderQuad = { a_vPos.x, a_vPos.y, a_iWidth, a_iHeight };
	SDL_RendererFlip rFlip = SDL_FLIP_NONE;

	SDL_RenderCopyEx(m_rRenderer, a_tTexture, NULL, &renderQuad, a_fRot, NULL, rFlip);
}

//Default construction.
Graphics::Graphics()
{
	m_bBackBuffer = NULL;
	m_bInitialised = Init();
}

//Destructor.
Graphics::~Graphics()
{
	SDL_DestroyWindow(m_wWindow);
	m_wWindow = NULL;

	SDL_DestroyRenderer(m_rRenderer);
	m_rRenderer = NULL;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

//Make sure the graphics is properly initialised.
bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Initialisation Error: %s\n", SDL_GetError());
		return false;
	}

	if (TTF_Init() < 0)
	{
		printf("Initialisation Error: %s\n", SDL_GetError());
		return false;
	}

	m_wWindow = SDL_CreateWindow("Missile Command!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_wWindow == NULL)
	{
		printf("Window Creation Error: %s\n", SDL_GetError());
		return false;
	}

	m_rRenderer = SDL_CreateRenderer(m_wWindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_rRenderer == NULL)
	{
		printf("Renderer Creation Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(m_rRenderer, 0, 0, 0, 0xFF);

	int iFlag = IMG_INIT_PNG;
	if (!(IMG_Init(iFlag) & iFlag))
	{
		printf("Image Initialisation Error: %s\n", IMG_GetError());
		return false;
	}

	m_bBackBuffer = SDL_GetWindowSurface(m_wWindow);
	return true;
}
