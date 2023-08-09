#include "pch.h"
#include "BoxComponent.h"

#include "D2DRenderer.h"
#include "GameObject.h"
#include "World.h"
//#include "CameraComponent.h"
#include "CameraObject.h"
void BoxComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	ID2D1SolidColorBrush* pBrush = D2DRenderer::m_instance->GetBrush();
	
	pBrush->SetColor(m_color);
	

	
	D2D1_RECT_F rect = { -width, -height, width, height };
	pRenderTarget->SetTransform(m_worldTransform);
	pRenderTarget->DrawRectangle(rect, pBrush);
}

void BoxComponent::Update(float dt)
{
	__super::Update(dt);
	D2D1_MATRIX_3X2_F transform;
	if (m_pParentComponent != nullptr)
	{
		m_worldTransform = m_relativeTransform * m_pParentComponent->GetWorldTransform();
		if (!dynamic_cast<CameraObject*>(m_pOwner))
		{
			m_worldTransform = m_worldTransform;// *World::m_cameraTransform;
		}
	}
	else
	{
		m_worldTransform = m_relativeTransform;
	}
}

bool BoxComponent::Initialize()
{
	return false;
}

void BoxComponent::SetColor(D2D1_COLOR_F color)
{
	 m_color = color; 
}
