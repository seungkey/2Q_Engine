#include "pch.h"
#include "Ground.h"
#include "TransformComponent.h"
#include "BoxCollider.h"
#include "BoxComponent.h"


bool Ground::Initialize()
{
	

	return false;
}

void Ground::SetCollider(Vector2D centerPos, Vector2D extends)
{
	AddComponent<TransformComponent>("TransformComponent");
	m_pRootComponent->SetRelativeTranslation(centerPos);

	AddComponent<BoxComponent>("BoxComponent");
	GetComponent<BoxComponent>("BoxComponent")->SetWidth(extends.x);
	GetComponent<BoxComponent>("BoxComponent")->SetHeight(extends.y);

	m_boxCollider = AddComponent<BoxCollider>("BoxCollider");
	m_boxCollider->SetExtends(extends.x, extends.y);
	m_boxCollider->SetCollisionType(CollisionType::BLOCK);
}
