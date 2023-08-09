#include "pch.h"
#include "CollisionManager.h"

#include "AABB.h"
#include "BoxCollider.h"
#include "OBB.h"
#include "GameObject.h"
#include "RigidBody.h"


CollisionManager::CollisionManager()
	:m_playerBox(nullptr),
	m_otherBoxes()
{
	aabb = new AABB;
	obb = new OBB;
}

CollisionManager::~CollisionManager()
{
	delete aabb;
	delete obb;
}

void CollisionManager::BoxCollision(BoxCollider& player, BoxCollider& other)
{
	bool bIsCollision = false;
	if (player.GetColliderType() == ColliderType::OBB || other.GetColliderType() == ColliderType::OBB)
	{
		if (obb->Intersect(player, other))
		{
			bIsCollision = true;
		}
		else
		{
			bIsCollision = false;
		}
	}
	else
	{
		if (aabb->Intersect(player, other))
		{
			bIsCollision = true;
		}
		else
		{
			bIsCollision = false;
		}
	}
	if (bIsCollision)
	{
		if (player.GetCollision())
		{
			player.GetOwner()->OnCollisionStay(other);
			other.GetOwner()->OnCollisionStay(player);
			player.GetOwner()->GetRootComponent()->AddRelativeTranslation(aabb->GetDifference());
			if (aabb->GetDifference().x == 0) {
				player.GetOwner()->GetComponent<RigidBody>("RigidBody")->SetGravity(0);
				
			}
		}
		else
		{
			player.GetOwner()->GetComponent<RigidBody>("RigidBody")->SetVelocity(Vector2D(0, 0));
			player.GetOwner()->OnCollisionEnter(other);
			other.GetOwner()->OnCollisionEnter(player);
			player.SetCollision(bIsCollision);
			other.SetCollision(bIsCollision);
		}
	}
	else
	{
		if (player.GetCollision()&&other.GetCollision())
		{
			player.GetOwner()->OnCollisionExit(other);
			other.GetOwner()->OnCollisionExit(player); 
			player.SetCollision(bIsCollision);
		}
			other.SetCollision(bIsCollision);
	}
}

void CollisionManager::Update()
{
	for (int i = 0; i < m_otherBoxes.size(); i++)
	{
		BoxCollision(*m_playerBox, *m_otherBoxes[i]);
	}
}

void CollisionManager::AddCollider(BoxCollider* boxCollider)
{
	m_otherBoxes.push_back(boxCollider);
}

void CollisionManager::SetPlayerCollider(BoxCollider* playerCollider)
{
	m_playerBox = playerCollider;
}


