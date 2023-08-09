#pragma once
#include "GameObject.h"
class DemoObject :
	public GameObject
{
public:
	DemoObject();
	virtual ~DemoObject() override {}

	
	virtual void Update(float dt) override;
	virtual bool Initialize() override;
};