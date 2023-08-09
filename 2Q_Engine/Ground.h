#pragma once
#include "GameObject.h"
class BoxCollider;
class BoxComponent;

class Ground :
    public GameObject
{
private:
    BoxCollider* m_boxCollider;
    BoxComponent* m_boxComponent;

public:
    virtual bool Initialize() override;

    void SetCollider(Vector2D centerPos, Vector2D extends);
    BoxCollider* GetCollider() { return m_boxCollider; }
};

