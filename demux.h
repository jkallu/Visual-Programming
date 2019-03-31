#ifndef DEMUX_H
#define DEMUX_H
#include "blockio.h"

class BlockIO;

class DeMux : virtual public BlockIO
{
public:
    DeMux(int i, int nIn, int nOut);
    void generateCode();

    static int getNumInputs(){return  1;}
    static int getNumOutputs(){return 1;}
};

#endif // DEMUX_H
