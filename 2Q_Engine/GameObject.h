//게임 오브젝트
//컴포넌트들을 create해서 가짐

#pragma once

#include "BaseObject.h"
#include "Component.h"

class World;
class Component;
class TransformComponent;
class GameObject :
	public BaseObject
{
protected:
	World* m_pWorld; //이 오브젝트가 속한 월드
	string m_tag;
	TransformComponent* m_pRootComponent; // 오브젝트의 최상위에 있는 TransformComponent
	vector<Component*> m_pComponents; // 이 오브젝트가 가지고 있는 컴포넌트들 집합

public:
	GameObject();
	virtual ~GameObject() override;

	virtual bool Initialize();
	virtual void Update(float dt);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

    void SetOwnerWorld(World* world) { m_pWorld = world; }
	World* GetOwnerWorld() { return m_pWorld; }
    string GetTag() { return m_tag; }
    void SetTag(string _tag) { m_tag = _tag; }
	TransformComponent* GetRootComponent() { return m_pRootComponent; }
	template<typename T>
	T* AddComponent(string _name = 0)
	{
		bool bIsComponent = is_base_of<Component, T>::value;
		assert(bIsComponent);
		T* component = new T(this, _name, this->m_pRootComponent);
		m_pComponents.push_back(component);
		return component;
	}


    template <class T>
    T* GetComponent(string name)
    {
        for (auto& component : m_pComponents)
        {
            if (component->GetName() == name)
            {
                return dynamic_cast<T*>(component);
            }
        }
    }
};

