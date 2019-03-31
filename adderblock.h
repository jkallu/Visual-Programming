#ifndef ADDERBLOCK_H
#define ADDERBLOCK_H
#include "blockio.h"

class BlockIO;


class AdderBlock : public BlockIO
{
public:
    AdderBlock(int i);
    void generateOutputs();
};

#endif // ADDERBLOCK_H
