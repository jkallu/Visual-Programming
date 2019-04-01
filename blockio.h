#ifndef BLOCKIO_H
#define BLOCKIO_H

#include <QComboBox>
#include "block.h"
#include "condition.h"
#include <vector>
#include "blockitem.h"
#include "/home/jin/qt_pgms/nodegencodes/packer.h"

class Condition;


class BlockIO : public Block
{
public:
    BlockIO(int id_l, int numOfIn, int numOfOut, BlockItem::BlockType typ);
    ~BlockIO();


    double **in, **out;
    void createIOArray(int io, int num, size_t size); // io  =  0 for input, 1 for output, num is the the index of io
    void reset();
    int getSize(int io, int num);
    bool isExecutedFull();
    void setIOConts(int n_in, int n_out);
    std::vector <int> getIOCounts();
    BlockItem::BlockType getType();
    int getFinalNoIns();
    int getFinalNoOuts();

    bool *flagIn, *flagOut;
    int numOfInputs, numOfOutputs;
    int *sizeIn;
    int *sizeOut;
    int *conToIONum;
    int *conToTotIns;

    QLabel **lblIn, **lblOut, **lblOutConTo;
    QLabel **lblInData, **lblOutData, **lblOutConToBlock;

    Condition condition;

    BlockItem::BlockType type;

};

#endif // BLOCKIO_H