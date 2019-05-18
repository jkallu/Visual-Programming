#include "rule.h"

Rule::Rule()
{
    dot_pos = 0;
    n = 0;
    //flagFinished = false;
}

bool Rule::isFinished()
{
    if(dot_pos < right.size())
    {
        return false;
    }

    return true;
}

string Rule::nextElement()
{
    if(dot_pos < right.size())
    {
        return right.at(dot_pos);
    }

    return "";
}

string Rule::lastElement()
{
    if(right.size() > 0)
    {
        return right.at(right.size() - 1);
    }

    return "";
}
