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
    file << "#include <string.h>\n"
            "#include <math.h>\n"
            "#include \"DeMuxBlock_0.h\"\n";
    file << "#include <stdio.h>\n\n";
    file << "extern pthread_mutex_t lock;\n"
            "extern PData_t *gPData;\n"
            "char *global_data;\n\n"
            "static int count;\n"
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

    file << "enum Types type;\n"
            "char *in = NULL;\n"
            "size_t size;\n"
            "getData(0, data, &type, &size, &in);\n"
            "size_t add = 0;\n"
            "if(type == Pack_Int)\n"
            "{\n"
                "for(size_t i = 0; i < size; i++)\n"
                "{\n"
                    "int d;\n"
                    "memcpy(&d, in + add, sizeof (int));\n"
                    "printf(\"%d\\n\", d);\n"
                    "add += sizeof (int);\n"
                "}\n"
            "}\n"
            "else if(type == Pack_Float)\n"
            "{\n"
                "for(size_t i = 0; i < size; i++)\n"
                "{\n"
                    "float d;\n"
                    "memcpy(&d, in + add, sizeof (float));\n"
                    "printf(\"%f\\n\", d);\n"
                    "add += sizeof (float);\n"
                "}\n"
            "}\n"
            "else if(type == Pack_Double)\n"
            "{\n"
                "for(size_t i = 0; i < size; i++)\n"
                "{\n"
                    "double d;\n"
                    "memcpy(&d, in + add, sizeof (double));\n"
                    "printf(\"%f\\n\", d);\n"
                    "add += sizeof (double);\n"
                "}\n"
            "}\n"
            ;

    file << "if(data != NULL)\n{\n"
            "deleteData(-1, &data);\n"
            "char callFunc[] = \"DeMuxBlock_0\";\n"
            "packData(&data, -1, Pack_func, strlen (callFunc) + 1, callFunc);\n"
            "char *strState;\n"
            "DeMuxBlock_0_StateType state = " << leName->text().toStdString()<<"_SUCCESS;\n"
            "strState = (char*)mallocAndCheck(sizeof(state));\n"
            "memcpy(strState, &state, sizeof(state));\n"
            "packData(&data, -2, Pack_State, sizeof(state), strState);\n"

            "localProcedureCall(callFunc, 1, 1, data);\n"
            "if(strState != NULL)\n{\n"
            "free(strState);\n}\n\n"

            "}\n"
            ;
    file << "if(data != NULL)\n{\n"
            "free(data);\n}\n\n"
            "if(in != NULL)\n{\n"
            "free(in);\n}\n\n"
            ;
    file << "printf(\""<<leName->text().toStdString()<<" END\\n\");\n";
    file << "count++;\n";
    file << "printf(\" COUNT %d \", count);\n";
    file << "pthread_exit(NULL);\n"
            "}";
    file.close();
}

void LocalProcedureBlock::preprocessScript()
{
    teScript->find("PACK_DATA");
}

