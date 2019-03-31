#ifndef GENERATEXYBLOCK_H
#define GENERATEXYBLOCK_H
#include "blockio.h"

class BlockIO;


class GenerateXYBlock: virtual public BlockIO
{
public:
    GenerateXYBlock(int i);
    void generateOutputs();
};

#endif // GENERATEXYBLOCK_H
