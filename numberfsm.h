#ifndef NUMBERFSM_H
#define NUMBERFSM_H

#include "fsm.h"

enum NumberStates {Initial,
            Integer,
            BeginNumberWithFractionalPart,
            NumberWithFractionalPart,
            BeginNumberWithExponent,
            BeginNumberWithSignedExponent,
            NumberWithExponent,
            NoNextState
           };

class NumberFSM : public FSM
{
public:
    NumberFSM();

    int nextState(int currentState, char c) override;

};

#endif // NUMBERFSM_H
