#include "pch.h"
#include "FSMCharacter.h"


void FSMCharacter::Update(float DeltaTime)
{
	assert(m_pMovementComponent != nullptr);
	m_prevDirection = m_moveDirection;
	m_moveDirection = m_pMovementComponent->GetDirection();


	FSM::Update(DeltaTime);
}
