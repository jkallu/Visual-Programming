#include "localprocedureblock.h"


LocalProcedureBlock::LocalProcedureBlock(int i, int nIn, int nOut):
    BlockIO(i, nIn, nOut, BlockItem::BlockType::LocalProcedure)
{
    lblScript = new QLabel("Script");
    teScript = new QTextEdit;

    boxLayout->addWidget(lblScript);
    boxLayout->addWidget(teScript);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Local Procedure Block");

    //teScript->append("unsigned int size;\n");
    //teScript->append("memcpy(&size, data, sizeof(size));\n");
    //teScript->append("printf(\" SIZE %d\\n\", size);\n");
}

void LocalProcedureBlock::generateCode(QString dir)
{
    preprocessScript();

    std::ofstream fileHeader(QString(dir+leName->text()).toLatin1()+".h");
    QString upper = leName->text().toUpper();
    fileHeader << "#ifndef " << upper.toStdString() << "_H \n";
    fileHeader << "#define " << upper.toStdString() << "_H \n\n";
    fileHeader << "#include <stdio.h>\n";
    fileHeader << "#include \"packer.h\"\n";
    fileHeader << "#include <string.h>\n\n";
    //fileHeader << "#include \"datapack.h\"\n";
    for(int i = 0; i < numOfOutputs; i++)
    {
        fileHeader << "#include \"" << lblOutConToBlock[i]->text().toStdString() << ".h\"\n";
    }
    fileHeader << "void * " << leName->text().toStdString() << "(void *dat);\n\n";
    fileHeader << "#endif\n";

    std::ofstream file(QString(dir+leName->text()).toLatin1()+".c");
    file << "#include \"" << leName->text().toStdString() << ".h\"\n\n";
    file << "void * " << leName->text().toStdString() << "(void *dat) \n{\n";
    file << "char *data;\n"
            "data = (char*)dat;\n"
            "enum Types type;\n"
            "char *in = NULL;\n"
            "size_t size;\n"
            "getData(0, data, &type, &size, &in);\n"
            "size_t add = 0;\n"
            "for(unsigned int i = 0; i < size; i++)\n"
            "{\n"
            "int val = 0;\n"
            "memcpy(&val, in + add, sizeof (int));\n"
            "add += sizeof (int);\n"
            "printf(\"%d\\n\", val);\n"
            "}\n"
            "free(data);\n";
    file << teScript->toPlainText().toStdString() << "\n";
    file << "}";
}

void LocalProcedureBlock::preprocessScript()
{
    teScript->find("PACK_DATA");
}

