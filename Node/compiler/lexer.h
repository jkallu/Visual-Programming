#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "token.h"
#include "fsm.h"
#include "numberfsm.h"


using namespace std;

class Token;
class FSM;
class NumberFSM;

class Lexer
{
public:
    Lexer(string fname, bool flagFile);

    Token* getNextToken();
    Token* recognizeIdentifier();
    Token* recognizeNumber();
    Token* recognizeOperator();
    Token* recognizeParenthesis();
    Token* recognizeCurlyBrackets();
    Token* recognizeComparisonOperator();
    Token* recognizeArithmeticOperator();
    Token* recognizeLogicalOperator();
    Token* recognizeVerticalBar();
    Token* recognizeDoubleDots();
    Token* recognizeSquareBracket();
    Token* recognizeTrigonometricFunctions(string ident);

    void skipWhiteSpace();

    bool isWhiteSpace(char c);
    bool isIDentifier(char c);
    bool isNumber(char c);
    bool isParenthesis(char c);
    bool isCurlyBrackets(char c);
    bool isOperator(char c);
    bool isComparisonOperator(char c);
    bool isArithmeticOperator(char c);
    bool isVerticalBar(char c);
    bool isDot(char c);
    bool isSquareBracket(char c);

    void test();
    vector <Token *> allTokens();


    string fileName;
    ifstream inFile;
    stringstream strStream;
    int line;
    int column;
};

#endif // LEXER_H
