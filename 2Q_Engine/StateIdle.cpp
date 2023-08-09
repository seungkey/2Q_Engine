#include "pch.h"
#include "StateIdle.h"
#include "FSMCharacter.h"

void StateIdle::Enter()
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation("Idle", pFSMCharacter->m_bMirror, true);
	pAnimationComponent->SetFrameIndex(0);
}

void StateIdle::Update(float dt)
{
}

void StateIdle::Exit()
{
}

bool StateIdle::CheckTransition(string& NextState)
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	if (pFSMCharacter->m_moveDirection.x != 0.0f || pFSMCharacter->m_moveDirection.y != 0.0f)
	{
		NextState = "Move";
		return true;
	}
	if (pFSMCharacter->m_bDeath)
	{
		NextState = "Death";
		return true;
	}
	return false;
}
