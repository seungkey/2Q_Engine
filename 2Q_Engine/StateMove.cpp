#include "pch.h"
#include "StateMove.h"
#include "FSMCharacter.h"

void StateMove::Enter()
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;

	if (pFSMCharacter->m_moveDirection.x > 0)
	{
		pFSMCharacter->m_bMirror = false;

	}
	else if (pFSMCharacter->m_moveDirection.x < 0)
	{
		pFSMCharacter->m_bMirror = true;

	}
	pAnimationComponent->SetAnimation("Move", pFSMCharacter->m_bMirror, true);
	pAnimationComponent->SetFrameIndex(0);
}

void StateMove::Update(float dt)
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	if (pFSMCharacter->m_prevDirection.x != pFSMCharacter->m_moveDirection.x)
	{
		AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
		if (pFSMCharacter->m_moveDirection.x > 0)
		{
			pFSMCharacter->m_bMirror = false;

		}
		else if (pFSMCharacter->m_moveDirection.x < 0)
		{
			pFSMCharacter->m_bMirror = true;
		}
		pAnimationComponent->SetReverse(pFSMCharacter->m_bMirror);
	}
}

void StateMove::Exit()
{
}

bool StateMove::CheckTransition(string& NextState)
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	if (pFSMCharacter->m_moveDirection.x == 0.0f && pFSMCharacter->m_moveDirection.y == 0.0f)
	{
		NextState = "Idle";
		return true;
	}
    return false;
}
