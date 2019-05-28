#include "numberfsm.h"

NumberFSM::NumberFSM()
{
    states.push_back(NumberStates::Initial);
    states.push_back(NumberStates::Integer);
    states.push_back(NumberStates::BeginNumberWithFractionalPart);
    states.push_back(NumberStates::NumberWithFractionalPart);

    initialState = NumberStates::Initial;
    endState = NumberStates::NoNextState;

    acceptingStates.push_back(NumberStates::Integer);
    acceptingStates.push_back(NumberStates::NumberWithFractionalPart);
    acceptingStates.push_back(NumberStates::NumberWithExponent);
}

int NumberFSM::nextState(int currentState, char c, char next)
{
    switch (currentState) {
    case NumberStates::Initial:
        if (isdigit(c)) {
            return NumberStates::Integer;
        }

        break;

    case NumberStates::Integer:
        if (isdigit(c)) {
            return NumberStates::Integer;
        }

        if (c == '.') {
            if(next == '.')
            {
                break; // ..
            }
            return NumberStates::BeginNumberWithFractionalPart;
        }

        if (tolower(c) == 'e') {
            return NumberStates::BeginNumberWithExponent;
        }

        break;

    case NumberStates::BeginNumberWithFractionalPart:
        if (isdigit(c)) {
            return NumberStates::NumberWithFractionalPart;
        }

        break;

    case NumberStates::NumberWithFractionalPart:
        if (isdigit(c)) {
            return NumberStates::NumberWithFractionalPart;
        }

        if (tolower(c) == 'e') {
            return NumberStates::BeginNumberWithExponent;
        }

        break;

    case NumberStates::BeginNumberWithExponent:
        if (c == '+' || c == '-'){
            return NumberStates::BeginNumberWithSignedExponent;
        }

        if (isdigit(c)) {
            return NumberStates::NumberWithExponent;
        }

        break;

    case NumberStates::BeginNumberWithSignedExponent:
        if (isdigit(c)) {
            return NumberStates::NumberWithExponent;
        }

        break;

    case NumberStates::NumberWithExponent:
        if (isdigit(c)) {
            return NumberStates::NumberWithExponent;
        }

        break;

    default:
        break;
    }

    return NumberStates::NoNextState;
}
