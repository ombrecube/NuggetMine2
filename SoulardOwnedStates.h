#ifndef SOULARD_OWNED_STATES_H
#define SOULARD_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   SoulardOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Soulard class
//
//  Author: Julien Mass
//
//------------------------------------------------------------------------
#include "States.h"

class Soulard;

//------------------------------------------------------------------------
class SoulardGlobalState : public State<Soulard>
{
private:

	SoulardGlobalState() {}

	//copy ctor and assignment should be private
	SoulardGlobalState(const SoulardGlobalState&);
	SoulardGlobalState& operator=(const SoulardGlobalState&);

public:

	//this is a singleton
	static SoulardGlobalState* Instance();

	virtual void Enter(Soulard* soulard) {}

	virtual void Execute(Soulard* soulard);

	virtual void Exit(Soulard* soulard) {}

	virtual bool OnMessage(Soulard* soulard, const Telegram& msg);
};
//------------------------------------------------------------------------
class EnterSaloonAndDrink : public State<Soulard>
{
private:
	EnterSaloonAndDrink() {}

	//copy ctor and assignment should be private
	EnterSaloonAndDrink(const EnterSaloonAndDrink&);
	EnterSaloonAndDrink& operator=(const EnterSaloonAndDrink&);

public:

	//this is a singleton
	static EnterSaloonAndDrink* Instance();

	virtual void Enter(Soulard* soulard);

	virtual void Execute(Soulard* soulard);

	virtual void Exit(Soulard* soulard);

	virtual bool OnMessage(Soulard* soulard, const Telegram& msg);
};
//------------------------------------------------------------------------
class WantToPlay : public State<Soulard>
{
private:
	WantToPlay() {}

	//copy ctor and assignment should be private
	WantToPlay(const WantToPlay&);
	WantToPlay& operator=(const WantToPlay&);

public:

	//this is a singleton
	static WantToPlay* Instance();

	virtual void Enter(Soulard* soulard);

	virtual void Execute(Soulard* soulard);

	virtual void Exit(Soulard* soulard);

	virtual bool OnMessage(Soulard* soulard, const Telegram& msg);
};
//------------------------------------------------------------------------
class GoHomeAndSleepDrunk : public State<Soulard>
{
private:

	GoHomeAndSleepDrunk() {}

	//copy ctor and assignment should be private
	GoHomeAndSleepDrunk(const GoHomeAndSleepDrunk&);
	GoHomeAndSleepDrunk& operator=(const GoHomeAndSleepDrunk&);

public:

	//this is a singleton
	static GoHomeAndSleepDrunk* Instance();

	virtual void Enter(Soulard* soulard);

	virtual void Execute(Soulard* soulard);

	virtual void Exit(Soulard* soulard);

	virtual bool OnMessage(Soulard* agent, const Telegram& msg);
};
//------------------------------------------------------------------------
class Drink: public State<Soulard>
{
private:

	Drink() {}

	//copy ctor and assignment should be private
	Drink(const Drink&);
	Drink& operator=(const Drink&);

public:

	//this is a singleton
	static Drink* Instance();

	virtual void Enter(Soulard* soulard);

	virtual void Execute(Soulard* soulard);

	virtual void Exit(Soulard* soulard);

	virtual bool OnMessage(Soulard* soulard, const Telegram& msg);
};




#endif