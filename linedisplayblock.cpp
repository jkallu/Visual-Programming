#include "linedisplayblock.h"

LineDisplayBlock::LineDisplayBlock(int i):
    BlockIO(i, 1, 0, BlockItem::BlockType::LineDisplay)
{
    lblOutDisplayName = new QLabel("Data Out");
    lblOutDisplayData = new QLabel();

    boxLayout->addWidget(lblOutDisplayName);
    boxLayout->addWidget(lblOutDisplayData);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Line Display Block");
}


void LineDisplayBlock::generateOutputs(){
    if(flagIn[0]){
        int size =  getSize(0, 0);
        QString strData;
        for(int j = 0; j < size; j++){
            strData += QString::number(in[0][j]) + " ";
        }
        lblOutDisplayData->setText(strData);
    }
}

void LineDisplayBlock::generateCode(QString dir)
{
    std::ofstream fileHeader(QString(dir+leName->text()).toLatin1()+".h");
    QString upper = leName->text().toUpper();
    fileHeader << "#ifndef " << upper.toStdString() << "_H \n";
    fileHeader << "#define " << upper.toStdString() << "_H \n";
    fileHeader << "#include <stdio.h>\n";
    fileHeader << "void " << leName->text().toStdString() << "(double *x, int size);\n";
    fileHeader << "#endif\n";

    std::ofstream file(QString(dir+leName->text()).toLatin1()+".c");
    file << "#include \"" << leName->text().toStdString() << ".h\"\n\n";
    file << "void " << leName->text().toStdString() << "(double *x, int size) \n{\n";
    file << "for (int i = 0; i < size; i++)\n{\n    printf(\"%f \", x[i]);\n}\n printf(\"\\n\");\n";
    file << "}";
}
