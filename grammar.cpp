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
    rule4.right.push_back("W");
    rules.push_back(rule4);

    Rule rule5;
    rule5.left = 'M';
    rule5.right.push_back("W");
    rules.push_back(rule5);

    Rule rule6;
    rule6.left = 'T';
    rule6.right.push_back("1");
    rules.push_back(rule6);

    Rule rule7;
    rule7.left = 'T';
    rule7.right.push_back("2");
    rules.push_back(rule7);

    Rule rule8;
    rule8.left = 'T';
    rule8.right.push_back("3");
    rules.push_back(rule8);

    Rule rule9;
    rule9.left = 'T';
    rule9.right.push_back("4");
    rules.push_back(rule9);

    Rule rule;

    rule.left = 'W';
    rule.right.push_back("T");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'W';
    rule.right.push_back("U");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'U';
    rule.right.push_back("Y");
    rule.right.push_back("(");
    rule.right.push_back("V");
    rule.right.push_back(")");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'Y';
    rule.right.push_back("sin");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'Y';
    rule.right.push_back("cos");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'V';
    rule.right.push_back("x");
    rules.push_back(rule);
    rule.right.clear();
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



bool Grammar::finished(Rule rule)
{
    if(rule.dot_pos + 1 < rule.right.size())
    {
        return false;
    }

    return true;
}

