#ifndef DATASPLITBLOCK_H
#define DATASPLITBLOCK_H
#include "blockio.h"

class BlockIO;

class DataSplitBlock : virtual public BlockIO
{
public:
    DataSplitBlock(int i);
    void generateOutputs();
    void generateCode(QString dir);
    static int getNumInputs(){return  1;}
    static int getNumOutputs(){return 2;}
};

#endif // DATASPLITBLOCK_H
