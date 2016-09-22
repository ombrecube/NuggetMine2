#include "SoulardOwnedStates.h"
#include "MinerOwnedStates.h"
#include "Soulard.h"
#include "Locations.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

SoulardGlobalState* SoulardGlobalState::Instance()
{
	static SoulardGlobalState instance;

	return &instance;
}

void SoulardGlobalState::Execute(Soulard* soulard)
{
	//1 in 10 chance of needing the bathroom (provided she is not already
	//in the bathroom)
	if ((RandFloat() < 0.5) &&
		!soulard->GetFSM()->isInState(*WantToPlay::Instance()))
	{
		soulard->GetFSM()->ChangeState(WantToPlay::Instance());
	}
}

bool SoulardGlobalState::OnMessage(Soulard* soulard, const Telegram& msg)
{
	SetTextColor(BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_HiBobPlay:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(soulard->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(soulard->ID()) <<
			": Hey, Bob do you want to play money games with me ?";

		soulard->GetFSM()->ChangeState(WantToPlay::Instance());
	}

	return true;

	}//end switch

	return false;
}

//------------------------------------------------------------------------EnterSaloonAndDrink

EnterSaloonAndDrink* EnterSaloonAndDrink::Instance()
{
	static EnterSaloonAndDrink instance;

	return &instance;
}

void EnterSaloonAndDrink::Enter(Soulard* soulard)
{
	//if not already cooking put the stew in the oven
	if (soulard->Location() != saloon)
	{
		cout << "\n" << GetNameOfEntity(soulard->ID()) << ":let s go to the saloon!";
		soulard->ChangeLocation(saloon);
	}
}

void EnterSaloonAndDrink::Execute(Soulard* soulard)
{
	cout << "\n" << GetNameOfEntity(soulard->ID()) << ": Hey inkeeper, One glass of whisky please!";
}

void EnterSaloonAndDrink::Exit(Soulard* soulard)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(soulard->ID()) << ": my glass is empty...";
}

bool EnterSaloonAndDrink::OnMessage(Soulard* soulard, const Telegram& msg)
{
		soulard->GetFSM()->ChangeState(Drink::Instance());
	return false;
}

//------------------------------------------------------------------------WantToPlay
WantToPlay* WantToPlay::Instance()
{
	static WantToPlay instance;

	return &instance;
}
void WantToPlay::Enter(Soulard* soulard)
{
	/*//if not already cooking put the stew in the oven
	if (!soulard->Drinking())
	{
		cout << "\n" << GetNameOfEntity(soulard->ID()) << ":let s go drink one more time ick*!";

		//out of the oven
		Dispatch->DispatchMessage(1.5,                  //time delay
			soulard->ID(),           //sender ID
			soulard->ID(),           //receiver ID
			Msg_StewReady,        //msg
			NO_ADDITIONAL_INFO);

		soulard->SetDrinking(true);
	}*/
}

void WantToPlay::Execute(Soulard* soulard)
{
	cout << "\n" << GetNameOfEntity(soulard->ID()) << ": Tabarnak *ick One More please *ick";
}

void WantToPlay::Exit(Soulard* soulard)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(soulard->ID()) << ": It was good! ";
}

bool WantToPlay::OnMessage(Soulard* soulard, const Telegram& msg)
{
	return false;
}
//------------------------------------------------------------------------GoHomeAndSleepTilRested
GoHomeAndSleepDrunk* GoHomeAndSleepDrunk::Instance()
{
	static GoHomeAndSleepDrunk instance;

	return &instance;
}

void GoHomeAndSleepDrunk::Enter(Soulard* soulard)
{
	if (soulard->Location() != shack)
	{
		cout << "\n" << GetNameOfEntity(soulard->ID()) << ": " << "Walkin' home";
		soulard->ChangeLocation(shack);
	}
}

void GoHomeAndSleepDrunk::Execute(Soulard* soulard)
{
	//if Soulard is not fatigued start to dig for nuggets again.
	if (!soulard->TooDrunk())
	{
		cout << "\n" << GetNameOfEntity(soulard->ID()) << ": "
			<< "All mah fatigue has drained away. Time to drink more!";

		soulard->GetFSM()->ChangeState(EnterSaloonAndDrink::Instance());
	}

	else
	{
		//sleep
		soulard->DecreaseDrunkLevel();

		cout << "\n" << GetNameOfEntity(soulard->ID()) << ": " << "ZZZZ... ";
	}
}

void GoHomeAndSleepDrunk::Exit(Soulard* soulard)
{
	//Nothing
}


bool GoHomeAndSleepDrunk::OnMessage(Soulard* soulard, const Telegram& msg)
{
	return false; //send message to global message handler
}

//------------------------------------------------------------------------Drink
Drink* Drink::Instance()
{
	static Drink instance;

	return &instance;
}
void Drink::Enter(Soulard* soulard)
{
	//if not already cooking put the stew in the oven
	if (soulard->Location() != saloon)
	{
		cout << "\n" << GetNameOfEntity(soulard->ID()) << ":Why i am not in the Saloon let s go drink !!";
		soulard->ChangeLocation(saloon);
	}
}

void Drink::Execute(Soulard* soulard)
{
	cout << "\n" << GetNameOfEntity(soulard->ID()) << ": Tabarnak *ick One More please *ick";
	if (soulard->TooDrunk())
	{
		soulard->GetFSM()->ChangeState(GoHomeAndSleepDrunk::Instance());
	}
}

void Drink::Exit(Soulard* soulard)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(soulard->ID()) << ": It was good! *ick ";
}

bool Drink::OnMessage(Soulard* soulard, const Telegram& msg)
{
	return false;
}
