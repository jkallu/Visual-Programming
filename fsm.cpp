#include "fsm.h"
#include <ctype.h>
#include "token.h"

FSM::FSM(int sts[], int initState, int acceptState[])
{
    int num_states = sizeof (sts) / sizeof (int);

    for(int i = 0; i < num_states; i++)
    {
        cout << sts[i] << endl;
    }
}

int FSM::nextState(int currentState, char c)
{
    switch (currentState)
    {
        case 1:
            if(isalpha(c) || c == '_')
            {
                return 2;
            }
        break;
        case 2:
            if(isalpha(c) || isdigit(c) || c == '_')
            {
                return 2;
            }
        break;
    }

    return TokenType::EndOfInput;
}

void FSM::run(string input)
{
    int currentState = initialState;

    for (int i = 0; i < input.length(); i++)
    {
        char c = input.at(i);
        int nectState = nextState(currentState, c);
        
        
    }
}

FSM::~FSM()
{

}
