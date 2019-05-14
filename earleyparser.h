#ifndef EARLEYPARSER_H
#define EARLEYPARSER_H

#include <iostream>
#include "grammar.h"

using namespace std;

class Grammar;

class EarleyParser
{
public:
    EarleyParser();

    void parse();
    void predict();
    void printRule(Rule rule);
    void findRulesIter(string symbol, size_t s);
    void addState(Rule state, size_t s);

    bool isSymbolProcessed(string symbol);

    Grammar *grammar;

    vector <string> processedSymbols;

    typedef vector <Rule> States_t;
    vector <States_t> stateList;
};

#endif // EARLEYPARSER_H
