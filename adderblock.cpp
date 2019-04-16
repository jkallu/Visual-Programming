#include "adderblock.h"

AdderBlock::AdderBlock(int i):
    BlockIO(i, 2, 1, BlockItem::BlockType::Adder)
{
    init();
}

void AdderBlock::init()
{
    boxLayout->rowStretch(1);
    groupBox->setLayout(boxLayout);

    groupBox->setTitle("Adder Block");
}

void AdderBlock::generateCode(QString dir)
{

}

void AdderBlock::generateOutputs(){
    int size = getSize(0, 0);
    createIOArray(1, 0, size);
    for(int i = 0; i < size; i++){
        out[0][i] = in[0][i] + in[1][i];
    }
    flagOut[0] = true;
}
