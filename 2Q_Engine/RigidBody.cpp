#include "pch.h"
#include "RigidBody.h"

void RigidBody::Update(float dt)
{
	if (m_velocity.y > MAX_GRAVITY)
	{
		m_velocity.y = MAX_GRAVITY;
	}
	if (m_velocity.x > 100)
	{
		m_velocity.x = 100;
	}
	if (m_velocity.x < -100)
	{
		m_velocity.x = -100;
	}
	m_pParentComponent->AddRelativeTranslation(m_velocity/(1.0/dt));
}

bool RigidBody::IsAffectedGravity()
{
	if (m_gravity != 0)
		return true;
	return false;
}


