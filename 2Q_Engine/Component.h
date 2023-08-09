//Component �߿� �ֻ��� Ŭ����

#pragma once

#include "BaseObject.h"

class GameObject;


class Component :
    public BaseObject
{
public:
    Component(GameObject* pOwner, string name);
    virtual ~Component();

public:
    void SetName(string name) { m_name = name; }
    const string& GetName() const { return m_name; }
    void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
    GameObject* GetOwner() { return m_pOwner; }
    virtual void Update(float dt) = 0;
    virtual bool Initialize() override;

    
protected:
    string m_name;
    GameObject* m_pOwner;
};

