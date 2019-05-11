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
        strStream.str(fname);
    }


    line = 0;
    column = 0;
}

Token *Lexer::getNextToken()
{
    char c;
    strStream.get(c);

    if(strStream.eof() || !strStream.good())
    {
        return new Token(TokenType::EndOfInput);
    }


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
    else
    {
        return nullptr;
    }
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
    if(
            c == '+'
            || c == '-'
            || c == '*'
            || c == '/'
            || c == '>'
            || c == '<'
            || c == '='
            )
    {
        return true;
    }
    else
    {
        return false;
    }
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

Token *Lexer::recognizeIdentifier()
{

}

Token *Lexer::recognizeNumber()
{

}

Token *Lexer::recognizeOperator()
{

}

Token *Lexer::recognizeParenthesis()
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

    while (token->tokenType != TokenType::EndOfInput)
    {
        tokens.push_back(token);
        token = getNextToken();
    }

    return tokens;
}

