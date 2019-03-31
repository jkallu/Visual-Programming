#ifndef GETMAXBLOCK_H
#define GETMAXBLOCK_H
#include "blockio.h"
#include <QDebug>

class BlockIO;

class GetMaxBlock : virtual public BlockIO
{
public:
    GetMaxBlock(int i);
    void generateOutputs();
};

#endif // GETMAXBLOCK_H
