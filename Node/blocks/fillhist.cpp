#include "fillhist.h"

FillHist::FillHist(int i):
    BlockIO(i, 1, 2, BlockItem::BlockType::FillHist)
{
    lblBins  = new QLabel("Bins");
    leBins = new QLineEdit("10");

    lblBegin  = new QLabel("Begin");
    leBegin = new QLineEdit("0");

    lblEnd  = new QLabel("End");
    leEnd = new QLineEdit("10");

    boxLayout->addWidget(lblBins);
    boxLayout->addWidget(leBins);

    boxLayout->addWidget(lblBegin);
    boxLayout->addWidget(leBegin);

    boxLayout->addWidget(lblEnd);
    boxLayout->addWidget(leEnd);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("FillHist Block");

    flagInit = false;
}

void FillHist::generateOutputs(){

    if(!flagInit){
        size =  getSize(0, 0);
        bins = leBins->text().toInt();

        if(bins < 1)
            bins = 1;




        min = leBegin->text().toDouble();
        max = leEnd->text().toDouble();

        dxBin = (max - min) / bins;

        createIOArray(1, 0, bins);
        createIOArray(1, 1, bins);

        for(int j = 0; j < bins; j++){
            out[0][j] = min + j * dxBin;
            out[1][j] = 0.;
        }

        flagInit = true;
    }

    for(int i = 0; i < size; i++){
        qDebug() << " Fill hist ";
        if(in[0][i] >= min && in[0][i] < max){
            int b =  in[0][i] / dxBin;
            qDebug() << " Fill hist "<< b;
            out[1][b] += 1.;
        }
    }


    flagOut[0] = true;
    flagOut[1] = true;
}
