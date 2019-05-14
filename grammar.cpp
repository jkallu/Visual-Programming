#include "grammar.h"

Grammar::Grammar()
{
    createRules();
}

void Grammar::createRules()
{
    Rule rule1;
    rule1.left = 'P';
    rule1.right.push_back("S");
    rules.push_back(rule1);

    Rule rule2;
    rule2.left = 'S';
    rule2.right.push_back("S");
    rule2.right.push_back("+");
    rule2.right.push_back("M");
    rules.push_back(rule2);

    Rule rule3;
    rule3.left = 'S';
    rule3.right.push_back("M");
    rules.push_back(rule3);

    Rule rule4;
    rule4.left = 'M';
    rule4.right.push_back("M");
    rule4.right.push_back("*");
    rule4.right.push_back("T");
    rules.push_back(rule4);

    Rule rule5;
    rule5.left = 'M';
    rule5.right.push_back("T");
    rules.push_back(rule5);

    Rule rule6;
    rule6.left = 'T';
    rule6.right.push_back("1");
    rule6.right.push_back("2");
    rule6.right.push_back("3");
    rule6.right.push_back("4");
    rules.push_back(rule6);
}

bool Grammar::symbolIsTerminal(string symbol)
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(rules.at(i).left == symbol)
        {
            return false;
        }
    }

    return true;
}

Rule Grammar::getStartRule()
{
    return rules.at(0);
}

vector <Rule> Grammar::getRulesForSymbol(string symbol)
{
    vector <Rule> tmp_rules;
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(rules.at(i).left == symbol)
        {
            tmp_rules.push_back(rules.at(i));
        }
    }

    return tmp_rules;
}

