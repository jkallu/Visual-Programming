#include "earleyparser.h"

EarleyParser::EarleyParser()
{
    grammar = new Grammar;
    dfsRecursCnt = 0;
    compileToC = new CompileToC;
}

string EarleyParser::parse(vector  <Token *> tokens, string typ)
{
    type = typ;
    //string tokens = "sin(0)";

    Rule startRule = grammar->getStartRule();
    addState(startRule, 0, &stateList);


    for (size_t i = 0; i <= tokens.size(); i++)
    {
        //string token;
        Token *token;

        if(i < tokens.size())
        {
            //token += tokens.at(i)->value;
            token = tokens.at(i);
        }

        if(i >= stateList.size())
        {
            cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << __FUNCTION__ << "Error in Parsing" << endl;
            return "";
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


        if(i == tokens.size())
        {
            if(successfullSentence())
            {
                printStates(&stateList);
                cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << "SUCCESSFUL" << endl;
                createPasrseTree();
                return compileToC->start(parseTree, type);
            }
            else
            {
                cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << "FAILURE" << endl;
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

void EarleyParser::changePriorityDuplicateRule(Rule rule, States_t *state)
{
    for (size_t i = 0; i < state->size(); i++)
    {
        if(rule.left != state->at(i).left ||
                rule.dot_pos != state->at(i).dot_pos ||
                rule.right.size() != state->at(i).right.size()
                )
        {
            continue;
        }

        for(size_t j = 0; j < rule.right.size(); j++)
        {
            if(rule.right.at(j) != state->at(i).right.at(j))
            {
                break;
            }

            if(j == rule.right.size() - 1)
            {
                if(rule.n > state->at(i).n)
                {
                    state->at(i).n = rule.n;
                }
                return; // duplicate
            }
        }
    }

    return; // not duplicate
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
        addState(rule, s, &stateList);
    }
}

void EarleyParser::scan(Token *token, size_t st)
{
    if(st >= stateList.size())
    {
        cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << "Error in Parsing" << endl;
        return;
    }

    for (size_t i = 0; i < stateList.at(st).size(); i++)
    {
        Rule rule = stateList.at(st).at(i);
        if(!rule.isFinished())
        {
            //if(rule.nextElement() == token->value)
           if(rule.nextElementType() == token->tokenType)
            {
                rule.dot_pos++;
                addState(rule, st + 1, &stateList);
                return;
            }
        }
    }

    cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] "<< " Unrecognized token " << token->value << endl;
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
                addState(rule, s, &stateList);
            }
        }
    }
}

void EarleyParser::addStateForReversed(Rule rule, size_t s, vector<States_t> *stList)
{
    if(s > stList->size())
    {
        cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << "Error in Parsing" << endl;
        return;
    }

    if(s < stList->size())
    {
        //
        if(!duplicateRule(rule, stList->at(s)))
        {
            stList->at(s).push_back(rule);
        }
        else
        {
            changePriorityDuplicateRule(rule, &stList->at(s));
        }
    }
    else
    {
        States_t tmp;
        tmp.push_back(rule);
        stList->push_back(tmp);
    }
}

