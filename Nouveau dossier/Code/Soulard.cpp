#include "Soulard.h"

bool Soulard::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

bool Soulard::TooDrunk() const
{
	if (m_DrunkLevel >= DrunkLevel) { return true; }

	return false;
}

bool Soulard::Drunk() const
{
	if (m_DrunkLevel >= DrunkLevel-3) { return true; }

	return false;
}


void Soulard::Update()
{
	//set text color to Blue
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}