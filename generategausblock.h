#ifndef GENERATEGAUSBLOCK_H
#define GENERATEGAUSBLOCK_H
#include "blockio.h"
//#include <TRandom3.h>

class BlockIO;

class GenerateGausBlock : virtual public BlockIO
{
public:
    GenerateGausBlock(int i);
    void generateArrayOutputs();

    QLineEdit *leCount;
    QLabel *lblCount;
    QLineEdit *leMean;
    QLabel *lblMean;
    QLineEdit *leSigma;
    QLabel *lblSigma;
};

#endif // GENERATEGAUSBLOCK_H