void EarleyParser::addState(Rule rule, size_t s, vector <States_t> *stList)
{
    if(s > stList->size())
    {
        cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << "Error in Parsing" << endl;
        return;
    }

    if(s < stList->size())
    {
        if(!duplicateRule(rule, stList->at(s)))
        {
            stList->at(s).push_back(rule);
        }
    }
    else
    {
        States_t tmp;
        tmp.push_back(rule);
        stList->push_back(tmp);
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
            addState(rules.at(i), s, &stateList);
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

void EarleyParser::printStates(vector<States_t> *stList)
{
    for (size_t i = 0; i < stList->size(); i++)
    {
        cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << endl << "S(" << i << ")" << endl;
        printState(stList->at(i));
    }
}

void EarleyParser::printState(States_t state)
{
    for (size_t j = 0; j < state.size(); j++)
    {
        printRule(state.at(j));
    }

    cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << "\n-------------------------------------------\n";
}

void EarleyParser::printRule(Rule rule)
{
    cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << rule.left << " -> ";
    for(size_t i = 0; i < rule.right.size(); i++)
    {
        if(i == rule.dot_pos)
        {
            cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << ".";
        }
        cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << rule.right.at(i) << " " ;
    }
    if(rule.right.size() == rule.dot_pos)
    {
        cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << ".";
    }
    cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << " " << rule.n;
    cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << endl;
}

void EarleyParser::recurseParser(Rule rule, States_t state)
{

    cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << endl;
    for (int i = rule.right.size() - 1; i >= 0; i--)
    {
        if(grammar->symbolIsTerminal(rule.right.at(i)))
        {
            cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << rule.right.at(i) << endl;
        }

        else
        {
            cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << rule.right.at(i) << endl;
            vector <Rule> rules = grammar->getRulesForSymbol(rule.right.at(i));

            for (size_t j = 0; j < rules.size(); j++)
            {
                Rule * finished_rule = getFinishedRuleOfThisType(rules.at(j), state);
                if(finished_rule != nullptr)
                {
                    cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << rule.right.at(i) << endl;
                }
            }

            for (size_t j = 0; j < rules.size(); j++)
            {
                Rule * finished_rule = getFinishedRuleOfThisType(rules.at(j), state);
                if(finished_rule != nullptr)
                {
                    if(isRuleProcessed(*finished_rule))
                    {
                        continue;
                    }
                    else
                    {
                        states_processed.push_back(*finished_rule);
                        recurseParser(*finished_rule, state);
                    }

                }
            }
        }
    }
}

void EarleyParser::createStateListCompletedReversed()
{
    for(size_t i = 0; i < stateList.size(); i++)
    {
        States_t state_tmp;
        stateListCompleteRev.push_back(state_tmp);

        States_t state = stateList.at(i);

        for (size_t j = 0; j < state.size(); j++)
        {
            Rule rule = state.at(j);
            if(rule.isFinished())
            {
                size_t n = rule.n;
                rule.n = i;
                addStateForReversed(rule, n, &stateListCompleteRev);
            }
        }
    }

    printStates(&stateListCompleteRev);
}

void EarleyParser::DFSRecurse(vector<States_t> *stList, size_t pos, ParseTree_t *pTree)
{
    if(pos >= stList->size())
    {
        cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << "Error!!" << endl;
        return;
    }

    States_t *state = &stList->at(pos);

    if(state->size() <= 0)
    {
        DFSRecurse(stList, pos + 1, pTree);
        return;
    }

    Rule *rule = getNotVisitedRulesForSymbolWithPriorityFromState(pTree->symbol, state);
    if(rule != nullptr)
    {
        for(size_t i = 0; i < rule->right.size(); i++)
        {
            string symbol = rule->right.at(i);
            ParseTree_t *tmp_tree = new ParseTree_t;
            tmp_tree->symbol = symbol;
            pTree->child.push_back(tmp_tree);

            ParseTree_t *tree_last = pTree->child.at(pTree->child.size() - 1);

            if(!grammar->symbolIsTerminal(symbol))
            {
                DFSRecurse(stList, pos, tree_last);
            }
        }
    }
    else
    {
        DFSRecurse(stList, pos + 1, pTree);
    }

    /*
    if(rule_Finished.right.size() > 0)
    {
        for (size_t i = 0; i < dfsProcessedSymbols.size(); i++)
        {
            if(dfsProcessedSymbols.at(i) == rule_Finished.left)
            {
                return;
            }
        }
        dfsProcessedSymbols.push_back(rule_Finished.left);
        for (size_t i = 0; i < rule_Finished.right.size(); i++)
        {
            string symbol = rule_Finished.right.at(i);

            ParseTree_t *tmp_tree = new ParseTree_t;
            tmp_tree->symbol = symbol;
            pTree->child.push_back(tmp_tree);

            ParseTree_t *pTree_last = pTree->child.at(pTree->child.size() - 1);

            if(!grammar->symbolIsTerminal(symbol))
            {
                DFSRecurse(stList, pos, pTree_last);
            }
            else
            {
                dfsProcessedSymbols.clear();
                pos++;
            }
        }
    }*/
}

void EarleyParser::printParseTree(ParseTree_t *pTree)
{

    cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << pTree->symbol << " ";

    treeLvlPos++;

    if(pTree->child.size() > 0)
    {

        for (size_t i = 0; i < pTree->child.size(); i++)
        {

            printParseTree(pTree->child.at(i));





        }

    }

    treeLvlPos--;

    cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] "  << endl;
    for (int j = 0; j < treeLvlPos; j++)
    {
        cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << "| ";
    }

}

void EarleyParser::parseRecursively(ParseTree_t *pTree, size_t pos, vector<States_t> *stList)
{
    if(state_pos < 1)
    {
        cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << "Error" << endl;
        return;
    }

    States_t *state = &stList->at(state_pos);

    Rule *rule = getFinishedRuleOfThisSymbol(pTree->symbol, state);
    if(rule != nullptr)
    {
        for(size_t i = 0; i < rule->right.size(); i++)
        {
            string symbol = rule->right.at(i);
            ParseTree_t *tmp_tree = new ParseTree_t;
            tmp_tree->symbol = symbol;
            pTree->child.push_back(tmp_tree);
        }

        // DFS Right to left
        for(int i = pTree->child.size() - 1; i >= 0; i--)
        {
            ParseTree_t *tmp_tree = pTree->child.at(i);
            if(!grammar->symbolIsTerminal(tmp_tree->symbol)) // non terminal
            {
                parseRecursively(tmp_tree, state_pos, stList);
            }
            else // terminal
            {
                state_pos--;
            }
        }
    }
    else
    {
        cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << state_pos << " " << pTree->symbol <<" Error! empty rule" << endl;
        return;
    }

}

void EarleyParser::createPasrseTree()
{
    if(stateList.size() <= 0)
    {
        return;
    }

    //createStateListCompletedReversed();

    Rule rule = grammar->getStartRule();

    parseTree = new ParseTree_t;
    parseTree->symbol = rule.left;

    state_pos = stateList.size() - 1;
    parseRecursively(parseTree, stateList.size() - 1, &stateList);

    treeLvlPos = 0;
    printParseTree(parseTree);

    /*States_t final_state = stateList.at(stateList.size() - 1);


    Rule *final_rule = getFinishedRuleOfThisType(grammar->getStartRule(), final_state);

    cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << endl << endl;

    cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << final_rule->left << endl;

    recurseParser(*final_rule, final_state);*/
}

void EarleyParser::printParseTreeBFS()
{
    while(queue.size() > 0)
    {
        ParseTree_t *pTree = queue.dequeue();
        cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << pTree->symbol << " ";
    }


}

Rule * EarleyParser::getNotVisitedRulesForSymbolWithPriorityFromState(string symbol, States_t *state)
{
    Rule *rule_ret = nullptr;
    for (size_t i = 0; i < state->size(); i++)
    {
        Rule *rule_fin = &state->at(i);
        if(rule_fin->isFinished() && !rule_fin->visited())
        {
            if(rule_fin->left != symbol)
            {
                continue;
            }

            if(rule_ret != nullptr)
            {
                if(rule_fin->n <= rule_ret->n)
                {
                    continue;
                }
            }

            rule_ret = rule_fin;
        }
    }

    if(rule_ret != nullptr)
    {
        rule_ret->setVisited(true);
    }

    return rule_ret;
}

Rule * EarleyParser::getFinishedRuleOfThisType(Rule rule, States_t state)
{
    Rule * rule_ret = new Rule;
    for (size_t i = 0; i < state.size(); i++)
    {
        Rule rule_fin =state.at(i);
        if(rule_fin.isFinished())
        {
            if(rule_fin.left != rule.left ||
                    rule_fin.right.size() != rule.right.size()
                    )
            {
                continue;
            }

            for(size_t j = 0; j < rule_fin.right.size(); j++)
            {
                if(rule.right.at(j) != rule_fin.right.at(j))
                {
                    break;
                }

                if(j == rule_fin.right.size() - 1)
                {
                    *rule_ret = rule_fin;
                    return rule_ret; // success
                }
            }
        }
    }

    return nullptr;
}

Rule *EarleyParser::getFinishedRuleOfThisSymbol(string symbol, States_t *state)
{
    Rule * rule_ret = nullptr;
    //cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << rule_ret.right.size() << endl;
    for (size_t i = 0; i < state->size(); i++)
    {
        Rule *rule_fin = &state->at(i);
        if(rule_fin->isFinished()  && !rule_fin->visited())
        {
            if(rule_fin->left != symbol)
            {
                continue;
            }

            rule_ret = rule_fin;
            break;
        }
    }


    if(rule_ret != nullptr)
    {
        rule_ret->setVisited(true);
    }

    return rule_ret;

}


bool EarleyParser::isRuleProcessed(Rule rule)
{
    if(states_processed.empty())
    {
        return false;
    }

    for (size_t i = 0; i < states_processed.size(); i++)
    {
        Rule tmp = states_processed.at(i);

        if(rule.left != tmp.left ||
                rule.right.size() != tmp.right.size())
        {
            continue;
        }

        for(size_t j = 0; j < rule.right.size(); j++)
        {
            if(rule.right.at(j) != tmp.right.at(j))
            {
                break;
            }

            if(j == rule.right.size() - 1)
            {
                return true; // processed
            }
        }
    }

    return false;
}
