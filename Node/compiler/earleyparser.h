#ifndef EARLEYPARSER_H
#define EARLEYPARSER_H

#include <iostream>
#include "grammar.h"
#include <QQueue>
#include "token.h"
#include "compiletoc.h"

#include "commonheader.h"


using namespace std;

class Grammar;
class Token;
class CompileToC;

class EarleyParser
{
public:
    EarleyParser();

    typedef vector <Rule> States_t;



    string parse(vector<Token *> tokens, string typ);
    void predict(string symbol, size_t s);
    void findRulesIter(string symbol, size_t s);
    void addState(Rule rule, size_t s, vector<States_t> *stList);
    void addStateForReversed(Rule rule, size_t s, vector<States_t> *stList);
    //void scan(string token, size_t st);
    void scan(Token *token, size_t st);
    void complete(Rule rl, size_t s);

    void changePriorityDuplicateRule(Rule rule, States_t *state);

    void printStates(vector<States_t> *stList);
    void printState(States_t state);
    void printRule(Rule rule);

    bool isSymbolProcessed(string symbol);
    bool finished(States_t state);
    bool duplicateRule(Rule rule, States_t state);
    bool successfullSentence();

    void createPasrseTree();
    Rule *getFinishedRuleOfThisType(Rule rule, States_t state);
    Rule *getFinishedRuleOfThisSymbol(string symbol, States_t *state);
    Rule * getNotVisitedRulesForSymbolWithPriorityFromState(string symbol, States_t *state);

    void recurseParser(Rule rule, States_t state);
    bool isRuleProcessed(Rule rule);

    void createStateListCompletedReversed();


    void DFSRecurse(vector<States_t> *stList, size_t pos, ParseTree_t *pTree); // Deapth first search

    void parseRecursively(ParseTree_t *pTree, size_t pos, vector<States_t> *stList);

    void printParseTree(ParseTree_t* pTree);

    void printParseTreeBFS();



    size_t dfsRecursCnt;

    Grammar *grammar;

    vector <string> processedSymbols;
    States_t states_processed;



    vector <States_t> stateList;
    vector <States_t> stateListCompleteRev;

    ParseTree_t *parseTree;

    vector <string> dfsProcessedSymbols;

    size_t state_pos, treeLvlPos;

    QQueue <ParseTree_t *> queue;

    CompileToC *compileToC;

    string type;
};

#endif // EARLEYPARSER_H
