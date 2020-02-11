#include "StateMachine.h"
#include <iostream>

#pragma region Class methods

void StateMachine::RemoveAllStates()
{
	while (!m_states.empty()) //removes items from the stack until it is empty
	{ 
		m_states.pop();
		std::cout << "POP" << std::endl;
	}
	std::cout << "STACK EMPTY" << std::endl;
}

StateReference &StateMachine::GetCurrentState()
{
	return this->m_states.top(); //return the last state from the top of the stack
}

void StateMachine::AddNewState(StateReference newState) //add new state to stack
{
	isAdded = true;
	m_newState = std::move(newState);
}

void StateMachine::ChangingState() //change the state
{
	if ((isRemoved == true) && !m_states.empty()) //if it is removed and the stack is not empty
	{
		m_states.pop(); //delete the state at the top of the stack
		isRemoved = false;
		nr_states--;
	}
	if (isAdded == true) //if it is added
	{
		if (!m_states.empty()) //if the stack is not empty
		{
				m_states.pop();
				nr_states--;
		}
		m_states.push(std::move(m_newState)); //add a new state
		m_states.top()->Initialization(); //initiate a new state
		isAdded = false;
		nr_states++;
		std::cout << "Stack contents: " << nr_states << std::endl;
	}
}

void StateMachine::DeleteState()
{
	isRemoved = true; //set the variable to delete the state
}

#pragma region endregion

#pragma region accesors

int StateMachine::GetNrOfStates() const
{
	return this->nr_states; //get the number of stack states
}

#pragma region endregion