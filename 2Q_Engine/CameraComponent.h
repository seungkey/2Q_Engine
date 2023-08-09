#pragma once
#include "TransformComponent.h"
class CameraComponent :
    public TransformComponent
{
public:
    CameraComponent(GameObject* pOwner, string name, TransformComponent* pRoot);
    virtual ~CameraComponent() override;

private:
    D2D1_MATRIX_3X2_F m_inversedTransform;

public:
    virtual void Update(float dt) override;
    virtual bool Initialize() override;

    D2D1_MATRIX_3X2_F GetInversedTransform()
    {
        return m_inversedTransform;
    }
};

