#ifndef LOCALPROCEDUREBLOCK_H
#define LOCALPROCEDUREBLOCK_H
#include "blockio.h"

#include <QTextEdit>

#include "simlinklist.h"

class BlockIO;


class LocalProcedureBlock : virtual public BlockIO
{
public:
    LocalProcedureBlock(int i, int nIn, int nOut);

    void generateCode(QString dir) override;
    void init() override;

    void preprocessScript();
    static int getNumInputs(){return  1;}
    static int getNumOutputs(){return 0;}

    QTextEdit *teScript;
    QLabel *lblScript;
};

#endif // LOCALPROCEDUREBLOCK_H
