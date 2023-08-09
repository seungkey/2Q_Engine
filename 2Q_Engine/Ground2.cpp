#include "pch.h"
#include "Ground2.h"
#include "TransformComponent.h"
#include "BoxCollider.h"
#include "BoxComponent.h"


bool Ground2::Initialize()
{
	AddComponent<TransformComponent>("TransformComponent");
	m_pRootComponent->SetRelativeTranslation(Vector2D(500, 350));
	

	AddComponent<BoxComponent>("BoxComponent");
	GetComponent<BoxComponent>("BoxComponent")->SetWidth(200);
	GetComponent<BoxComponent>("BoxComponent")->SetHeight(10);

	m_boxCollider = AddComponent<BoxCollider>("BoxCollider");
	m_boxCollider->SetExtends(200, 10);
	m_boxCollider->SetCollisionType(CollisionType::BLOCK);
	
	return false;
}
