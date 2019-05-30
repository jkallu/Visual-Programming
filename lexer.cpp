#include "lexer.h"

Lexer::Lexer(string fname, bool flagFile)
{
    strStream.clear();

    if(flagFile)
    {
        fileName = fname;
        inFile.open(fileName);

        if(!inFile.is_open())
        {
            cout << "Error! " << fileName << " could not be opened" << endl;
            return;
        }

        strStream << inFile.rdbuf();
    }
    else
    {
        strStream.str(fname + '\0');
    }


    line = 0;
    column = 0;
}

Token *Lexer::getNextToken()
{
    skipWhiteSpace();
    if(strStream.eof() || strStream.fail())
    {
        return new Token(TokenType::EndOfInput);
    }


    char c;
    strStream.get(c);

    if(isIDentifier(c))
    {
        strStream.unget();
        return recognizeIdentifier();
    }

    else if(isNumber(c))
    {
        strStream.unget();
        return recognizeNumber();
    }

    else if(isOperator(c))
    {
        strStream.unget();
        return recognizeOperator();
    }

    else if(isParenthesis(c))
    {
        strStream.unget();
        return recognizeParenthesis();
    }

    else if(isCurlyBrackets(c))
    {
        strStream.unget();
        return recognizeCurlyBrackets();
    }

    else if(isSquareBracket(c))
    {
        strStream.unget();
        return recognizeSquareBracket();
    }

    else if (isVerticalBar(c))
    {
        strStream.unget();
        return recognizeLogicalOperator();
    }

    else if (isDot(c))
    {
        strStream.unget();
        return recognizeDoubleDots();
    }

    else if (c == '\0')
    {
        return new Token(TokenType::EndOfInput);
    }

    else
    {
        cout << "No handler !! for " << c << endl;
    }
}

bool Lexer::isWhiteSpace(char c)
{
    if(   c == ' '
          || c == '\t'
          || c == '\n'
          || c == '\v'
          || c == '\f'
          || c == '\r'
          )
    {
        return true;
    }

    return false;
}

bool Lexer::isIDentifier(char c)
{
    return isalpha(c);
}

bool Lexer::isNumber(char c)
{
    return isdigit(c);
}

bool Lexer::isOperator(char c)
{
    return (isArithmeticOperator(c) || isComparisonOperator(c));
}

bool Lexer::isComparisonOperator(char c)
{
    if(
            c == '>'
            || c == '<'
            || c == '='
            )
    {
        return true;
    }

    return false;
}

bool Lexer::isArithmeticOperator(char c)
{
    if(
            c == '+'
            || c == '-'
            || c == '*'
            || c == '/'
            )
    {
        return true;
    }

    return false;
}

