#pragma once
#include "TransformComponent.h"
class Resource;
class GameObject;
class CameraObject;
class World
{
public:
	static D2D1_MATRIX_3X2_F m_cameraTransform;
private:
	vector<GameObject*> m_gameObjects;
	Resource* m_pRes;
	CameraObject* m_pCameraObject;
public:
	template <typename T>
	T* CreateGameObject()
	{
		bool bIsGameObject = is_base_of<GameObject, T>::value;
		assert(bIsGameObject);
		T* newObject = new T();
		newObject->SetOwnerWorld(this);
		m_gameObjects.push_back(newObject);
		return newObject;
	}
	
	D2D1_MATRIX_3X2_F GetCameraTransform() { return m_cameraTransform; }
	void Initialize();
	void Update(float dt);
	void Render(ID2D1HwndRenderTarget* pRenderTarget);
	void Enter();
	void Exit();
public:
	World();
	~World();

	void LoadWorld(string _path);
	void SaveWorld(string _path);

};

