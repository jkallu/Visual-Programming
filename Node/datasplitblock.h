#ifndef DATASPLITBLOCK_H
#define DATASPLITBLOCK_H
#include "blockio.h"

class BlockIO;

class DataSplitBlock : virtual public BlockIO
{
public:
    DataSplitBlock(int i);

    void init() override;
    void generateCode(QString dir) override;
    //void setData(char *data) override;

    void generateOutputs();

    static int getNumInputs(){return  1;}
    static int getNumOutputs(){return 2;}
};

#endif // DATASPLITBLOCK_H
