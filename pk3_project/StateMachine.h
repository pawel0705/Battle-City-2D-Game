#ifndef StateMachine_hpp
#define StateMachine_hpp

#include "ProgramState.h"

#include <memory>
#include <stack>

typedef std::unique_ptr<ProgramState> StateReference;

class StateMachine //state machine
{
	std::stack<std::unique_ptr<ProgramState>> m_states; //stack of states
	std::unique_ptr<ProgramState> m_newState; // intelligent indicator
	int nr_states = 0; //number of states
	bool isAdded = false;
	bool isRemoved = false;

public:
	StateMachine() = default;
	~StateMachine() = default;

	int GetNrOfStates() const; //get the number of states on the stack
	StateReference &GetCurrentState(); //take the current state
	void AddNewState(StateReference newState); //add a new state to the stack
	void ChangingState(); //change the state
	void DeleteState(); //remove from the stack
	void RemoveAllStates(); //release the whole stack
};

#endif