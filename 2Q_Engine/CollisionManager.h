#pragma once

class AABB;
class OBB;
class BoxCollider;

class CollisionManager
{
private:
	AABB* aabb;
	OBB* obb;

	BoxCollider* m_playerBox;
	vector<BoxCollider*> m_otherBoxes;
	


public:
	CollisionManager();
	~CollisionManager();
	
	void BoxCollision(BoxCollider& player, BoxCollider& other);
	void Update();
	void AddCollider(BoxCollider* boxCollider);
	void SetPlayerCollider(BoxCollider* playerCollider);
};

