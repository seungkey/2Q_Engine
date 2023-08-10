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
	bool otherCollision = other.GetCollision();

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
		
		if (otherCollision)
		{
			player.GetOwner()->OnCollisionStay(other);
			other.GetOwner()->OnCollisionStay(player);
			return;
		}
		else
		{
			if (player.GetCollision())
			{
				player.GetOwner()->OnCollisionStay(other);
				other.SetCollision(bIsCollision);
				
				return;
			}
			else
			{
				player.GetOwner()->OnCollisionEnter(other);
				other.GetOwner()->OnCollisionEnter(player);
				player.SetCollision(bIsCollision);
				return;
			}
		}
	}
	else
	{
		if (otherCollision)
		{
			player.SetCollision(bIsCollision);
			player.GetOwner()->OnCollisionExit(other);
		}
			//player.GetOwner()->OnCollisionExit(other);
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


