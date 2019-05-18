#include "earleyparser.h"

EarleyParser::EarleyParser()
{
    grammar = new Grammar;
}

void EarleyParser::parse()
{
    string tokens = "2+3*4+2*1";

    Rule startRule = grammar->getStartRule();
    addState(startRule, 0);


    for (size_t i = 0; i <= tokens.size(); i++)
    {
        string token;

        if(i < tokens.size())
        {
            token += tokens.at(i);
        }

        if(i >= stateList.size())
        {
            cout << "Error in Parsing" << endl;
            return;
        }

        for (size_t j = 0; j < stateList.at(i).size(); j++)
        {
            Rule rule = stateList.at(i).at(j);
            if(!rule.isFinished())
            {
                string next_elm = rule.nextElement();
                if(!grammar->symbolIsTerminal(next_elm))
                {
                    predict(next_elm, i);
                }

                else if(i < tokens.size())
                {
                    scan(token, i);
                }
            }
            else
            {
                complete(rule, i);
            }
        }
        printState(i);

        if(i == tokens.size())
        {
            if(successfullSentence())
            {
                cout << "SUCCESSFUL" << endl;
            }
            else
            {
                cout << "FAILURE" << endl;
            }
        }
    }
}

bool EarleyParser::successfullSentence()
{
    Rule start = grammar->getStartRule();
    for (size_t i = 0; i < stateList.at(stateList.size() - 1).size(); i++)
    {
        Rule rule = stateList.at(stateList.size() - 1).at(i);
        if(rule.isFinished())
        {
            if(rule.left != start.left ||
                    rule.right.size() != start.right.size()
                    )
            {
                continue;
            }

            for(size_t j = 0; j < rule.right.size(); j++)
            {
                if(rule.right.at(j) != start.right.at(j))
                {
                    break;
                }

                if(j == rule.right.size() - 1)
                {
                    return true; // success
                }
            }
        }
    }

    return false;
}

bool EarleyParser::duplicateRule(Rule rule, States_t state)
{
    for (size_t i = 0; i < state.size(); i++)
    {
        if(rule.left != state.at(i).left ||
                rule.dot_pos != state.at(i).dot_pos ||
                rule.right.size() != state.at(i).right.size()
                )
        {
            continue;
        }

        for(size_t j = 0; j < rule.right.size(); j++)
        {
            if(rule.right.at(j) != state.at(i).right.at(j))
            {
                break;
            }

            if(j == rule.right.size() - 1)
            {
                return true; // duplicate
            }
        }
    }

    return false; // not duplicate
}

bool EarleyParser::finished(States_t state)
{
    return state.at(0).isFinished();
}

void EarleyParser::predict(string symbol, size_t s)
{
    vector <Rule> rules = grammar->getRulesForSymbol(symbol);

    for (size_t i = 0; i < rules.size(); i++)
    {
        Rule rule = rules.at(i);
        rule.n = s;
        addState(rule, s);
    }
}

void EarleyParser::scan(string token, size_t st)
{
    if(st >= stateList.size())
    {
        cout << "Error in Parsing" << endl;
        return;
    }

    for (size_t i = 0; i < stateList.at(st).size(); i++)
    {
        Rule rule = stateList.at(st).at(i);
        if(!rule.isFinished())
        {
            if(rule.nextElement() == token)
            {
                rule.dot_pos++;
                addState(rule, st + 1);
                return;
            }
        }
    }

    cout << "Unrecognized token " << token << endl;
}

void EarleyParser::complete(Rule rl, size_t s)
{
    for(size_t i = 0; i < stateList.at(rl.n).size(); i++)
    {
        Rule rule = stateList.at(rl.n).at(i);
        if(!rule.isFinished())
        {
            if(rule.nextElement() == rl.left)
            {
                rule.dot_pos++;
                addState(rule, s);
            }
        }
    }
}

void EarleyParser::addState(Rule state, size_t s)
{
    if(s > stateList.size())
    {
        cout << "Error in Parsing" << endl;
        return;
    }

    if(s < stateList.size())
    {
        if(!duplicateRule(state, stateList.at(s)))
        {
            stateList.at(s).push_back(state);
        }
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
    if(rule.right.size() == rule.dot_pos)
    {
        cout << ".";
    }
    cout << " " << rule.n;
    cout << endl;
}
