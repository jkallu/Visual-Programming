#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>

using namespace std;

class Rule
{
public:
    Rule();
    bool isFinished();
    string nextElement();
    string lastElement();
    //void setFinished(bool flag){flagFinished = flag;}


    string left;
    vector <string> right;
    size_t dot_pos;
    size_t n;
    //bool flagFinished;
};

#endif // RULE_H
