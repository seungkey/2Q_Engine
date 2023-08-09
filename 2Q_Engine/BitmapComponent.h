#pragma once
#include "RenderComponent.h"
class BitmapComponent :
    public RenderComponent
{
public:
	BitmapComponent(GameObject* pOwner, const string name, TransformComponent* pRoot)
		:RenderComponent(pOwner, name, pRoot), m_pBitmap(), m_destRect()
	{
	}

	virtual ~BitmapComponent() { }

public:
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	void SetBitmap(const wstring bitmapKey);

private:
	ID2D1Bitmap* m_pBitmap;
	D2D1_RECT_F m_destRect;
};

