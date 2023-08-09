#include "pch.h"
#include "DemoObject.h"

#include "BoxComponent.h"
#include "BoxCollider.h"
#include "World.h"

DemoObject::DemoObject()
    :GameObject()
{
    AddComponent<BoxComponent>("BoxComponent");
    AddComponent<BoxCollider>("BoxCollider");
    m_pRootComponent->SetRelativeTranslation({ 100.f,100.f });
}





void DemoObject::Update(float dt)
{
   __super::Update(dt);
}

bool DemoObject::Initialize()
{
    //m_pRootComponent->SetParentTransformComponent(m_pWorld->GetCameraTransform());
    return true;
}
