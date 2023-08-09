#pragma once
#include "FSMState.h"
class StateDeath :
    public FSMState
{
public:
    StateDeath(FSM* pOwner)
        : FSMState(pOwner, "Death")
    {}
    virtual ~StateDeath() {}

public:
    virtual void Enter() override;
    virtual void Update(float dt) override;
    virtual void Exit() override;

    virtual bool CheckTransition(string& NextState) override;
};

