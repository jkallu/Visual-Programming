#include "grammar.h"

Grammar::Grammar()
{
    createRules();
    printRules();
}

void Grammar::createRules()
{
    Rule rule;

    rule.left = "Grammar";
    rule.right.push_back("SetNotation");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = "SetNotation";
    rule.right.push_back("Expression");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = "SetNotation";
    rule.right.push_back("Expression");
    rule.right.push_back("|");
    rule.right.push_back("Qualifier");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = "Qualifier";
    rule.right.push_back("Generator");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = "Generator";
    rule.right.push_back("[");
    rule.right.push_back("T");
    rule.right.push_back("T");
    rule.right.push_back("..");
    rule.right.push_back("T");
    rule.right.push_back("]");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = "Qualifier";
    rule.right.push_back("Expression");
    rule.right.push_back(",");
    rule.right.push_back("Expression");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = "Expression";
    rule.right.push_back("P");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = "Expression";
    rule.right.push_back("x");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'P';
    rule.right.push_back("S");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'S';
    rule.right.push_back("S");
    rule.right.push_back("+");
    rule.right.push_back("M");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'S';
    rule.right.push_back("M");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'M';
    rule.right.push_back("M");
    rule.right.push_back("*");
    rule.right.push_back("W");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'M';
    rule.right.push_back("W");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'W';
    rule.right.push_back("T");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'T';
    rule.right.push_back("1");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'T';
    rule.right.push_back("2");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'T';
    rule.right.push_back("3");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'T';
    rule.right.push_back("4");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'W';
    rule.right.push_back("U");
    rules.push_back(rule);
    rule.right.clear();

    rule.left = 'U';
    rule.right.push_back("Trigonometric_functions");
    rule.right.push_back("(");
    rule.right.push_back("V");
    rule.right.push_back(")");
    rules.push_back(rule);
    rule.right.clear();

    vector <Rule> trigonometric_rules = getTrigonometricRules();
    for (size_t i = 0; i < trigonometric_rules.size(); i++)
    {
        rules.push_back(trigonometric_rules.at(i));
    }

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

vector <Rule> Grammar::getTrigonometricRules()
{
    vector <Rule> trigonometric_rules;
    Rule rule;

    rule.left = "Trigonometric_functions";
    rule.right.push_back("sin");
    trigonometric_rules.push_back(rule);
    rule.right.clear();

    rule.left = "Trigonometric_functions";
    rule.right.push_back("cos");
    trigonometric_rules.push_back(rule);
    rule.right.clear();

    return trigonometric_rules;
}

void Grammar::printRules()
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        Rule rule = rules.at(i);
        std::cout << rule.left << " -> ";
        for (size_t j = 0; j < rule.right.size(); j++)
        {
            std::cout << rule.right.at(j) << " ";
        }

        cout << "\n";
    }
}

