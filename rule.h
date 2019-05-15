#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>

using namespace std;

class Rule
{
public:
    Rule();


    string left;
    vector <string> right;
    size_t dot_pos;
};

#endif // RULE_H
