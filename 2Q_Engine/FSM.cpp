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
		// �ʱ� ���·� �ٲ۴�.
		assert(m_pInitialState != nullptr);
		ChangeState(m_pInitialState->GetName());
		return;
	}

	// Update Action
	// ���� �������� State�� Update�� ������� �������� ������ ������ ó���ϰ� �Ѵ�.
	m_pCurrentState->Update(DeltaTime);

	// Transition Check�����Ͽ� ���ǿ� �����Ұ�� �Ѱܹ��� nextState�� �����Ѵ�.
	std::string nextStateName;
	if (m_pCurrentState->CheckTransition(nextStateName))
	{
		ChangeState(nextStateName);
		return;
	}

	// ���� Transition Check
	//for (auto pStateAlias : m_pStateAlias)
	//{
	//	// ���� State�� Alias�� ���ԵǾ� �ִ��� Ȯ���Ѵ�.
	//	if (!pStateAlias->CheckAlias(m_pCurrentState))
	//		continue;

	//	// Alias�� ���ԵǾ� ���� ��� Transition�� Ȯ���Ѵ�.
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
		// State�� ����ɶ� ���� State�� ���� ó���� ������ �����Ѵ�.
		m_pCurrentState->Exit();
	}

	auto it = m_pStates.find(stateName);
	assert(it != m_pStates.end());
	if (it != m_pStates.end())
	{
		m_pCurrentState = it->second;

		// Enter Action
		// State�� ����ɶ� ���ο� State�� ���� ó���� ������ �����Ѵ�.
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