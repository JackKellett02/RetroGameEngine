#include "..\include\UseButtonCommand.h"

//Sets the selected button.
void UseButtonCommand::SetSelectedButton()
{
	if (m_mMenu)
	{
		int index = m_mMenu->GetIndexPos();
		m_bCurrentlySelectedButton = m_mMenu->GetButtonAtIndex(index);
	}
}

//Constructor.
UseButtonCommand::UseButtonCommand(Menu* a_mMenu, float a_fTimeToChange)
{
	m_fTimeToChangeButton = a_fTimeToChange;
	m_fTimer = 0.0f;
	m_tTimer = Timer::Instance();

	m_mMenu = a_mMenu;
	m_bCurrentlySelectedButton = nullptr;
}

//Destructor.
UseButtonCommand::~UseButtonCommand()
{
	m_mMenu = nullptr;
	m_bCurrentlySelectedButton = nullptr;
}

void UseButtonCommand::Update()
{
	m_fTimer += m_tTimer->DeltaTime();
}

//Executes the commmand stored in the currently selected button.
void UseButtonCommand::Execute()
{
	SetSelectedButton();
	if (m_bCurrentlySelectedButton && m_fTimer >= m_fTimeToChangeButton)
	{
		m_fTimer = 0.0f;
		m_bCurrentlySelectedButton->RunCommand();
	}
}
