#pragma once
#include "AnimationComponent.h"

class FSMComponent;
class FSMState;
class FSMTransition;
class FSM
{
public:
	FSM(FSMComponent* pOwnerComponent)
		: m_pCurrentState(nullptr)
		, m_pInitialState(nullptr)
		, m_pOwnerComponent(pOwnerComponent)
	{

	}
	virtual ~FSM();
protected:
	FSMState* m_pCurrentState;  
	FSMState* m_pInitialState;	
	FSMComponent* m_pOwnerComponent;

	map<string, FSMState*> m_pStates;	// ������ FSMState���� �����ϴ� �����̳�

	//std::vector<FSMStateAlias*> m_pStateAlias;	// StateAlias ���� �����ϴ� �����̳�
public:
	virtual void Update(float DeltaTime);
	void ChangeState(string stateName);
	void SetInitialState(string stateName);
	void AddState(FSMState* pState);
	//void AddStateAlias(FSMStateAlias* pStateAlias);

};

