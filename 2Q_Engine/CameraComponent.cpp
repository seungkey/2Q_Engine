#include "pch.h"
#include "CameraComponent.h"

CameraComponent::CameraComponent(GameObject* pOwner, string name, TransformComponent* pRoot)
	: TransformComponent(pOwner, name, pRoot)
	, m_inversedTransform{}
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Update(float dt)
{
	__super::Update(dt);
	m_inversedTransform = m_worldTransform;
	D2D1InvertMatrix(&m_inversedTransform);
}

bool CameraComponent::Initialize()
{
	return false;
}
