#include "pch.h"
#include "FSM.h"
#include "FSMState.h"


FSM::~FSM()
{

}

void FSM::Update(float DeltaTime)
{
	if (m_pCurrentState == nullptr)
	{
		// 초기 상태로 바꾼다.
		assert(m_pInitialState != nullptr);
		ChangeState(m_pInitialState->GetName());
		return;
	}

	// Update Action
	// 현재 실행중인 State의 Update를 실행시켜 매프레임 실행할 내용을 처리하게 한다.
	m_pCurrentState->Update(DeltaTime);

	// Transition Check수행하여 조건에 만족할경우 넘겨받은 nextState로 변경한다.
	std::string nextStateName;
	if (m_pCurrentState->CheckTransition(nextStateName))
	{
		ChangeState(nextStateName);
		return;
	}

	// 공유 Transition Check
	//for (auto pStateAlias : m_pStateAlias)
	//{
	//	// 현재 State가 Alias에 포함되어 있는지 확인한다.
	//	if (!pStateAlias->CheckAlias(m_pCurrentState))
	//		continue;

	//	// Alias에 포함되어 있을 경우 Transition을 확인한다.
	//	if (pStateAlias->CheckTransition(nextStateName))
	//	{
	//		ChangeState(nextStateName);
	//		break;
	//	}
	//}
}

void FSM::ChangeState(std::string stateName)
{
	if (m_pCurrentState)
	{
		// Exit Action 
		// State가 변경될때 이전 State가 종료 처리할 내용을 실행한다.
		m_pCurrentState->Exit();
	}

	auto it = m_pStates.find(stateName);
	assert(it != m_pStates.end());
	if (it != m_pStates.end())
	{
		m_pCurrentState = it->second;

		// Enter Action
		// State가 변경될때 새로운 State가 시작 처리할 내용을 실행한다.
		m_pCurrentState->Enter();
	}
	
}

void FSM::SetInitialState(std::string stateName)
{
	auto it = m_pStates.find(stateName);
	assert(it != m_pStates.end());
	if (it != m_pStates.end())
	{
		m_pInitialState = it->second;
	}
	
}

void FSM::AddState(FSMState* pState)
{
	m_pStates.insert(make_pair(pState->GetName(), pState));
}


//void FSM::AddStateAlias(FSMStateAlias* pStateAlias)
//{
//	m_pStateAlias.push_back(pStateAlias);
//}