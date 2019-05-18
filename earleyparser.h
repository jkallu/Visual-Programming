#ifndef EARLEYPARSER_H
#define EARLEYPARSER_H

#include <iostream>
#include "grammar.h"

typedef vector <Rule> States_t;

using namespace std;

class Grammar;

class EarleyParser
{
public:
    EarleyParser();

    void parse();
    void predict(string symbol, size_t s);
    void findRulesIter(string symbol, size_t s);
    void addState(Rule state, size_t s);
    void scan(string token, size_t st);
    void complete(Rule rl, size_t s);

    void printStates();
    void printState(size_t st);
    void printRule(Rule rule);

    bool isSymbolProcessed(string symbol);
    bool finished(States_t state);
    bool duplicateRule(Rule rule, States_t state);
    bool successfullSentence();

    Grammar *grammar;

    vector <string> processedSymbols;


    vector <States_t> stateList;
};

#endif // EARLEYPARSER_H
