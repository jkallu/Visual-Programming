#include "earleyparser.h"

EarleyParser::EarleyParser()
{
    grammar = new Grammar;
}

void EarleyParser::parse()
{
    string tokens = "2+3*4";

    Rule startRule = grammar->getStartRule();
    size_t st = 0;

    predict(startRule.left, st);
    processedSymbols.clear();

    printState(st);

    for (size_t i = 0; i < tokens.size(); i++)
    {
        string token;
        token += tokens.at(i);
        Rule rule = scan(token, st);

        st++;

        rule.dot_pos++;
        addState(rule, st);

        complete(rule.left, st);
        processedSymbols.clear();



        for (size_t j = 0; j < stateList.at(st).size(); j++)
        {
            Rule tmp_rule = stateList.at(st).at(j);
            if(tmp_rule.dot_pos < tmp_rule.right.size())
            {
                if(!grammar->symbolIsTerminal(tmp_rule.right.at(tmp_rule.dot_pos)))
                {
                    predict(tmp_rule.right.at(tmp_rule.dot_pos), st);
                }
            }
        }

        processedSymbols.clear();

        printState(st);

    }


}

void EarleyParser::predict(string symbol, size_t s)
{
    findRulesIter(symbol, s);
}

Rule EarleyParser::scan(string token, size_t st)
{
    for (size_t i = 0; i < stateList.at(st).size(); i++)
    {
        Rule rule = stateList.at(st).at(i);
        if(rule.dot_pos < rule.right.size())
        {
            if(rule.right.at(rule.dot_pos) == token)
            {
                return rule;
            }
        }
    }
}

void EarleyParser::complete(string symbol, size_t s)
{
    if(!isSymbolProcessed(symbol))
    {
        processedSymbols.push_back(symbol);
        for(size_t i = 0; i < stateList.at(s - 1).size(); i++)
        {
            Rule rule = stateList.at(s - 1).at(i);
            if(rule.dot_pos < rule.right.size())
            {
                if(rule.right.at(rule.dot_pos) == symbol)
                {
                    rule.dot_pos++;
                    addState(rule, s);
                    complete(rule.left, s);
                }
            }
        }
    }
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
    if(!isSymbolProcessed(symbol) && !grammar->symbolIsTerminal(symbol))
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

void EarleyParser::printStates()
{
    for (size_t i = 0; i < stateList.size(); i++)
    {
        printState(i);
    }
}

void EarleyParser::printState(size_t st)
{
    cout << "\n-------------------------------------------\n";
    cout << "S(" << st << ")" << endl;
    if(st < stateList.size())
    {
        for (size_t j = 0; j < stateList.at(st).size(); j++)
        {
            printRule(stateList.at(st).at(j));
        }
    }
}

void EarleyParser::printRule(Rule rule)
{
    cout << rule.left << " -> ";
    for(size_t i = 0; i < rule.right.size(); i++)
    {
        if(i == rule.dot_pos)
        {
            cout << ".";
        }
        cout << rule.right.at(i) << " " ;
    }
    cout << endl;
}
