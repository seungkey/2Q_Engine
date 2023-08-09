#include "pch.h"
#include "PlayerObject.h"

#include "AnimationComponent.h"
#include "FSMComponent.h"
#include "FSM.h"
#include "FSMCharacter.h"

PlayerObject::PlayerObject()
{
	m_pMovementComponent = AddComponent<MovementComponent>("MovementComponent");
	m_pMovementComponent->SetSpeed(100.f);

	m_pAnimationComponent = AddComponent<AnimationComponent>("AnimationComponent");
	m_pAnimationComponent->SetAnimationAsset(std::wstring(L"../Resource/testLoadAsset.txt"));

	m_pFSMComponent = AddComponent<FSMComponent>("FSMComponent");
	m_pFSMCharacter = m_pFSMComponent->CreateFiniteStateMachine<FSMCharacter>();
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::Update(float dt)
{
	Vector2D Location, Direction{ 0.f,0.f };
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { //왼쪽
		Direction.x = -1.0f;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //오른쪽
		Direction.x = 1.0f;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) { //위
		Direction.y = 1.0f;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //아래
		Direction.y = -1.0f;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_pFSMCharacter->m_bDeath = true;
	}
	__super::Update(dt);
}


