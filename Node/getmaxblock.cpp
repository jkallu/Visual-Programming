#include "getmaxblock.h"

GetMaxBlock::GetMaxBlock(int i):
    BlockIO(i, 1, 1, BlockItem::BlockType::GetMax)
{
    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Get Maximum Block");
}


void GetMaxBlock::generateOutputs(){
    createIOArray(1, 0, 1);
    double max = -1.e300;
    int size = getSize(0, 0);
    for(int k = 0; k < size; k++){
        if(in[0][k] > max){
            max = in[0][k];
        }
    }
    out[0][0] = max;

    flagOut[0] = true;

    qDebug() << "max " << max;
}
