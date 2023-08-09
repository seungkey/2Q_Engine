#include "pch.h"
#include "Player.h"

#include "BoxCollider.h"
#include "BoxComponent.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include "RigidBody.h"
#include "Input.h"

Player::~Player()
{
}

bool Player::Initialize()
{
	AddComponent<TransformComponent>("TransformComponent");
	GetComponent<TransformComponent>("TransformComponent")->SetRelativeTranslation(Vector2D(100, 100));
	AddComponent<BoxComponent>("BoxComponent");
	GetComponent<BoxComponent>("BoxComponent")->SetWidth(50);
	GetComponent<BoxComponent>("BoxComponent")->SetHeight(50);
	
	m_movementComponent = AddComponent<MovementComponent>("MovementComponent");
	m_movementComponent->SetMoveSpeed(100);
	m_movementComponent->SetDashSpeed(300);
	m_movementComponent->SetJumpPower(500);

	m_boxCollider = AddComponent<BoxCollider>("BoxCollider");
	m_boxCollider->SetExtends(50, 50);

	m_rigidBody = AddComponent<RigidBody>("RigidBody");
	m_rigidBody->SetGravity(100);

	return false;
}

void Player::Update(float dt)
{
	__super::Update(dt);
	Vector2D direction = { 0,0 };
	if (Input::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::HOLD) 
	{
		direction += m_movementComponent->Move(Vector2D(-1, 0));
	}
	else if (Input::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		direction += m_movementComponent->Move(Vector2D(1, 0));
	}
	if(Input::GetInstance()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
   		direction += m_movementComponent->Jump();
	}
	if (m_rigidBody->IsAffectedGravity())
	{
 		direction += {0, m_rigidBody->GetGravity()* m_rigidBody->GetMass()* GRAVITY};
	}
	m_rigidBody->SetVelocity(direction);
 }



void Player::OnCollisionEnter(Collider& other)
{
	if (other.GetCollisionType() == CollisionType::BLOCK)
	{
		
	}
}

void Player::OnCollisionStay(Collider& other)
{
	m_rigidBody->SetGravity(0);
	//m_rigidBody->SetVelocity({ 0,0 });
}

void Player::OnCollisionExit(Collider& other)
{
	if (other.GetCollisionType() == CollisionType::BLOCK)
	{
		m_rigidBody->SetGravity(100);
		//m_rigidBody->SetVelocity(Vector2D(0, 0));
	}
}
