#pragma once
#include "Component.h"
#include "FSM.h"

class FSMCharacter;
class FiniteStateMachine;
class GameObject;
class FSMComponent :
	public Component
{
public:
	FSMComponent(GameObject* pOwner, const string& Name, TransformComponent* pRoot = nullptr)
		: Component(pOwner, Name)
		, m_pFSM(nullptr)
	{

	}

	virtual ~FSMComponent()
	{
		if (m_pFSM != nullptr)
			delete m_pFSM;
	}
protected:
	FSM* m_pFSM;
public:
	virtual void Update(float DeltaTime)
	{
		if (m_pFSM != nullptr)
			m_pFSM->Update(DeltaTime);
	}

	template<typename T>
	T* CreateFiniteStateMachine()
	{
		assert(m_pFSM == nullptr);
		// �θ�Ŭ������ FSM���� Ȯ��
		bool bIsFSM = is_base_of<FSM, T>::value;
		assert(bIsFSM);
		T* newFSM = new T(this);

		m_pFSM = newFSM;
		return newFSM;
	}
};

