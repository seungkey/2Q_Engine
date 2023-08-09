#pragma once
#include "TransformComponent.h"
#include "Component.h"

class Input;

class MovementComponent :
    public TransformComponent
{
private:
  
    Vector2D m_move;
    float m_moveSpeed;
    float m_jumpPower;
    float m_dashSpeed;

public:
    MovementComponent(GameObject* pOwner, string name, TransformComponent* pRoot)
        :TransformComponent(pOwner, name, pRoot), 
        m_moveSpeed(0),
        m_jumpPower(0),
        m_dashSpeed(0) {}
    ~MovementComponent() {}

    Vector2D Move(Vector2D vec);
    Vector2D Jump();
    Vector2D Dash(Vector2D vec);

    void SetMoveSpeed(float moveSpeed) { m_moveSpeed = moveSpeed; }
    void SetDashSpeed(float dashSpeed) { m_dashSpeed = dashSpeed; }
    void SetJumpPower(float jumpPower) { m_jumpPower = jumpPower; }
    

    void AddLocation();
    
    Vector2D GetDirection() { return m_move; }
};

