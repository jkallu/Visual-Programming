#ifndef GSLBLOCK_H
#define GSLBLOCK_H

#include "blockio.h"

class BlockIO;

class GSLBlock : virtual public BlockIO
{
public:
    GSLBlock(int i, BlockItem::BlockType type);

    void init() override;
    void generateCode(QString dir) override;

    QLineEdit *leExpression;
    QLabel *lblExp;
};

#endif // GSLBLOCK_H
