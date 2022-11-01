#include "..\include\FireCommand.h"

//Constructor with value.
FireCommand::FireCommand(AntiAirCannon* a_gCannon)
{
	m_gCannon = a_gCannon;
}

//Destructor.
FireCommand::~FireCommand()
{
	m_gCannon = NULL;
}

//Fire the cannon.
void FireCommand::Execute()
{
	if (m_gCannon)
	{
		m_gCannon->Fire();
	}
}
