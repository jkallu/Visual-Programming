#ifndef CONSTANTBLOCK_H
#define CONSTANTBLOCK_H
#include "blockio.h"
#include <QLineEdit>

class BlockIO;

class ConstantBlock : virtual public BlockIO
{
public:
    ConstantBlock(int i);

    void init() override;
    void generateCode(QString dir) override;

    QLineEdit *leConstantVal;
    QLabel *lblConstVal;
};

#endif // CONSTANTBLOCK_H
