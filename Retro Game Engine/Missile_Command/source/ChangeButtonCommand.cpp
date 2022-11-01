#include "..\include\ChangeButtonCommand.h"

//Constructor.
ChangeButtonCommand::ChangeButtonCommand(Menu* a_mMenu, bool a_bIncrememnt, float a_fTimeToChangeButton)
{
	m_tTimer = Timer::Instance();
	m_fTimer = 0.0f;
	m_fTimeToChangeButton = a_fTimeToChangeButton;

	if (a_mMenu)
	{
		m_mMenu = a_mMenu;
		m_bIncrement = a_bIncrememnt;
	}
	else
	{
		m_mMenu = nullptr;
		m_bIncrement = a_bIncrememnt;
	}
}

//Destructor.
ChangeButtonCommand::~ChangeButtonCommand()
{
	if (m_mMenu)
	{
		m_mMenu = nullptr;
	}
}

void ChangeButtonCommand::Update()
{
	m_fTimer += m_tTimer->DeltaTime();
}

//Increment menu index by 1 or decrement by 1.
void ChangeButtonCommand::Execute()
{
	if (m_mMenu)
	{
		if (m_fTimer >= m_fTimeToChangeButton)
		{
			m_fTimer = 0.0f;
			if (m_bIncrement)
			{
				m_mMenu->ChangeIndexByInt(1);
			}
			else
			{
				m_mMenu->ChangeIndexByInt(-1);
			}
		}
	}
}