#pragma once
#include "FSM.h"
#include "FSMState.h"
//#include "FSMTransition.h"
#include "StateIdle.h"
//#include "StateAttack.h"
#include "StateMove.h"
#include "StateDeath.h"
//#include "TransitionDeath.h"

//#include "FSMStateAlias.h"
#include "FSMComponent.h"
#include "MovementComponent.h"
#include "GameObject.h"

class AnimationComponent;
class MovementComponent;
/*
	이 FSM은 PlayerCharacter와 분리된 게임 정보로 작동되므로
	NPC에게도 사용할수있다.
*/
class FSMCharacter :
	public FSM
{
public:
	FSMCharacter(FSMComponent* pOwner)
		: FSM(pOwner)
		, m_StateIdle(this)
		, m_StateMove(this)
		, m_StateDeath(this)
		/*m_TransitionToDeath(this),
		m_StateAliasDeath(this)*/
	{
		AddState(&m_StateMove);
		AddState(&m_StateIdle);
		AddState(&m_StateDeath);

		//AddStateAlias(&m_StateAliasDeath);

		/*m_StateAliasDeath.BindState(&m_StateMove);
		m_StateAliasDeath.BindState(&m_StateAttack);
		m_StateAliasDeath.BindState(&m_StateIdle);*/

		SetInitialState("Idle");

		GameObject* pGameObject = pOwner->GetOwner();
		m_pAnimationComponent = (AnimationComponent*)pGameObject->GetComponent<AnimationComponent>("AnimationComponent");
		m_pMovementComponent = (MovementComponent*)pGameObject->GetComponent<MovementComponent>("MovementComponent");

		m_bMirror = false;
		m_bAnimationComplete = false;
		m_bDeath = false;
	}
	virtual ~FSMCharacter()
	{

	}

	StateMove m_StateMove;
	StateDeath m_StateDeath;
	StateIdle m_StateIdle;
	//TransitionDeath m_TransitionToDeath;

	// Death상태로 가는 공통 Transition을 처리한다.
	//FSMStateAlias m_StateAliasDeath;


	AnimationComponent* m_pAnimationComponent;
	MovementComponent* m_pMovementComponent;

	Vector2D m_moveDirection;
	Vector2D m_prevDirection;
	bool m_bAnimationComplete;
	bool m_bMirror;
	bool m_bDeath;
	virtual void Update(float DeltaTime) override;
};

