#include "earleyparser.h"

EarleyParser::EarleyParser()
{
    grammar = new Grammar;
}

void EarleyParser::parse()
{
    Rule startRule = grammar->getStartRule();
    findRulesIter(startRule.left, 0);

    for (size_t i = 0; i < stateList.size(); i++)
    {
        for (size_t j = 0; j < stateList.at(i).size(); j++)
        {
            printRule(stateList.at(i).at(j));
        }
    }

    processedSymbols.clear();
}

void EarleyParser::predict()
{
    processedSymbols.clear();
}

void EarleyParser::addState(Rule state, size_t s)
{
    if(s < stateList.size())
    {
        stateList.at(s).push_back(state);
    }
    else
    {
        States_t tmp;
        tmp.push_back(state);
        stateList.push_back(tmp);
    }
}

void EarleyParser::findRulesIter(string symbol, size_t s)
{
    if(!isSymbolProcessed(symbol))
    {
        processedSymbols.push_back(symbol);

        vector <Rule> rules = grammar->getRulesForSymbol(symbol);

        for (size_t i = 0; i < rules.size(); i++)
        {
            addState(rules.at(i), s);
        }

        for (size_t i = 0; i < rules.size(); i++)
        {

            for (size_t j = 0; j < rules.at(i).right.size(); j++)
            {
                findRulesIter(rules.at(i).right.at(j), s);
            }
        }
    }
}

bool EarleyParser::isSymbolProcessed(string symbol)
{
    for (size_t i = 0; i < processedSymbols.size(); i++)
    {
        if(processedSymbols.at(i) == symbol)
        {
            return true;
        }
    }

    return false;
}

void EarleyParser::printRule(Rule rule)
{
    cout << rule.left << " -> ";
    for(size_t i = 0; i < rule.right.size(); i++)
    {
        cout << rule.right.at(i) << " " ;
    }
    cout << endl;
}
