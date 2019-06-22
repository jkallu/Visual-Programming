#ifndef FILLHIST_H
#define FILLHIST_H
#include "blockio.h"
#include <QDebug>

class BlockIO;


class FillHist : virtual public BlockIO
{
public:
    FillHist(int i);

    void generateOutputs();

    QLabel *lblBins;
    QLineEdit *leBins;

    QLabel *lblBegin;
    QLineEdit *leBegin;

    QLabel *lblEnd;
    QLineEdit *leEnd;

    bool flagInit;
    int bins;
    int size;

    double min, max;
    double dxBin;

};

#endif // FILLHIST_H
