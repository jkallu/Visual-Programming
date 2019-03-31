#include "generatexyblock.h"

GenerateXYBlock::GenerateXYBlock(int i):
    BlockIO(i, 1, 2, BlockItem::BlockType::GenerateXY)
{
    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("GenerateXY Block");
}

void GenerateXYBlock::generateOutputs(){
    int size =  getSize(0, 0);
    createIOArray(1, 0, size);
    createIOArray(1, 1, size);
    for(int j = 0; j < size; j++){
        out[0][j] = j; // x
        out[1][j] = in[0][j]; // y
    }
    flagOut[0] = true;
    flagOut[1] = true;
}
