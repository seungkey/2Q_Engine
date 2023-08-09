#include "pch.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent(GameObject* pOwner, const string& Name, TransformComponent* pRoot)
	: TransformComponent(pOwner,Name,pRoot)
	, m_renderingOrder(0)	, m_bVisible(true)
{
}

RenderComponent::~RenderComponent()
{
}
 