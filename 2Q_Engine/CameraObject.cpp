#include "pch.h"
#include "CameraObject.h"

#include "CameraComponent.h"
#include "BoxComponent.h"
#include "MovementComponent.h"
#include "BoxCollider.h"

CameraObject::CameraObject()
	: GameObject()
	, m_cameraTransform{}
	, m_pCameraComponent(nullptr)
{
	m_pCameraComponent = AddComponent<CameraComponent>("CameraComponent");
	AddComponent<MovementComponent>("MovementComponent");
	GetComponent<MovementComponent>("MovementComponent")->SetMoveSpeed(100.f);
	AddComponent<BoxComponent>("BoxComponent");
	AddComponent<BoxCollider>("BoxCollider");
}

CameraObject::~CameraObject()
{
}

void CameraObject::Update(float dt)
{
	__super::Update(dt);

	m_cameraTransform = m_pCameraComponent->GetInversedTransform();
}

bool CameraObject::Initialize()
{
	return false;

}

