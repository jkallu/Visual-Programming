#ifndef HISTFROMARRBLOCK_H
#define HISTFROMARRBLOCK_H
#include "blockio.h"

class BlockIO;

class HistFromArrBlock : virtual public BlockIO
{
public:
    HistFromArrBlock(int i);

    void generateOutputs();

    QLabel *lblBins;
    QLineEdit *leBins;
};

#endif // HISTFROMARRBLOCK_H
