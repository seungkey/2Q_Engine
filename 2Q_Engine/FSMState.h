#pragma once

class FSM;
class FSMTransition;
class FSMState abstract
{
public:
	FSMState(FSM* pOwner, string name)
		: m_pOwner(pOwner)
		, m_name(name)
	{}

	virtual ~FSMState() {}
protected:
	FSM* m_pOwner;
	string m_name;

	vector<FSMTransition*> m_transitions;
public:
	void SetOwner(FSM* pOwner) { m_pOwner = pOwner; }

	const string& GetName() { return m_name; }


	virtual void Enter() = 0;
	virtual void Update(float dt) = 0;
	virtual void Exit() = 0;

	virtual bool CheckTransition(string& nextState);
};

