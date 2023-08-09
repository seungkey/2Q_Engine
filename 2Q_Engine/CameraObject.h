#pragma once
#include "GameObject.h"

class CameraComponent;
class CameraObject :
    public GameObject
{
public:
    CameraObject();
    virtual ~CameraObject() final;

    virtual void Update(float dt) final;
    virtual bool Initialize() final;

private:
    CameraComponent* m_pCameraComponent;
    D2D1_MATRIX_3X2_F m_cameraTransform;

public:
    D2D1_MATRIX_3X2_F GetCameraTransform() { return m_cameraTransform; }
};

