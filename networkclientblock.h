#ifndef NETWORKCLIENTBLOCK_H
#define NETWORKCLIENTBLOCK_H
#include "blockio.h"

#include <QTextEdit>

#include "simlinklist.h"

class BlockIO;


class NetworkClientBlock : virtual public BlockIO
{
public:
    NetworkClientBlock(int i, int nIn, int nOut);
    void generateCode(QString dir);
    void preprocessScript();
    static int getNumInputs(){return  1;}
    static int getNumOutputs(){return 0;}

    QTextEdit *teScript;
    QLabel *lblScript;
};

#endif // NETWORKCLIENTBLOCK_H
