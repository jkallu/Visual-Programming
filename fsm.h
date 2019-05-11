#ifndef FSM_H
#define FSM_H

#include <iostream>
#include <string>

using namespace std;

class FSM
{
public:
    FSM(int sts[] = {}, int initState = 0, int acceptState[] = {});
    ~FSM();

    int nextState(int currentState, char c);
    void run(string input); // for test

    int *states;
    int initialState;
    int *acceptingStates;
};

#endif // FSM_H
