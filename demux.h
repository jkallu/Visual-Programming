#ifndef DEMUX_H
#define DEMUX_H
#include "blockio.h"
#include <QTextEdit>

class BlockIO;

class DeMux : virtual public BlockIO
{
public:
    DeMux(int i, int nIn, int nOut);
    void generateCode(QString dir, QStringList list);

    static int getNumInputs(){return  1;}
    static int getNumOutputs(){return 1;}

    QTextEdit *teStates;
    QLabel *lblStates;

};

#endif // DEMUX_H
