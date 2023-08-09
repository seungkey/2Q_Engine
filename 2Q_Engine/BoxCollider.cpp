#include "pch.h"
#include "BoxCollider.h"

#include "D2DRenderer.h"

BoxCollider::BoxCollider(GameObject* pOwner, string Name, TransformComponent* pRoot)
	:Collider(pOwner,Name,pRoot),
	m_widthVector(0, 0),
	m_heightVector(0, 0),
	m_color(RGB(255, 0, 0))

{
}
BoxCollider::~BoxCollider()
{
	if (!m_vertex.empty())
	{
		m_vertex.erase(m_vertex.begin(), m_vertex.end());
	}
	m_vertex.clear();
}
void BoxCollider::Update(float dt)
{
	m_centerPos = m_pParentComponent->GetRelativeTranslation();
	SetVertex();
	SetAxis();
	if (((int)this->m_pParentComponent->GetRelativeRotation() % 90) <= 0)
	{
		m_colliderType = ColliderType::AABB;
	}
	else
	{
		m_colliderType = ColliderType::OBB;
	}
}

void BoxCollider::SetAxis()
{
	m_widthVector = { m_vertex[0].x - m_vertex[1].x,m_vertex[0].y - m_vertex[1].y };
	m_heightVector = { m_vertex[1].x - m_vertex[2].x,m_vertex[1].y - m_vertex[2].y };
	
	m_widthVector.Normalize();
	m_heightVector.Normalize();
}

void BoxCollider::SetVertex()
{
	m_vertex[0] = Vector2D(- m_extends.x, - m_extends.y);
	m_vertex[1]= Vector2D( m_extends.x, - m_extends.y);
	m_vertex[2] = Vector2D( m_extends.x,  m_extends.y);
	m_vertex[3]= Vector2D( - m_extends.x,  m_extends.y);

	D2D1_MATRIX_3X2_F transform = m_pParentComponent->GetWorldTransform();

	m_vertex[0] = { m_vertex[0].x * transform._11 + m_vertex[0].y * transform._21+ transform._31,m_vertex[0].x * transform._12 + m_vertex[0].y * transform._22+ transform._32 };
	m_vertex[1] = { m_vertex[1].x * transform._11 + m_vertex[1].y * transform._21+ transform._31,m_vertex[1].x * transform._12 + m_vertex[1].y * transform._22 + transform._32};
	m_vertex[2] = { m_vertex[2].x * transform._11 + m_vertex[2].y * transform._21+ transform._31,m_vertex[2].x * transform._12 + m_vertex[2].y * transform._22 + transform._32 };
	m_vertex[3] = { m_vertex[3].x * transform._11 + m_vertex[3].y * transform._21+ transform._31,m_vertex[3].x * transform._12 + m_vertex[3].y * transform._22 + transform._32 };
}

