#include "constarrayblock.h"
#include "./nodegencodes/packer.h"

ConstArrayBlock::ConstArrayBlock(int i, int nIn, int nOut):
    BlockIO(i, nIn, nOut, BlockItem::BlockType::Array)
{
    //setId(i);
    //initBlock();

    leCount = new QLineEdit("10");
    leBegin = new QLineEdit("0");
    leEnd = new QLineEdit("10");


    lblCount = new QLabel("Count");
    lblBegin = new QLabel("Begin");
    lblEnd = new QLabel("End");

    lblType = new QLabel("Type");
    cbType = new QComboBox;
    for(int i = Pack_Char; i <= Pack_func; i++)
    {
        switch (i)
        {
        case Pack_Char:
            cbType->addItem("char");
            break;
        case Pack_Int:
            cbType->addItem("int");
            break;
        case Pack_Float:
            cbType->addItem("float");
            break;
        case Pack_Double:
            cbType->addItem("double");
            break;
        }

    }
    cbType->setCurrentIndex(1);

    boxLayout->addWidget(lblCount);
    boxLayout->addWidget(leCount);
    boxLayout->addWidget(lblBegin);
    boxLayout->addWidget(leBegin);
    boxLayout->addWidget(lblEnd);
    boxLayout->addWidget(leEnd);

    boxLayout->addWidget(lblType);
    boxLayout->addWidget(cbType);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Constant Array Block");
}

void ConstArrayBlock::generateArrayOutputs(){

    int constcount = leCount->text().toInt();

    double i_l = leBegin->text().toDouble();
    double i_r = leEnd->text().toDouble();

    double di = (i_r - i_l) / (double) constcount;

    for(int i = 0; i < numOfOutputs; i++)
    {
        createIOArray(1, i, constcount);
        for(int k = 0; k < constcount; k++){
            out[i][k] = i_l + (double)k * di;
        }
        //qDebug() << "array "<< constArrayBlock[j]->out[k];
    }
    flagOut[0] = true;
}

void ConstArrayBlock::generateCode(QString dir)
{
    int constcount = leCount->text().toInt();

    double i_l = leBegin->text().toDouble();
    double i_r = leEnd->text().toDouble();

    double di = (i_r - i_l) / (double) constcount;

    std::ofstream fileHeader(QString(dir+leName->text()).toLatin1()+".h");
    QString upper = leName->text().toUpper();
    fileHeader << "#ifndef " << upper.toStdString() << "_H \n";
    fileHeader << "#define " << upper.toStdString() << "_H \n";
    //for(int i = 0; i < numOfOutputs; i++)
    //{
        //fileHeader << "#include \"" << lblOutConToBlock[i]->text().toStdString() << ".h\"\n";
    //}
    fileHeader << "void * " << leName->text().toStdString() << "(void *dat);\n";
    fileHeader << "#endif\n";

    fileHeader.close();

    std::ofstream file(QString(dir+leName->text()).toLatin1()+".c");
    file << "#include \"" << leName->text().toStdString() << ".h\"\n";
    file << "#include \"linkedList.h\"\n";
    file << "#include \"packer.h\"\n";
    file << "#include <string.h>\n\n";
    file << "#include <stdio.h>\n\n";
    file << "char *global_data;\n\n"
            ;
    file << "void * " << leName->text().toStdString() << "(void *dat) \n{\n";

    file << "while(pthread_mutex_trylock(&global_lock))\n"
            "{\n"
            "printf(\"\\rTRYING TO LOCK MUTEX %s\", __FUNCTION__);\n"
            "}\n";
    file << "char **ptr_global_data = &global_data;\n"
            "free(*ptr_global_data);\n"
            "*ptr_global_data = NULL;\n"
            "pthread_mutex_unlock(&global_lock);\n\n"
            ;
    //file << "printf(\""<<leName->text().toStdString()<<" STARTED %ld\\n\", &lock);\n";
    Types type;
    QString strType = cbType->currentText();

    if(strType == "char")
    {
        type = Types::Pack_Char;
    }
    else if(strType == "int")
    {
        type = Types::Pack_Int;
    }
    else if(strType == "float")
    {
        type = Types::Pack_Float;
    }
    else if(strType == "double")
    {
        type = Types::Pack_Double;
    }


   qDebug() <<" CURR idx "<< cbType->currentIndex() <<" " <<Types::Pack_Int << strType;

    file << "size_t size = " << leCount->text().toInt() << ";\n"
         << strType.toStdString() << " *arr = (" << strType.toStdString() << " *) mallocAndCheck(size * sizeof (" << strType.toStdString() << "));\n";
    file << "double i_l = " << i_l << ";\n";
    file << "double i_r = " << i_r << ";\n";
    file << "double di = " << di << ";\n";
    file << "for(size_t i = 0; i < size; i++)\n"
            "{\n"
                "arr[i] = (i_l + (double)i * di);\n"
            "}\n\n"
            "char **callFunc = mallocAndCheck(" << numOfOutputs << " * sizeof (char *));\n"
            "char **data = mallocAndCheck(" << numOfOutputs << "* sizeof (char *));\n"
            ;
    for(int i = 0; i < numOfOutputs; i++)
    {
        file << "char nm_" << i << "[] = \"" << lblOutConToBlock[i]->text().toStdString() <<"\";\n";
        file << "callFunc[" << i << "] = mallocAndCheck(sizeof (nm_" << i << ") + 1);\n";
        file << "memcpy(callFunc[" << i << "], nm_" << i << ", sizeof (nm_" << i << ") + 1);\n"
                "data[" << i << "] = NULL;\n"
                "packData(&data[" << i << "], -1, Pack_func, strlen (callFunc[" << i << "]) + 1, callFunc[" << i << "]);\n"
                "packData(&data[" << i << "], " << conToIONum[i] << ", " << type << ", size, arr);\n"

                "localProcedureCall(callFunc[" << i << "], " << conToTotIns[i] << ", 1, data[" << i << "]);\n"

                "if(data[" << i << "] != NULL)\n{\n"
                "free(data[" << i << "]);\n}\n"
                "if(callFunc[" << i << "] != NULL)\n{\n"
                "free(callFunc[" << i << "]);\n}\n\n"
                ;
    }
    file << "if(data != NULL)\n{\n"
            "free(data);\n}\n"
            "if(callFunc != NULL)\n{\n"
            "free(callFunc);\n}\n\n"
            "if(arr != NULL)\n{\n"
            "free(arr);\n}\n\n";

    file << "printf(\""<<leName->text().toStdString()<<" END\\n\");\n";

    file << "}";

    file.close();
}

int ConstArrayBlock::setSimData(char *data)
{

}

