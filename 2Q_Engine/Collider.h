#pragma once
#include "TransformComponent.h"
enum class ColliderType
{
	AABB,
	OBB,
};

enum class CollisionType
{
	BLOCK,
	UNBLOCK
};

class Collider :
	public TransformComponent
{
protected:
	Vector2D m_centerPos = { 0,0 };
	Vector2D m_extends = { 0,0 };

	bool bCollision;                   //충돌유무

	ColliderType m_colliderType;        //충돌체크 타입(AABB,OBB)
	CollisionType m_collisionType;      //통과 가능 유무(Block,Unblock)


public:
	Collider(GameObject* pOwner, string Name, TransformComponent* pRoot)
		:TransformComponent(pOwner, Name, pRoot),
		bCollision(false),
		m_colliderType(ColliderType::OBB),
		m_collisionType(CollisionType::UNBLOCK)
	{}
	virtual ~Collider() {}

	virtual void Update(float dt) = 0;

	Vector2D GetCenterPos() { return m_centerPos; }
	void SetCenterPos(float x, float y) { m_centerPos = { x, y }; }

	Vector2D GetExtends() { return m_extends; }
	void SetExtends(float width, float height) {
		m_extends = { width ,height  };
	}

	void SetCollision(bool isCollision) { this->bCollision = isCollision; }
	bool GetCollision() { return bCollision; }

	ColliderType GetColliderType() { return m_colliderType; }
	
	CollisionType GetCollisionType() { return m_collisionType; }
	void SetCollisionType(CollisionType collisionType) { m_collisionType = collisionType; }
	
};