bool Lexer::isParenthesis(char c)
{
    if(c == '(' || c == ')')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Lexer::isCurlyBrackets(char c)
{
    if(c == '{' || c == '}')
    {
        return true;
    }

    return false;
}

bool Lexer::isSquareBracket(char c)
{
    if(c == '[' || c == ']')
    {
        return true;
    }

    return false;
}

bool Lexer::isVerticalBar(char c)
{
    if(c == '|')
    {
        return true;
    }

    return false;
}

bool Lexer::isDot(char c)
{
    if(c == '.')
    {
        return true;
    }

    return false;
}

void Lexer::skipWhiteSpace()
{
    char c;
    strStream.get(c);

    while(isWhiteSpace(c))
    {
        if(strStream.eof() || !strStream.good())
        {
            return ;
        }

        if(c == '\n')
        {
            line ++;
        }

        if(strStream.eof() || strStream.fail())
        {
            return;
        }
        strStream.get(c);
    }

    strStream.unget();
}

Token *Lexer::recognizeIdentifier()
{
    string identifier = "";
    char c;
    while (!strStream.eof())
    {
        strStream.get(c);
        if(!(isIDentifier(c) || isNumber(c) || c == '_'))
        {
            strStream.unget();
            break;
        }
        column++;
        identifier += c;

    }

    return new Token(TokenType::Identifier, identifier, line, column);
}

Token *Lexer::recognizeNumber()
{
    NumberFSM numberFSM;
    Token *tok = numberFSM.run(&strStream, column);
    tok->setLine(line);
    tok->setType(TokenType::Number);

    return tok;
}

Token *Lexer::recognizeOperator()
{
    char c;
    strStream.get(c);

    if(isArithmeticOperator(c))
    {
        strStream.unget();
        return recognizeArithmeticOperator();
    }

    else if(isComparisonOperator(c))
    {
        strStream.unget();
        return recognizeComparisonOperator();
    }

    return nullptr;
}

Token* Lexer::recognizeParenthesis()
{
    char c;
    strStream.get(c);

    column++;

    if(c == '(')
    {
        return new Token(TokenType::LeftParenthesis, "(", line, column - 1);
    }

    return new Token(TokenType::RightParenthesis, ")", line, column - 1);
}

Token* Lexer::recognizeCurlyBrackets()
{
    char c;
    strStream.get(c);

    column++;

    if(c == '{')
    {
        return new Token(TokenType::LeftCurlyBracket, "{", line, column - 1);
    }

    return new Token(TokenType::RightCurlyBracket, "}", line, column - 1);
}

Token* Lexer::recognizeSquareBracket()
{
    char c;
    strStream.get(c);

    column++;

    if(c == '[')
    {
        return new Token(TokenType::LeftSquareBracket, "[", line, column - 1);
    }

    return new Token(TokenType::RightSquareBracket, "]", line, column - 1);
}

Token* Lexer::recognizeArithmeticOperator()
{
    char c;
    strStream.get(c);

    column++;

    if(c == '+')
    {
        return new Token(TokenType::Plus, "+", line, column - 1);
    }

    else if (c == '-')
    {
        return new Token(TokenType::Minus, "-", line, column - 1);
    }

    else if (c == '*')
    {
        return new Token(TokenType::Times, "*", line, column - 1);
    }

    return new Token(TokenType::Div, "/", line, column - 1);
}

Token *Lexer::recognizeComparisonOperator()
{
    char c;
    strStream.get(c);

    column++;

    char lookAhead = '\0';

    if(!strStream.eof())
    {
        strStream.get(lookAhead);
    }


    if(c == '<')
    {
        if(lookAhead == '=')
        {
            column++;
            return new Token(TokenType::LessThanOrEqual, "<=", line, column - 2);
        }

        strStream.unget();
        return new Token(TokenType::LessThan, "<", line, column - 1);
    }

    else if (c == '>')
    {
        if(lookAhead == '=')
        {
            column++;
            return new Token(TokenType::GreaterThanOrEqual, ">=", line, column - 2);
        }

        strStream.unget();
        return new Token(TokenType::GreaterThan, ">", line, column - 1);
    }

    else
    {
        if(lookAhead == '=')
        {
            column++;
            return new Token(TokenType::Equal, "==", line, column - 2);
        }

        strStream.unget();
        return new Token(TokenType::Assign, "=", line, column - 1);
    }
}

Token *Lexer::recognizeLogicalOperator()
{
    char c;
    strStream.get(c);

    column++;

    if(c == '|')
    {
        return new Token(TokenType::VerticalBar, "|", line, column - 1);
    }

    return nullptr;
}

Token *Lexer::recognizeDoubleDots()
{
    char c;
    strStream.get(c);

    column++;

    if(c == '.')
    {
        strStream.get(c);
        if(c == '.')
        {
            column++;
            return new Token(TokenType::DoubleDots, "..", line, column - 1);
        }
        strStream.unget();
    }

    return nullptr;
}

void Lexer::test()
{
    //int states[] = {1, 2};
    //int acceptingStates[] = {2};
    //FSM *fsm = new FSM(states, 1, acceptingStates);
    //fsm->run("hello");

    //delete fsm;

    vector  <Token *> tokens = allTokens();

    for (size_t i = 0; i < tokens.size(); i++)
    {
        cout << tokens.at(i)->value << " " << tokens.at(i)->tokenType << endl;
    }
}

vector <Token *>Lexer::allTokens()
{
    vector  <Token *> tokens;
    Token *token = getNextToken();
    if(token->value == "sin" || token->value == "cos")
    {
        token->tokenType = TokenType::Trigonometric;
    }

    while (token->tokenType != TokenType::EndOfInput)
    {
        tokens.push_back(token);
        token = getNextToken();
    }

    for (size_t i = 0; i < tokens.size(); i++)
    {
        cout << tokens.at(i)->value << " " << tokens.at(i)->tokenType << endl;
    }

    return tokens;
}

