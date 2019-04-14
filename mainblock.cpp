#include "mainblock.h"

MainBlock::MainBlock(int i):
    BlockIO (i, 0, 1, BlockItem::BlockType::MainBlock)
{
    lblScript = new QLabel("Script");
    teScript = new QTextEdit;

    boxLayout->addWidget(lblScript);
    boxLayout->addWidget(teScript);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);

    groupBox->setTitle("Main Block");

    /*teScript->append("char *data;\n");

    teScript->append("unsigned int size = sizeof(unsigned int) + sizeof (unsigned char);\n");
    teScript->append("data = (char *)mallocAndCheck(size);\n");
    teScript->append("if(data == NULL)\n");
    teScript->append("{\n");
    teScript->append("printf (\"Error\\n\" );\n");
    teScript->append("}\n");
    teScript->append("else\n");
    teScript->append("{\n");
    teScript->append("  memcpy(data, &size, sizeof(unsigned int));\n");
    teScript->append("  unsigned char  no_var = 0;\n");
    teScript->append("  memcpy(data + sizeof(unsigned int), &no_var, sizeof(unsigned char));\n");
    teScript->append("}\n");*/

    dataPack = new DataPack;
}

void MainBlock::generateCode(QString dir)
{
    preprocessScript();

    std::ofstream file(dir.toStdString() + "main.c");
    file << strHeader.toStdString() << "\n";
    file << "#include \"eventLoop.h\"\n\n";
    file << "int " << "main" << "() \n{\n";
    //file << teScript->toPlainText().toStdString() << "\n";
    file << "exec(\"" << lblOutConToBlock[0]->text().toStdString().c_str() << "\", NULL, 0, NULL);\n";
    file << "return 0;\n";
    file << "}";

    generateMakefile(dir);
    generateQtProjFile(dir);
    createEventLoopFiles(dir);
}

void MainBlock::preprocessScript()
{
    teScript->find("PACK_DATA");
}

void MainBlock::generateMakefile(QString dir)
{
    QStringList list = strSources.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    std::ofstream file(dir.toStdString() + "Makefile");
    file << "CC=gcc \n";
    file << "CFLAGS=-Wall -g -I.\n";

    file << "DEPS = ";
    for(int i = 0; i < list.size(); i++)
    {
        file << list.at(i).toStdString()<< ".h ";
    }
    file << "\n";

    file << "OBJ = main.o eventLoop.o linkedList.o packer.o ";
    for(int i = 0; i < list.size(); i++)
    {
        file << list.at(i).toStdString()<< ".o ";
    }
    file << "\n";

    file << "%.o: %.c $(DEPS)\n\t$(CC) -c -o $@ $< $(CFLAGS) -lpthread -lm \n";
    file << "gen: $(OBJ)\n\t$(CC) -o $@ $^ $(CFLAGS) -lpthread -lm \n";

    file << ".PHONY: clean\n";

    file << "clean:\n\trm -f ./*.o *~ core";

    file.close();
}

void MainBlock::generateQtProjFile(QString dir)
{
    std::ofstream file(dir.toStdString() + "gen.pro");
    file << "TEMPLATE = app\n"
            "CONFIG += console\n"
            "CONFIG -= app_bundle\n"
            "CONFIG -= qt\n\n";

    file << "SOURCES += \\ \n"
            "main.c \\ \n"
            "eventLoop.c \\ \n"
            "linkedList.c \\ \n"
            "packer.c \\ \n";

    QStringList list = strSources.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    for(int i = 0; i < list.size(); i++)
    {
        file << list.at(i).toStdString()<< ".c ";
        if(i == list.size() - 1)
        {
            file << "\n";
        }
        else
        {
           file << "\\ \n";
        }
    }

    file << "\n HEADERS += \\ \n"
            "eventLoop.h \\ \n"
            "linkedList.h \\ \n"
            "packer.h \\ \n";
    for(int i = 0; i < list.size(); i++)
    {
        file << list.at(i).toStdString()<< ".h ";
        if(i == list.size() - 1)
        {
            file << "\n";
        }
        else
        {
           file << "\\ \n";
        }
    }

    file << "\nLIBS += -lpthread \n";

    file.close();
}

void MainBlock::addHeader(QString header)
{
    if(strHeader.isEmpty())
    {
        strHeader.append("#include <stdio.h>\n");
        strHeader.append("#include <string.h>\n");
        strHeader.append("#include <stdlib.h>\n");
        //strHeader.append("#include \"datapack.h\"\n");
        //strSources.append("datapack ");
    }
    strHeader.append("#include \"" + header + ".h\"\n");
    strSources.append(header + " ");
}

