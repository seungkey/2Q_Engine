#pragma once
#include "GameObject.h"

class AnimationComponent;
class MovementComponent;
class FSMComponent;
class FSMCharacter;
class TextComponent;
class CameraComponent;
class BoxComponent;
class PlayerObject :
    public GameObject
{
public:
	PlayerObject();
	virtual ~PlayerObject();

	MovementComponent* m_pMovementComponent;
	FSMComponent* m_pFSMComponent;
	AnimationComponent* m_pAnimationComponent;
	FSMCharacter* m_pFSMCharacter;
public:

	virtual void Update(float dt) override;

	


};

