#ifndef LINEDISPLAYBLOCK_H
#define LINEDISPLAYBLOCK_H
#include "blockio.h"

class BlockIO;


class LineDisplayBlock : virtual public BlockIO
{
public:
    LineDisplayBlock(int i);

    void generateCode(QString dir) override;
    void init() override;

    void generateOutputs();

    QLabel *lblOutDisplayName, *lblOutDisplayData;

};

#endif // LINEDISPLAYBLOCK_H
