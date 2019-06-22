#include "readfileblock.h"

ReadFileBlock::ReadFileBlock(int i):
    BlockIO(i, 0, 1, BlockItem::BlockType::ReadFile)
{

    lblFile = new QLabel("File path");
    leFilePath = new QLineEdit("/Users/jkallunk/intelligence/inputs/test_0.txt");

    boxLayout->addWidget(leFilePath);
    boxLayout->addWidget(lblFile);


    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Read File Block");

}

void ReadFileBlock::generateArrayOutputs(){
    QFile file(leFilePath->text());
    if (!file.open(QIODevice::ReadWrite)){
        qDebug() << "File could not open";
        return;
    }

    int dataCount = 0;
    QTextStream dsOut(&file);
    QString data;
    dsOut >> dataCount;
    qDebug() << " Data " << dataCount;
    if(dataCount > 0){
        dsOut >> data;
        createIOArray(1, 0, dataCount);
        int i = 0;
        while(i < dataCount){
            dsOut >> data;
            out[0][i] = data.toDouble();
            qDebug() << out[0][i];
            i++;
        }
        flagOut[0] = true;
    }
}

