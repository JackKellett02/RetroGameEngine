#include "..\include\Timer.h"

Timer* Timer::m_sInstance = NULL;

//Creates an instance of timer if one hasn't been created already.
Timer* Timer::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new Timer();
	}
	return m_sInstance;
}

//Deletes the timer instance.
void Timer::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
}

//Returns the current deltaTime.
float Timer::DeltaTime()
{
	return m_fDeltaTime;
}

//Returns the time elapsed.
float Timer::TimeElapsed()
{
	return m_fTimeElapsed;
}

//Sets the current timeScale.
void Timer::SetTimeScale(float a_fScale)
{
	m_fTimeScale = a_fScale;
}

//Gets the current time scale.
float Timer::GetTimeScale()
{
	return m_fTimeScale;
}

//Updates the timer.
bool Timer::Update()
{
	m_uiElapsedTicks = SDL_GetTicks() - m_uiStartTicks;
	m_fDeltaTime = m_uiElapsedTicks * 0.001f;//Convert from ms
	m_fTimeElapsed += m_fDeltaTime;
	if (m_fDeltaTime > 0.0f)
	{
		return true;
	}
	return false;
}

//Resets the timer.
void Timer::Reset()
{
	m_uiStartTicks = SDL_GetTicks();
	m_uiElapsedTicks = 0;
	m_fDeltaTime = 0.0f;
}

//Constructor.
Timer::Timer()
{
	Reset();
	m_fTimeScale = 1.0f;
	m_fTimeElapsed = 0.0f;
}

//Destructor.
Timer::~Timer()
{

}
