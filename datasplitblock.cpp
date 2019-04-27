#include "datasplitblock.h"

DataSplitBlock::DataSplitBlock(int i):
    BlockIO(i, 1, 2, BlockItem::BlockType::Split)
{
    init();
}

void DataSplitBlock::init()
{
    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Split Block");
}

void DataSplitBlock::generateOutputs(){
    if(flagIn[0]){
        int size = getSize(0, 0);
        for(int i = 0; i < numOfOutputs; i++){
            createIOArray(1, i, size);
            for(int j = 0; j < size; j++){
                out[i][j] = in[0][j];
            }
            flagOut[i] = true;
        }
    }
}

void DataSplitBlock::generateCode(QString dir)
{
    std::ofstream fileHeader(QString(dir+leName->text()).toLatin1()+".h");
    QString upper = leName->text().toUpper();
    fileHeader << "#ifndef " << upper.toStdString() << "_H \n";
    fileHeader << "#define " << upper.toStdString() << "_H \n";

    fileHeader << "void * " << leName->text().toStdString() << "(void *dat);\n";
    fileHeader << "#endif\n";

    fileHeader.close();

    std::ofstream file(QString(dir+leName->text()).toLatin1()+".c");
    file << "#include \"" << leName->text().toStdString() << ".h\"\n";
    file << "#include \"linkedList.h\"\n";
    file << "#include \"packer.h\"\n";
    file << "#include <string.h>\n";
    file << "#include <stdio.h>\n\n";
    file << "extern pthread_mutex_t lock;\n"
            "extern PData_t *gPData;\n"
            "char *global_data;\n\n"
            ;
    file << "void * " << leName->text().toStdString() << "(void *dat) \n{\n";
    file << "while(pthread_mutex_trylock(&global_lock))\n"
            "{\n"
            "printf(\"\\rTRYING TO LOCK MUTEX %s\", __FUNCTION__);\n"
            "}\n";
    file << "char **ptr_global_data = &global_data;\n"
            "size_t tot_size;\n"
            "memcpy(&tot_size, *ptr_global_data, sizeof (tot_size));\n"
            "char *data = mallocAndCheck(tot_size);\n"
            "memcpy(data, *ptr_global_data, tot_size);\n\n"
            "free(*ptr_global_data);\n"
            "*ptr_global_data = NULL;\n"
            "pthread_mutex_unlock(&global_lock);\n\n"
            ;
    file << "char **callFunc = mallocAndCheck(" << numOfOutputs << "* sizeof (char *));\n"
            "char **data_out = mallocAndCheck(" << numOfOutputs << "* sizeof (char *));\n"
            ;
    file << "enum Types type;\n"
            "char *in = NULL;\n"
            "size_t size;\n"
            "getData(0, data, &type, &size, &in);\n"
            ;
    for(int i = 0; i < numOfOutputs; i++)
    {
        file << "char nm_" << i << "[] = \"" << lblOutConToBlock[i]->text().toStdString() <<"\";\n";
        file << "callFunc[" << i << "] = mallocAndCheck(sizeof (nm_" << i << ") + 1);\n";
        file << "memcpy(callFunc[" << i << "], nm_" << i << ", sizeof (nm_" << i << ") + 1);\n"
                "data_out[" << i << "] = NULL;\n"
                "packData(&data_out[" << i << "], -1, Pack_func, strlen (callFunc[" << i << "]) + 1, callFunc[" << i << "]);\n"
                "packData(&data_out[" << i << "], " << conToIONum[i] << ", type, size, in);\n"

                "localProcedureCall(callFunc[" << i << "], " << conToTotIns[i] << ", 1, data_out[" << i << "]);\n\n";

        file << "if(data_out[" << i << "] != NULL)\n{\n"
                "free(data_out[" << i << "]);\n}\n"
                "if(callFunc[" << i << "] != NULL)\n{\n"
                "free(callFunc[" << i << "]);\n}\n\n"
                ;
    }
    file << "if(data_out != NULL)\n{\n"
            "free(data_out);\n}\n"
            "if(callFunc != NULL)\n{\n"
            "free(callFunc);\n}\n\n"
            "if(data != NULL)\n{\n"
            "free(data);\n}\n\n"
            "if(in != NULL)\n{\n"
            "free(in);\n}\n\n";
    file << "printf(\""<<leName->text().toStdString()<<" END\\n\");\n";

    file << "pthread_exit(NULL);\n"
            "}";
    file.close();
}


