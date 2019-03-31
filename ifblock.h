#ifndef IFBLOCK_H
#define IFBLOCK_H
#include "blockio.h"

#include <QtScript>

class BlockIO;

class IfBlock : virtual public BlockIO
{
public:
    IfBlock(int i);
    void generateOutputs();

    QLabel *lblExp;
    QLineEdit *leExp;
};

#endif // IFBLOCK_H
