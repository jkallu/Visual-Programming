#include "generategausblock.h"

GenerateGausBlock::GenerateGausBlock(int i):
    BlockIO(i, 0, 1, BlockItem::BlockType::GenerateGaus)
{

    leCount = new QLineEdit("100");
    leMean = new QLineEdit("0");
    leSigma = new QLineEdit("2");

    lblCount = new QLabel("Count");
    lblMean = new QLabel("Mean");
    lblSigma = new QLabel("Sigma");

    boxLayout->addWidget(lblCount);
    boxLayout->addWidget(leCount);
    boxLayout->addWidget(lblMean);
    boxLayout->addWidget(leMean);
    boxLayout->addWidget(lblSigma);
    boxLayout->addWidget(leSigma);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Generate Gaus Block");
}

void GenerateGausBlock::generateArrayOutputs(){
    int countGaus = leCount->text().toInt();
    double mean = leMean->text().toDouble();
    double sigma = leSigma->text().toDouble();

    //TRandom3 rand3;

    createIOArray(1, 0, countGaus);

    for(int k = 0; k < countGaus; k++){
        //out[0][k] = rand3.Gaus(mean, sigma);
    }
    flagOut[0] = true;
}
