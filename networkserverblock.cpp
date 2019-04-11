#include "networkserverblock.h"


NetworkServerBlock::NetworkServerBlock(int i, int nIn, int nOut):
    BlockIO(i, nIn, nOut, BlockItem::BlockType::NetworkServer)
{
    //lblScript = new QLabel("Script");
    //teScript = new QTextEdit;
    lblPort = new QLabel("Port");
    lePort = new QLineEdit("5001");

    boxLayout->addWidget(lblPort);
    boxLayout->addWidget(lePort);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Network server Block");

    //teScript->append("unsigned int size;\n");
    //teScript->append("memcpy(&size, data, sizeof(size));\n");
    //teScript->append("printf(\" SIZE %d\\n\", size);\n");
}

void NetworkServerBlock::generateCode(QString dir)
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
    file << "#include <stdio.h>\n"
            "#include <stdlib.h>\n"

            "#include <netdb.h>\n"
            "#include <netinet/in.h>\n"
            "\n";
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
            //"char *data = mallocAndCheck(tot_size);\n"
            //"memcpy(data, *ptr_global_data, tot_size);\n\n"
            "free(*ptr_global_data);\n"
            "*ptr_global_data = NULL;\n"
            "pthread_mutex_unlock(&global_lock);\n\n"
            ;
    file << "int sockfd = 0, newsockfd = 0, portno = "<< lePort->text().toStdString()<<", clilen = 0;\n"
            "char *data = NULL;\n"
            "struct sockaddr_in serv_addr, cli_addr;\n"
            "int  n;\n"

            "sockfd = socket(AF_INET, SOCK_STREAM, 0);\n"
            "if (sockfd < 0) \n{\n"
            "perror(\"ERROR opening socket\");\n"
            "exit(1);\n"
            "}\n"

            "bzero((char *) &serv_addr, sizeof(serv_addr));\n"
            "serv_addr.sin_family = AF_INET;\n"
            "serv_addr.sin_addr.s_addr = INADDR_ANY;\n"
            "serv_addr.sin_port = htons(portno);\n"

            "if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) \n{\n"
            "perror(\"ERROR on binding\");\n"
            "exit(1);\n"
            "}\n"

            "listen(sockfd,5);\n"
            "clilen = sizeof(cli_addr);\n"

            "newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);\n"

            "if (newsockfd < 0) {\n"
               "perror(\"ERROR on accept\");\n"
               "exit(1);\n"
            "}\n"

            "char strSize[sizeof (unsigned long)];\n"
            "bzero(strSize,sizeof (unsigned long));\n"
            "n = read( newsockfd, strSize, sizeof (unsigned long) );\n"

            "if (n < 0) \n{\n"
               "perror(\"ERROR reading from socket\");\n"
               "exit(1);\n"
            "}\n"

            "unsigned long size;\n"
            "memcpy(&size, strSize, sizeof (size));\n"

            "printf(\"Here is the size: %d\\n\",size);\n"

            "data = malloc(size);\n"

            "bzero(strSize,sizeof (unsigned long));\n"
            "n = read( newsockfd, data, size );\n"

            "if (n < 0) \n{\n"
               "perror(\"ERROR reading from socket\");\n"
               "exit(1);\n"
            "}\n"

            "char nm[] = \"" << lblOutConToBlock[0]->text().toStdString() <<"\";\n"
            "packData(&data, -1, Pack_func, strlen (nm) + 1, nm);\n"
            "localProcedureCall(nm, " << conToTotIns[0] << ", 1, data);\n"
            //"printf(\"%s\\n\", data);\n"
            ;

 /*   file << "enum Types type;\n"
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
            "if(in != NULL)\n{\n"
            "free(in);\n}\n\n"
            ;
*/
    /*file << "if(data != NULL)\n{\n"
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
            ;*/
    file << "if(data != NULL)\n{\n"
            "free(data);\n}\n\n"

            ;
    file << "printf(\""<<leName->text().toStdString()<<" END\\n\");\n";
    file << "count++;\n";
    file << "printf(\" COUNT %d \", count);\n";
    file << "pthread_exit(NULL);\n"
            "}";
    file.close();
}

void NetworkServerBlock::preprocessScript()
{
    //teScript->find("PACK_DATA");
}

