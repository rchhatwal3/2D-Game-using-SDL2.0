#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "CONSTANTS.h"

class StateMachine
{
private:
public:
    StateMachine();
    ~StateMachine();

    enum States 
    {
        IDLE,
        UP,
        DOWN,
        RIGHT,
        LEFT
    };

    States currentState;

    void setPlayerState(States new_state);
    States getPlayerState();
};




#endif