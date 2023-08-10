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
	m_pRootComponent->SetRelativeTranslation(Vector2D(100,100));
	//GetComponent<TransformComponent>("TransformComponent")->SetRelativeTranslation(Vector2D(100, 100));
	AddComponent<BoxComponent>("BoxComponent");
	GetComponent<BoxComponent>("BoxComponent")->SetWidth(50);
	GetComponent<BoxComponent>("BoxComponent")->SetHeight(50);
	
	m_movementComponent = AddComponent<MovementComponent>("MovementComponent");
	m_movementComponent->SetMoveSpeed(100);
	m_movementComponent->SetDashSpeed(300);
	m_movementComponent->SetJumpPower(800);

	m_boxCollider = AddComponent<BoxCollider>("BoxCollider");
	m_boxCollider->SetExtends(50, 50);

	m_rigidBody = AddComponent<RigidBody>("RigidBody");
	m_rigidBody->SetGravity(10);

	return false;
}

void Player::Update(float dt)
{
	__super::Update(dt);
	Vector2D direction = m_rigidBody->GetVelocity();
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

Vector2D Player::ModificationVector(Collider& other)
{
	Vector2D thisMinVector = m_boxCollider->GetMinColliderVector();
	Vector2D thisMaxVector = m_boxCollider->GetMaxColliderVector();
	Vector2D otherMinVector = other.GetMinColliderVector();
	Vector2D otherMaxVector = other.GetMaxColliderVector();

	if (thisMaxVector.y >= otherMinVector.y && thisMaxVector.y <= otherMinVector.y+(other.GetExtends().y*0.2))
	{
		return { 0,-thisMaxVector.y + otherMinVector.y };
	}
	if (thisMinVector.x <= otherMaxVector.x && thisMinVector.x >= otherMaxVector.x-(other.GetExtends().x * 0.2))
	{
		return {otherMaxVector.x-thisMinVector.x,0};
	}
	if(thisMaxVector.x>=otherMinVector.x&&thisMaxVector.x<=otherMinVector.x+(other.GetExtends().x*0.2))
	{
		return { otherMinVector.x - thisMaxVector.x,0 };
	}
	return { 0,0 };
}



void Player::OnCollisionEnter(Collider& other)
{
	if (other.GetCollisionType() == CollisionType::BLOCK)
	{
		//if()
		
		//m_rigidBody->SetVelocity({ 0,0 });
		
		m_pRootComponent->AddRelativeTranslation(ModificationVector(other));
		if (abs(ModificationVector(other).y) > 0)
		{
			m_rigidBody->SetGravity(0);
			m_rigidBody->SetYVelocity(0);
		}
		
		m_pRootComponent->AddRelativeTranslation(ModificationVector(other));
	}
}

void Player::OnCollisionStay(Collider& other)
{
	if (other.GetCollisionType() == CollisionType::BLOCK)
	{
		if (abs(ModificationVector(other).y) > 0)
		{
			m_rigidBody->SetGravity(0);
			m_rigidBody->SetYVelocity(0);
		}
		
		m_pRootComponent->AddRelativeTranslation(ModificationVector(other)); 
	}
}

void Player::OnCollisionExit(Collider& other)
{
	if (other.GetCollisionType() == CollisionType::BLOCK)
	{
		if (other.GetMinColliderVector().y >= m_boxCollider->GetMaxColliderVector().y) {
			m_rigidBody->SetGravity(10);

		}
		//m_rigidBody->SetVelocity(Vector2D(0, 0));
	}
}
