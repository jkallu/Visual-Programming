#include "demux.h"

DeMux::DeMux(int i, int nIn, int nOut):
    BlockIO(i, nIn, nOut, BlockItem::BlockType::DeMux)
{
    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("DeMux Block");

}

void DeMux::generateCode()
{
    std::ofstream fileHeader(QString("../nodegencodes/"+leName->text()).toLatin1()+".h");
    QString upper = leName->text().toUpper();
    fileHeader << "#ifndef " << upper.toStdString() << "_H \n";
    fileHeader << "#define " << upper.toStdString() << "_H \n";
    fileHeader << "#include <stdio.h>\n";
    fileHeader << "#include <string.h>\n";
    fileHeader << "#include \"datapack.h\"\n";
    for(int i = 0; i < numOfOutputs; i++)
    {
        fileHeader << "#include \"" << lblOutConToBlock[i]->text().toStdString() << ".h\"\n";
    }
    fileHeader << "void " << leName->text().toStdString() << "(char *data);\n";
    fileHeader << "#endif\n";

    std::ofstream file(QString("../nodegencodes/"+leName->text()).toLatin1()+".c");
    file << "#include \"" << leName->text().toStdString() << ".h\"\n\n";
    file << "void " << leName->text().toStdString() << "(char *data) \n{\n";
    file << "unsigned int size;\n";
    file << "memcpy(&size, data, sizeof(size));\n";
    file << "printf(\" SIZE %d\\n\", size);\n";


    file << "}";
}

