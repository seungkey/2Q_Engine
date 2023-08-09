#pragma once
#include "RenderComponent.h"
class BoxComponent :
	public RenderComponent
{
public:
	BoxComponent(GameObject* pOwner, const string name, TransformComponent* pRoot)
		:RenderComponent(pOwner, name, pRoot),
		m_color({ 0,255,0,1 })
	{
		
	}
	virtual ~BoxComponent() final{}

private:
	int height = 100;
	int width = 100;
	D2D1_COLOR_F m_color;
public:
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) final;
	virtual void Update(float dt) final;
	virtual bool Initialize() final;
	void SetHeight(int height) { this->height = height; }
	void SetWidth(int width) { this->width = width; }

	void SetColor(D2D1_COLOR_F color);

};

