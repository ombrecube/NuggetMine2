#ifndef AGENTSOULARD_H	
#define MINERSWIFE_H
//------------------------------------------------------------------------
//
//  Name: AgentSoulard.h
//
//  Desc: class to implement a soulard (Bob's friend).
//
//  Author: Mass Julien
//
//------------------------------------------------------------------------

#include <string>

#include "States.h"
#include "BaseGameEntity.h"
#include "Locations.h"
//#include "MinersWifeOwnedStates.h" #Create is State
#include "ConsoleUtils.h"
#include "Miner.h"
#include "StateMachine.h"
#include "Utils.h"



class AgentSoulard : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<AgentSoulard>* m_pStateMachine;

	location_type   m_Location;

	//is he presently drunk?
	int				m_Drunk;
	


public:

	AgentSoulard(int id) :m_Location(shack),
		m_Drunk=0,
		BaseGameEntity(id)

	{
		//set up the state machine
		m_pStateMachine = new StateMachine<AgentSoulard>(this);

		m_pStateMachine->SetCurrentState(DoHouseWork::Instance());

		m_pStateMachine->SetGlobalState(WifesGlobalState::Instance());
	}

	~AgentSoulard(){ delete m_pStateMachine; }


	//this must be implemented
	void          Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<AgentSoulard>* GetFSM()const{ return m_pStateMachine; }

	//----------------------------------------------------accessors
	location_type Location()const{ return m_Location; }
	void          ChangeLocation(location_type loc){ m_Location = loc; }

	bool          Cooking()const{ return m_bCooking; }
	void          SetCooking(bool val){ m_bCooking = val; }

};

#endif
