#pragma once
#include "Collider.h"

class BoxCollider :
    public Collider
{
private:

    vector<Vector2D> m_vertex = { {0,0},{0,0} ,{0,0} ,{0,0} };
    //�浹 Ȯ���� ���� �ӽ÷� �� �߰�
    COLORREF m_color;

public:
    Vector2D m_widthVector;
    Vector2D m_heightVector;
    BoxCollider(GameObject* pOwner, string Name, TransformComponent* pRoot);
    ~BoxCollider();
    virtual void Update(float dt) override;
    
    
    void SetAxis();

    void SetVertex();
    vector<Vector2D>& GetVertex() { return m_vertex; }
    
    virtual void OnCollisionEnter(Collider& other) {}
    virtual void OnCollisionStay(Collider& other) {}
    virtual void OnCollisionExit(Collider& other) {}
};

