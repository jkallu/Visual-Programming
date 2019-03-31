#ifndef CONSTANTBLOCK_H
#define CONSTANTBLOCK_H
#include "blockio.h"
#include <QLineEdit>

class BlockIO;

class ConstantBlock : virtual public BlockIO
{
public:
    ConstantBlock(int i);

    QLineEdit *leConstantVal;
    QLabel *lblConstVal;
};

#endif // CONSTANTBLOCK_H
