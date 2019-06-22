#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "rule.h"
#include <iostream>

class Rule;

class Grammar
{
public:
    Grammar();
    void createRules();
    void printRules();
    bool symbolIsTerminal(string symbol);
    Rule getStartRule();
    vector <Rule> getRulesForSymbol(string symbol);
    bool finished(Rule rule);

    vector <Rule> getTrigonometricRules();

private:
    vector <Rule> rules;
};

#endif // GRAMMAR_H
