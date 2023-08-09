#pragma once
#include "Component.h"


class GameObject;
class TransformComponent :
    public Component
{
public:

protected:
    TransformComponent* m_pParentComponent; // �θ� ������Ʈ�� �ּ�

    Vector2D m_relativeScale; // ��� ũ��
    float m_relativeRotation; // ��� ȸ��
    Vector2D m_relativeTranslation; // ��� ��ġ

    D2D1_MATRIX_3X2_F m_relativeTransform; // �� ������Ʈ���� Ʈ������
    D2D1_MATRIX_3X2_F m_worldTransform; // �������� Ʈ������

public:
    TransformComponent(GameObject* pOwner, string Name, TransformComponent* pRoot);
    virtual ~TransformComponent() override;

    virtual bool Initialize() override;
    virtual void Update(float dt) override;

    void SetRelativeScale(const Vector2D& obj) { m_relativeScale = obj; }
    Vector2D& GetRelativeScale() { return m_relativeScale; }
    void AddRelativeScale(const Vector2D& obj) { m_relativeScale += obj; }

    void SetRelativeRotation(const float degree) { m_relativeRotation = degree; }
    float& GetRelativeRotation() { return m_relativeRotation; }
    void AddRelativeRotation(const float degree) { m_relativeRotation += degree; }

    void SetRelativeTranslation(const Vector2D& obj) { m_relativeTranslation = obj; }
    Vector2D& GetRelativeTranslation() { return m_relativeTranslation; }
    void AddRelativeTranslation(const Vector2D& obj) { m_relativeTranslation += obj; }

    void SetParentTransform(TransformComponent* pParent) { m_pParentComponent = pParent; }

    D2D1_MATRIX_3X2_F& GetWorldTransform() { return m_worldTransform; }
};

