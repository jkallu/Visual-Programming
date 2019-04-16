#ifndef DEMUX_H
#define DEMUX_H
#include "blockio.h"
#include <QTextEdit>

class BlockIO;

class DeMux : virtual public BlockIO
{
public:
    DeMux(int i, int nIn, int nOut);

    void init() override;
    void generateCode(QString dir) override;

    static int getNumInputs(){return  1;}
    static int getNumOutputs(){return 1;}

    QTextEdit *teStates;
    QLabel *lblStates;

    QLabel *lblInitState;
    QLineEdit *leInitState;

};

#endif // DEMUX_H
