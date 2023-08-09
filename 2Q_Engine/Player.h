#pragma once
#include "GameObject.h"

class TransformComponent;
class MovementComponent;
class BoxCollider;
class Collider;
class RigidBody;

class Player :
    public GameObject
{
private:
    MovementComponent* m_movementComponent;
    RigidBody* m_rigidBody;

public:
    BoxCollider* m_boxCollider;
    Player() {}
    virtual ~Player();
    virtual bool Initialize() override;
    virtual void Update(float dt)override;

    virtual void OnCollisionEnter(Collider& other)override;
    virtual void OnCollisionStay(Collider& other)override;
    virtual void OnCollisionExit(Collider& other)override;
};

