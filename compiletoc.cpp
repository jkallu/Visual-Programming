#include "compiletoc.h"

CompileToC::CompileToC()
{

}
/*
string CompileToC::start(ParseTree_t *pTree)
{
    return compileToCIter(pTree);
}

string CompileToC::compileToCIter(ParseTree_t *pTree)
{
    string exp;
    if(pTree->child.size() == 0)
    {
        if(pTree->symbol == "x")
        {
            return  "((double)d)";
        }
        else
        {
            return  pTree->symbol;
        }
    }

    for (size_t i = 0; i < pTree->child.size(); i++)
    {
        exp += compileToCIter(pTree->child.at(i));
    }

    return exp;
}
*/
