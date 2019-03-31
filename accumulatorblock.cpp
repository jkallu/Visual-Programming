#include "accumulatorblock.h"

AccumulatorBlock::AccumulatorBlock(int i):
    BlockIO(i, 1, 1, BlockItem::BlockType::Accumulator)
{
    boxLayout->rowStretch(1);
    groupBox->setLayout(boxLayout);

    groupBox->setTitle("Accumulator Block");
}

void AccumulatorBlock::generateOutputs(){
    int size = getSize(0, 0);

    createIOArray(1, 0, size);

    double accum = 0.;

    for(int i = 0; i < size; i++){
        if(i > 0)
            accum += in[0][i];

        out[0][i] = accum;
    }

    flagOut[0] = true;
}
