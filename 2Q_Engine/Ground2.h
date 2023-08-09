#pragma once
#include "GameObject.h"
class BoxCollider;
class BoxComoponent;

class Ground2 :
    public GameObject
{
public:
    BoxCollider* m_boxCollider;
    virtual bool Initialize() override;

};

