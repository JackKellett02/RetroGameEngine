#include "..\include\CannonRangeCommand.h"

//Constructor with values.
CannonRangeCommand::CannonRangeCommand(AntiAirCannon* a_gCannon, float a_fRangeTransformValue)
{
	m_gCannon = a_gCannon;
	m_fRangeTranformValue = a_fRangeTransformValue;
}

//Destructor.
CannonRangeCommand::~CannonRangeCommand()
{
	//Don't delete as this is deleted by the game manager.
	m_gCannon = nullptr;
}

//Transform the cannon's firing distance based on the value held in this class.
void CannonRangeCommand::Execute()
{
	if (m_gCannon)
	{
		m_gCannon->TransformFiringDistance(m_fRangeTranformValue * m_tTimer->DeltaTime());
	}
}