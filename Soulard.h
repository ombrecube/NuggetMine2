#ifndef SOULARD_H
#define SOULARD_H
//------------------------------------------------------------------------
//
//  Name: Soulard.h
//
//  Desc: class to implement Soulard agents.
//
//  Author: Julien Mass
//
//------------------------------------------------------------------------

#include <string>
#include "States.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "SoulardOwnedStates.h"
#include "ConsoleUtils.h"
#include "Miner.h"
#include "StateMachine.h"
#include "Utils.h"

const int DrunkLevel = 8;

class Soulard : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Soulard>* m_pStateMachine;

	location_type   m_Location;

	//is he presently drunk?
	int            m_DrunkLevel;


public:

	Soulard(int id) :m_Location(shack),
		m_DrunkLevel(0),
		BaseGameEntity(id)

	{
		//set up the state machine
		m_pStateMachine = new StateMachine<Soulard>(this);


		m_pStateMachine->SetGlobalState(SoulardGlobalState::Instance());
	}

	~Soulard() { delete m_pStateMachine; }


	//this must be implemented
	void          Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<Soulard>* GetFSM()const { return m_pStateMachine; }

	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }
	bool          TooDrunk()const;
	bool          Drunk()const;
	void		  DecreaseDrunkLevel() { m_DrunkLevel = 0; }
	void          Drinking() { m_DrunkLevel += 1; }
	
};

#endif

