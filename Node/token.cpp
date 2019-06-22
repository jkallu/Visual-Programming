#include "token.h"

Token::Token(enum TokenType tType, string val, int ln, int col)
{
    tokenType = tType;
    value = val;
    line = ln;
    column = col;
}
