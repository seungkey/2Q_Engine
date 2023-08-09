#include "pch.h"
#include "BitmapComponent.h"

#include "D2DRenderer.h"

void BitmapComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	D2D1_MATRIX_3X2_F transform;
	if (m_pParentComponent != nullptr)
	{
		transform = m_relativeTransform * m_worldTransform;
	}
	else
	{
		transform = m_relativeTransform;
	}

	pRenderTarget->SetTransform(transform);
	pRenderTarget->DrawBitmap(m_pBitmap, m_destRect);
}

void BitmapComponent::SetBitmap(const wstring bitmapKey)
{
	m_pBitmap = D2DRenderer::m_instance->CreateBitmapFromFile(bitmapKey);
	D2D1_SIZE_F size = m_pBitmap->GetSize();
	m_destRect.bottom = -size.height / 2;
	m_destRect.top = size.height / 2;
	m_destRect.left = -size.width / 2;
	m_destRect.right = size.width / 2;
}