void MainBlock::createEventLoopFiles(QString dir)
{
    QStringList list = strSources.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    std::ofstream file(dir.toStdString() + "eventLoop.c");
    file << "#include <stdio.h>\n"
            "#include \"eventLoop.h\"\n"
            "#include <pthread.h>\n"
            "#include <stdlib.h>\n"
            "#include <unistd.h>\n"
            "#include \"packer.h\"\n"
            "#include <string.h>\n"
            "#include \"DeMuxBlock_0.h\"\n";
    for(int i = 0; i < list.size(); i++)
    {
        file << "#include \"" << list.at(i).toStdString() << ".h\"\n";
    }

    file << "\n"
            "PData_t *gPData;\n"
            "pthread_mutex_t lock;\n\n"
            "char* global_data;\n\n"
            "PData_t **simPData = NULL;\n"
            "pthread_mutex_t *simLock;\n"
            "char flagSim;\n"
            "pthread_mutex_t global_lock;\n"

            "void exec(char callFunc[], pthread_mutex_t *sLock, char flagS, PData_t **simPD)\n"
            "{\n"
            "if(simPD != NULL)\n { \n simPData = simPD;\n}\n"
            "simLock = sLock;\n"
            "flagSim = flagS;\n\n"
            "gPData = NULL;\n"
            "char *data = NULL; // always init pointer to NULL\n\n"


            "packData(&data, -1, Pack_func, strlen(callFunc) + 1 , callFunc);\n\n"

            "char *strState;\n"
            "DeMuxBlock_0_StateType state = " << leName->text().toStdString()<<"_SUCCESS;\n"
            "strState = (char*)mallocAndCheck(sizeof(state));\n"
            "memcpy(strState, &state, sizeof(state));\n"
            "packData(&data, -2, Pack_State, sizeof(state), strState);\n"

            "/*if(pthread_mutex_init(&lock, NULL))\n"
            "{\n"
            "fprintf(stderr, \"Mutex init has failed\\n\");\n"
            "exit(1);\n"
            "}\n\n*/"
            //"printf(\"%ld\", &lock);\n"
            "//pthread_mutex_lock(&lock);\n"
            "char noIn = " << conToTotIns[0] << ";\n"
                                                "char nov = " << 1 << ";\n"
                                                                      "localProcedureCall(callFunc, noIn, nov, data);\n"
                                                                      "//pthread_mutex_unlock(&lock);\n\n"

                                                                      "pthread_t thread_id;\n"
                                                                      "if(pthread_create(&thread_id, NULL, eventLoop, NULL))\n"
                                                                      "{\n"
                                                                      "fprintf(stderr, \"Error creating thread\\n\");\n"
                                                                      "return;\n"
                                                                      "}\n"
                                                                      "if(!flagSim)\n{\n"
                                                                      "if(pthread_join(thread_id, NULL))\n"
                                                                      "{\n"
                                                                      "fprintf(stderr, \"Error joining thread\\n\");\n"
                                                                      "return;\n"
                                                                      "}\n"
                                                                      "pthread_mutex_destroy(&lock);\n"
                                                                      "}\n\n}\n"

                                                                      "void *eventLoop(void *dummy)\n"
                                                                      "{\n"
                                                                      "pthread_t thread_id[100];\n"
                                                                      "int countThreadId = 0;\n"
                                                                      "char *data = NULL;\n"
                                                                      "char *funcName = NULL;\n"
                                                                      "char **ptr_global_data = &global_data;\n"
                                                                      "*ptr_global_data = NULL;\n"
                                                                      "while(1)\n"
                                                                      "{\n"
                                                                      "popFilled(&data);\n"

                                                                      "if(flagSim && data != NULL)\n"
                                                                      "{\n"


                                                                      "pthread_mutex_lock(simLock);\n"
                                                                      "pushSim(simPData, data);\n"
                                                                      "printf(\"SIZE   FROM TH %ld\\n\", (*simPData)->size);\n"
                                                                      "pthread_mutex_unlock(simLock);\n"
                                                                      "}\n"
                                                                      "if(data != NULL)\n"
                                                                      "{\n"
                                                                      //"testData(data);\n"
                                                                      "getFuncName(data, &funcName);\n"
                                                                      "deleteData(-1, &data);\n"

                                                                      "size_t size;\n"
                                                                      "memcpy(&size, data, sizeof (size_t));\n"
                                                                      "*ptr_global_data = (char*)mallocAndCheck(size);\n"
                                                                      "memcpy(*ptr_global_data, data, size);\n"

            ;

    for(int i = 0; i < list.size(); i++)
    {
        if(i == 0)
        {
            file << "if";
        }
        else
        {
            file << "else if";
        }

        file << "(strcmp(funcName, \"" << list.at(i).toStdString() << "\") == 0)\n";

        file << "{\n";
        file << "if(pthread_create(&thread_id[countThreadId], NULL, " << list.at(i).toStdString() << ", NULL))\n"
                                                                                                     "{\n"
                                                                                                     "fprintf(stderr, \"Error creating thread\\n\");\n"
                                                                                                     "}\n"
                                                                                                     "else\n{\n"
                                                                                                     "countThreadId++;\n}\n"
                                                                                                     "}\n";
    }
    file << "else\n"
            "{\n"
            "while(pthread_mutex_trylock(&global_lock))\n"
            "{\n"
            "printf(\"\\rTRYING TO LOCK MUTEX %s\", __FUNCTION__);\n"
            "}\n"

            "free(*ptr_global_data);\n"
            "*ptr_global_data = NULL;\n"

            "pthread_mutex_unlock(&global_lock);\n"
            "}\n"
            "}\n";

    file << "// Never free data from here before the thread is expired\n"
            "if(data != NULL)\n{\n"
            "free (data);\n}\n"
            "data = NULL;\n"
            "if(funcName != NULL)\n{\n"
            "free (funcName);\n}\n"
            "funcName = NULL;\n"
            "while(pthread_mutex_trylock(&global_lock))\n"
            "{\n"
            "   printf(\"\\rTRYING TO LOCK MUTEX %s\", __FUNCTION__);\n"
            "}\n"
            "if(*ptr_global_data == NULL)\n"
            "{\n"
            "    pthread_mutex_unlock(&global_lock);\n"
            "    printf(\"\\rGLOBAL DATA IS NULL\");\n"
            "    usleep(10);\n"
            "}\n"
            "else\n"
            "{\n"
            "    pthread_mutex_unlock(&global_lock);\n"
            "    usleep(10);\n"
            "    while(1)\n"
            "    {\n"
            "        while(pthread_mutex_trylock(&global_lock))\n"
            "        {\n"
            "            printf(\"\\rTRYING TO LOCK MUTEX %s\", __FUNCTION__);\n"
            "        }\n"
            "        if(*ptr_global_data != NULL)\n"
            "        {\n"
            "            printf(\"\\rGLOBAL DATA IS NOT NULL\");\n"
            "            pthread_mutex_unlock(&global_lock);\n"
            "            usleep(10);\n"
            "        }\n"
            "        else\n"
            "        {\n"
            "            pthread_mutex_unlock(&global_lock);\n"
            "            break;\n"
            "        }\n"
            "    }\n"
            "}\n"
            "}\n"
            "pthread_exit(NULL);\n"
            "}\n";

    file << "void testData(char *dat)\n"
            "{\n"
            "printf(\"\\nTESTING DATA STARTED\\n\");\n"

            "enum Types type = Pack_func;\n"
            "size_t size_0 = 0, size_1 = 0, size_func = 0;\n"
            "char *data_0 = NULL, *data_1 = NULL, *data_func = NULL;\n"
            "getData(-1, dat, &type, &size_func, &data_func);\n"
            "printf(\"FUNC NAME %s\\n\", data_func);\n"
            "getData(0, dat, &type, &size_0, &data_0);\n"
            "getData(1, dat, &type, &size_1, &data_1);\n"

            "if(data_func != NULL)\n"
            "{\n"
                "free(data_func);\n"
                "data_func = NULL;\n"
            "}\n"
            "if(data_0 != NULL)\n"
            "{\n"
            "    free(data_0);\n"
            "    data_0 = NULL;\n"
            "}\n"

            "if(data_1 != NULL)\n"
            "{\n"
            "    free(data_1);\n"
            "    data_1 = NULL;\n"
            "}\n"

            "printf(\"\\nTESTING DATA END\\n\");\n"
            "}\n";


    std::ofstream fileHeader(dir.toStdString() + "eventLoop.h");
    fileHeader << "#ifndef EVENTLOOP_H\n"
                  "#define EVENTLOOP_H\n"
                  "#include <stdio.h>\n"
                  "#include \"linkedList.h\"\n\n"
                  "#ifdef __cplusplus\n"
                  "extern \"C\"\n"
                  "#endif\n\n"

                  "extern PData_t **simPData;\n"
                  "extern pthread_mutex_t *simLock;\n"
                  "extern char flagSim;\n\n"
                  "#ifdef __cplusplus\n"
                  "extern \"C\"\n"
                  "#endif\n\n"

                  "void exec(char *callFunc, pthread_mutex_t *simLock, char flagSim, PData_t **simPD);\n"
                  "void * eventLoop(void *dummy);\n"
                  "void testData(char *dat);\n\n"
                  "#endif // EVENTLOOP_H\n";
}

void MainBlock::resetHeader()
{
    strHeader.clear();
    strSources.clear();
}
