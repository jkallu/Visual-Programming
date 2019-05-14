#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "rule.h"

class Rule;

class Grammar
{
public:
    Grammar();
    void createRules();
    bool symbolIsTerminal(string symbol);
    Rule getStartRule();
    vector <Rule> getRulesForSymbol(string symbol);

private:
    vector <Rule> rules;
};

#endif // GRAMMAR_H
