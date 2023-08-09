//�ֻ��� ������Ʈ
//������Ʈ�� ���� ������Ʈ�� �̰� ��� ����

#pragma once

class Collider;

class BaseObject
{
public:
	BaseObject() {}
	virtual ~BaseObject() {}

	virtual bool Initialize() = 0; //�ʱ�ȭ�� ������Ʈ�� ��밡������Ȯ���Ѵ�.
	virtual void Update(float dt) = 0;	//������Ʈ�� ���¸� ������Ʈ�Ѵ�.

	virtual void OnCollisionEnter(Collider& other){}
	virtual void OnCollisionStay(Collider& other) {}
	virtual void OnCollisionExit(Collider& other) {}
	//virtual void FixedUpdate(float elapsedTime) = 0;
};

