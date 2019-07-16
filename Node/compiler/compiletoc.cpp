#include "compiletoc.h"

CompileToC::CompileToC()
{

}
string CompileToC::start(ParseTree_t *pTree, string typ)
{
    type = typ;
    return compileToCSetNotationIter(pTree);
}

string CompileToC::compileToCSetNotationIter(ParseTree_t *pTree)
{
    string exp;
    if(pTree->symbol == "SetNotation")
    {
        if(pTree->child.size() == 1)
        {
            return compileToCIter(pTree);
        }
        else if (pTree->child.size() > 1)
        {
            string strRet;
            for (size_t i = 2; i < pTree->child.size(); i++)
            {
                strRet += deSugar(pTree->child.at(i)->child.at(0));
            }
            return strRet;
        }
    }

    for (size_t i = 0; i < pTree->child.size(); i++)
    {
        exp += compileToCSetNotationIter(pTree->child.at(i));
    }

    return exp;
}

string CompileToC::deSugar(ParseTree_t *pTree)
{
    //for (size_t i = 2; i < pTree->child.size(); i++)
    //{
    //    ParseTree_t *pTree_chld = pTree->child.at(i);
    //    if(pTree_chld->symbol == "Generator")
    //    {

    cout <<"["<<__FILE__ "]["<<__LINE__ <<"]["<< __FUNCTION__ <<"] " << "GENERATOR " << pTree->child.at(1)->child.at(0)->symbol << " " << pTree->child.at(2)->child.at(0)->symbol << " " << pTree->child.at(4)->child.at(0)->symbol << endl;
    //    }
    //}
}

string CompileToC::compileToCIter(ParseTree_t *pTree)
{
    string exp;
    if(pTree->child.size() == 0)
    {
        if(pTree->symbol == "x")
        {
            if(type == "EXP")
            {
                return  "((double)d)";
            }
            else if(type == "GSLEXP")
            {
                return "y[0]";
            }
            else
            {
                return  pTree->symbol;
            }
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
