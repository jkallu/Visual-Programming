#ifndef ACCUMULATORBLOCK_H
#define ACCUMULATORBLOCK_H
#include "blockio.h"

class BlockIO;

class AccumulatorBlock : public BlockIO
{
public:
    AccumulatorBlock(int i);
    void generateOutputs();
};

#endif // ACCUMULATORBLOCK_H
