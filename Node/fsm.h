#ifndef FSM_H
#define FSM_H

#include <iostream>
#include <string>
#include <vector>

#include "token.h"

using namespace std;

class FSM
{
public:
    FSM();

    virtual int nextState(int currentState, char c, char next);
    Token *run(stringstream *input, int col); // for test

    vector <int> states;
    int initialState;
    int endState;
    vector <int> acceptingStates;
};

#endif // FSM_H
