#ifndef GENERATEGAUSBLOCK_H
#define GENERATEGAUSBLOCK_H
#include "blockio.h"

class BlockIO;

class GenerateGausBlock : virtual public BlockIO
{
public:
    GenerateGausBlock(int i);
    void generateArrayOutputs();
    void init() override;
    void generateCode(QString dir) override;

    QLineEdit *leCount;
    QLabel *lblCount;
    QLineEdit *leMean;
    QLabel *lblMean;
    QLineEdit *leSigma;
    QLabel *lblSigma;
};

#endif // GENERATEGAUSBLOCK_H
