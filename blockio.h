#ifndef BLOCKIO_H
#define BLOCKIO_H

#include <QComboBox>
#include <QTextEdit>
#include "block.h"
#include "condition.h"
#include <vector>
#include "blockitem.h"
#include "./nodegencodes/packer.h"


class Condition;


class BlockIO : public Block
{

public:
    BlockIO(int id_l, int numOfIn, int numOfOut, BlockItem::BlockType typ);
    ~BlockIO();

    virtual void generateCode(QString dir);
    virtual void init();
    virtual void addHeader(QString header);
    virtual QString getDir();

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

    QLabel **lblIn, **lblOut, **lblOutConTo, *lblData;
    QLabel **lblInData, **lblOutData, **lblOutConToBlock;

    QTextEdit *teData;

    Condition condition;

    BlockItem::BlockType type;

//public slots:
    virtual void setData(char *data);
//signals:
  //  void dataChanged(char *data);
};

#endif // BLOCKIO_H
