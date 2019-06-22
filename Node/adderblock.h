#ifndef ADDERBLOCK_H
#define ADDERBLOCK_H
#include "blockio.h"

class BlockIO;


class AdderBlock : public BlockIO
{
public:
    AdderBlock(int i);

    void init() override;
    void generateCode(QString dir) override;

    void generateOutputs();
};

#endif // ADDERBLOCK_H
