#ifndef LINEDISPLAYBLOCK_H
#define LINEDISPLAYBLOCK_H
#include "blockio.h"

class BlockIO;


class LineDisplayBlock : virtual public BlockIO
{
public:
    LineDisplayBlock(int i);
    void generateOutputs();
    void generateCode(QString dir);

    QLabel *lblOutDisplayName, *lblOutDisplayData;

};

#endif // LINEDISPLAYBLOCK_H
