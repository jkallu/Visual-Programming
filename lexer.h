#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <fstream>

#include "token.h"
#include "fsm.h"
#include <sstream>
#include <vector>

using namespace std;

class Token;
class FSM;

class Lexer
{
public:
    Lexer(string fname, bool flagFile);
    Token *getNextToken();
    Token *recognizeIdentifier();
    Token *recognizeNumber();
    Token *recognizeOperator();
    Token *recognizeParenthesis();

    bool isIDentifier(char c);
    bool isNumber(char c);
    bool isParenthesis(char c);
    bool isOperator(char c);

    void test();
    vector <Token *> allTokens();


    string fileName;
    ifstream inFile;
    stringstream strStream;
    int line;
    int column;
};

#endif // LEXER_H
