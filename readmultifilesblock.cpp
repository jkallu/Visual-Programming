#include "readmultifilesblock.h"

ReadMultiFilesBlock::ReadMultiFilesBlock(int i):
    BlockIO(i, 0, 1, BlockItem::BlockType::ReadMultiFile)
{

    lblFile = new QLabel("File path");
    pteFilePaths = new QPlainTextEdit("/Users/jkallunk/intelligence/inputs/test_0.txt");

    boxLayout->addWidget(lblFile);
    boxLayout->addWidget(pteFilePaths);


    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Read Multi Files Block");
}

void ReadMultiFilesBlock::generateArrayOutputs(int num){
    qDebug() << stringList.at(num);
    QFile file(stringList.at(num));
    if (!file.open(QIODevice::ReadWrite)){
        //qDebug() << "File could not open";
        return;
    }

    int dataCount = 0;
    QTextStream dsOut(&file);
    QString data;
    dsOut >> dataCount;
    //qDebug() << " Data " << dataCount;
    if(dataCount > 0){
        dsOut >> data;
        createIOArray(1, 0, dataCount);
        int i = 0;
        while(i < dataCount){
            dsOut >> data;
            out[0][i] = data.toDouble();
            //qDebug() << out[0][i];
            i++;
        }
        flagOut[0] = true;
    }
}

int ReadMultiFilesBlock::numberOfFiles(){
    QString strFiles = pteFilePaths->toPlainText();
    stringList.clear();
    stringList.empty();
    stringList = strFiles.split("\n",QString::SkipEmptyParts);

    return stringList.length();
}
