#ifndef DELAYBLOCK_H
#define DELAYBLOCK_H
#include "blockio.h"

class BlockIO;


class DelayBlock : public BlockIO
{
public:
    DelayBlock(int i);

    void init() override;
    void generateCode(QString dir) override;


    void generateOutputs();

    QLineEdit *leDelay;
    QLabel *lblDelay;

    int delay;
};

#endif // DELAYBLOCK_H
