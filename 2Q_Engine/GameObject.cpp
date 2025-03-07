#include "pch.h"
#include "GameObject.h"

#include "Component.h"
#include "AnimationComponent.h"
#include "BoxComponent.h"
#include "MovementComponent.h"
#include "World.h"

GameObject::GameObject()
	: BaseObject()
{
	m_pRootComponent = AddComponent<TransformComponent>("Transform");
}

GameObject::~GameObject()
{
	for (auto& component : m_pComponents)
	{
		delete component;
	}
	m_pComponents.clear();
}

bool GameObject::Initialize()
{
	for (auto& component : m_pComponents)
	{
		if (!component->Initialize())
		{
			return false;
		}
	}
	return true;
}

void GameObject::Update(float dt)
{
	for (auto& component : m_pComponents)
	{
		component->Update(dt);
	}
}

void GameObject::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto& component : m_pComponents)
	{
		if (!dynamic_cast<RenderComponent*>(component))
			continue;
		dynamic_cast<RenderComponent*>(component)->Render(pRenderTarget);
	}
}
