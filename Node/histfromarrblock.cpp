#include "histfromarrblock.h"

HistFromArrBlock::HistFromArrBlock(int i):
    BlockIO(i, 1, 2, BlockItem::BlockType::HistFromArrayBlock)
{
    lblBins  = new QLabel("Bins");

    leBins = new QLineEdit("10");

    boxLayout->addWidget(lblBins);
    boxLayout->addWidget(leBins);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("HistFromArr Block");
}

void HistFromArrBlock::generateOutputs(){
    int size =  getSize(0, 0);

    int bins = leBins->text().toInt();

    if(bins < 1)
        bins = 1;

    createIOArray(1, 0, bins);
    createIOArray(1, 1, bins);

    // get max and min of array
    double max = -1.e300;
    double min = +1.e300;

    for(int j = 0; j < size; j++){
        if(in[0][j] > max)
            max = in[0][j];

        if(in[0][j] < min)
            min = in[0][j];
    }

    double dxBin = (max - min) / bins;

    // adjust the max and min to incude min and max values
    //max += dxBin / 10.;
    //min -= dxBin / 10.;

    // adjust the dxBin
    //dxBin = (max - min) / bins;

    for(int j = 0; j < bins; j++){
        out[0][j] = min + (j + 1) * dxBin;
        out[1][j] = 0.;
    }

    for(int j = 0; j < size; j++){
        for(int k = 0; k < bins; k++){
            if(k == bins - 1){
                if(in[0][j] >= out[0][k] - dxBin && in[0][j] <= out[0][k]){
                    out[1][k] += 1.;
                    break;
                }
            }
            else{
                if(in[0][j] >= out[0][k] - dxBin && in[0][j] < out[0][k]){
                    out[1][k] += 1.;
                    break;
                }
            }
        }
    }

    flagOut[0] = true;
    flagOut[1] = true;

}
