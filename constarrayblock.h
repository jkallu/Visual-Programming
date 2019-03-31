#ifndef CONSTARRAYBLOCK_H
#define CONSTARRAYBLOCK_H
#include "blockio.h"

class BlockIO;

class ConstArrayBlock : virtual public BlockIO
{
public:
    ConstArrayBlock(int i, int nIn, int nOut);
    void generateArrayOutputs();
    void generateCode(QString dir);
    static int getNumInputs(){return  1;}
    static int getNumOutputs(){return 1;}
    int setSimData(char *data);

    QLineEdit *leCount;
    QLabel *lblCount;
    QLineEdit *leBegin;
    QLabel *lblBegin;
    QLineEdit *leEnd;
    QLabel *lblEnd;
};

#endif // CONSTARRAYBLOCK_H
