#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;

enum TokenType{
                // Identifiers and literals
                Identifier,
                Number,
                // Arithmetic operators
                Plus, Minus, Times, Div,
                // Comparison operators
                GreaterThan,
                GreaterThanOrEqual,
                LessThan,
                LessThanOrEqual,
                Equal,
                // Assignment operator
                Assign,
                // Parenthesis
                LeftParenthesis,
                RightParenthesis,
                // End
                EndOfInput
              };


class Token
{
public:
    Token(enum TokenType tType, string val = "", int ln = 0, int col = 0);

    void setColumn(int col){column = col;}
    void setLine(int lin){line = lin;}
    void setType(enum TokenType typ){tokenType = typ;}

    enum TokenType tokenType;
    string value;
    int line;
    int column;
};

#endif // TOKEN_H
