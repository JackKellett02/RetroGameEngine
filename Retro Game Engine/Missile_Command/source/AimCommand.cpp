#include "AimCommand.h"
//Constructor with values.
AimCommand::AimCommand(AntiAirCannon* a_gCannon, float a_fAmmountToRotate)
{
	m_gCannon = a_gCannon;
	m_fRotationAmmount = a_fAmmountToRotate;
}

//Destructor.
AimCommand::~AimCommand()
{
	m_gCannon = NULL;
	m_tTimer = nullptr;
}

//When ran it rotates the cannon game object.
void AimCommand::Execute()
{
	if (m_gCannon)
	{
		m_gCannon->TransformRotation(m_fRotationAmmount * m_tTimer->DeltaTime());
		if (m_gCannon->GetRotation() < -90.0f)
		{
			m_gCannon->SetRotation(-90.0f);
		}
	}
}