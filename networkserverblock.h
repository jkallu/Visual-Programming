#ifndef NETWORKSERVERBLOCK_H
#define NETWORKSERVERBLOCK_H
#include "blockio.h"

#include <QTextEdit>

#include "simlinklist.h"

class BlockIO;


class NetworkServerBlock : virtual public BlockIO
{
public:
    NetworkServerBlock(int i, int nIn, int nOut);
    void generateCode(QString dir);
    void preprocessScript();
    static int getNumInputs(){return  1;}
    static int getNumOutputs(){return 1;}

    //QTextEdit *teScript;
    QLabel *lblPort;
    QLineEdit *lePort;
};

#endif // NETWORKSERVERBLOCK_H
