#include "delayblock.h"

DelayBlock::DelayBlock(int i):
    BlockIO(i, 1, 1, BlockItem::BlockType::Delay)
{
    init();
}

void DelayBlock::init()
{
    lblDelay = new QLabel("Delay");
    leDelay = new QLineEdit;

    boxLayout->addWidget(lblDelay);
    boxLayout->addWidget(leDelay);

    boxLayout->rowStretch(1);
    groupBox->setLayout(boxLayout);

    groupBox->setTitle("Delay Block");
}

void DelayBlock::generateCode(QString dir)
{

}

void DelayBlock::generateOutputs(){
    delay = leDelay->text().toInt();
    int size = getSize(0, 0);
    createIOArray(1, 0, size);
    for(int i = 0; i < size; i++){
        int delCount = i - delay;
        if(delCount < 0 || delCount >= size){
          out[0][i] = 0.;
        }
        else{
          out[0][i] = in[0][delCount];
        }
    }
    flagOut[0] = true;
}

