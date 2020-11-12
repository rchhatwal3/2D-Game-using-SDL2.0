#include "../Includes/StateMachine.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::setPlayerState(States new_state)
{
    currentState = new_state;
}

StateMachine::States StateMachine::getPlayerState()
{
    return currentState;
}