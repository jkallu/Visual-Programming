#include "fsm.h"
#include <ctype.h>

#include <sstream>

FSM::FSM()
{

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

Token * FSM::run(stringstream* input, int col)
{
    string val = "";

    int currentState = initialState;

    char c;
    while (!input->eof())
    {
        input->get(c);

        int next_state = nextState(currentState, c);

        cout << next_state << endl;

        if(next_state == endState)
        {
            input->unget();
            break;
        }

        val += c;
        col ++;

        currentState = next_state;
    }

    return new Token(TokenType::Identifier, val, 0, col);
}
