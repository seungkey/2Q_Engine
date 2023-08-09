#include "pch.h"
#include "StateDeath.h"
#include "FSMCharacter.h"

void StateDeath::Enter()
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation("Death", pFSMCharacter->m_bMirror, false);
	pAnimationComponent->SetFrameIndex(0);
}

void StateDeath::Update(float dt)
{
}

void StateDeath::Exit()
{
}

bool StateDeath::CheckTransition(string& NextState)
{
	return false;
}
