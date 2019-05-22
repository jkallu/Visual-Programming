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

    bool visited() {return flagVisited;}
    void setVisited(bool flag) {flagVisited = flag;}
    //void setFinished(bool flag){flagFinished = flag;}


    string left;
    vector <string> right;
    size_t dot_pos;
    size_t n;
    bool flagVisited;
    //bool flagFinished;
};

#endif // RULE_H
