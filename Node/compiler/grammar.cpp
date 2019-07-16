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
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = "SetNotation";
    rule.right.push_back("Expression");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = "SetNotation";
    rule.right.push_back("Expression");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rule.right.push_back("|");
    rule.rightTokenType.push_back(TokenType::VerticalBar);
    rule.right.push_back("Qualifier");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = "Qualifier";
    rule.right.push_back("Generator");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = "Generator";
    rule.right.push_back("[");
    rule.rightTokenType.push_back(TokenType::LeftSquareBracket);
    rule.right.push_back("T");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rule.right.push_back("T");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rule.right.push_back("..");
    rule.rightTokenType.push_back(TokenType::DoubleDots);
    rule.right.push_back("T");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rule.right.push_back("]");
    rule.rightTokenType.push_back(TokenType::RightSquareBracket);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = "Qualifier";
    rule.right.push_back("Expression");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rule.right.push_back(",");
    rule.rightTokenType.push_back(TokenType::Comma);
    rule.right.push_back("Expression");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = "Expression";
    rule.right.push_back("P");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

   /*rule.left = "Expression";
    rule.right.push_back("x");
    rule.rightTokenType.push_back(TokenType::Identifier);
    rules.push_back(rule);
    rule.right.clear();*/

    rule.left = 'P';
    rule.right.push_back("S");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = 'S';
    rule.right.push_back("S");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rule.right.push_back("+");
    rule.rightTokenType.push_back(TokenType::Plus);
    rule.right.push_back("M");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = 'S';
    rule.right.push_back("M");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = 'M';
    rule.right.push_back("M");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rule.right.push_back("*");
    rule.rightTokenType.push_back(TokenType::Times);
    rule.right.push_back("W");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = 'M';
    rule.right.push_back("W");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = 'W';
    rule.right.push_back("T");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = 'T';
    rule.right.push_back("1");
    rule.rightTokenType.push_back(TokenType::Number);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = 'T';
    rule.right.push_back("2");
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = 'T';
    rule.right.push_back("3");
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = 'T';
    rule.right.push_back("4");
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = 'W';
    rule.right.push_back("U");
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = 'U';
    rule.right.push_back("Trigonometric_functions");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rule.right.push_back("(");
    rule.rightTokenType.push_back(TokenType::LeftParenthesis);
    rule.right.push_back("V");
    rule.rightTokenType.push_back(TokenType::EndOfInput);
    rule.right.push_back(")");
    rule.rightTokenType.push_back(TokenType::RightParenthesis);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    vector <Rule> trigonometric_rules = getTrigonometricRules();
    for (size_t i = 0; i < trigonometric_rules.size(); i++)
    {
        rules.push_back(trigonometric_rules.at(i));
    }

    rule.left = 'V';
    rule.right.push_back("x");
    rule.rightTokenType.push_back(TokenType::Identifier);
    rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();
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
    rule.rightTokenType.push_back(TokenType::Trigonometric);
    trigonometric_rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    rule.left = "Trigonometric_functions";
    rule.right.push_back("cos");
    rule.rightTokenType.push_back(TokenType::Trigonometric);
    trigonometric_rules.push_back(rule);
    rule.right.clear();
    rule.rightTokenType.clear();

    return trigonometric_rules;
}

void Grammar::printRules()
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        Rule rule = rules.at(i);
        std::cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << rule.left << " -> ";
        for (size_t j = 0; j < rule.right.size(); j++)
        {
            std::cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << rule.right.at(j) << " ";
        }

        cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << "\n";
    }
}

