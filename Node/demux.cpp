#include "demux.h"
#include <QLineEdit>

DeMux::DeMux(int i, int nIn, int nOut):
    BlockIO(i, nIn, nOut, BlockItem::BlockType::DeMux)
{
    init();
}

void DeMux::init()
{
    lblInitState = new QLabel("Initial state");
    leInitState = new QLineEdit;

    lblStates = new QLabel("States");
    teStates = new QTextEdit;

    boxLayout->addWidget(lblInitState);
    boxLayout->addWidget(leInitState);

    boxLayout->addWidget(lblStates);
    boxLayout->addWidget(teStates);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("DeMux Block");
}

void DeMux::generateCode(QString dir)
{
    std::ofstream fileHeader(QString(dir+leName->text()).toLatin1()+".h");
    QString upper = leName->text().toUpper();
    fileHeader << "#ifndef " << upper.toStdString() << "_H \n";
    fileHeader << "#define " << upper.toStdString() << "_H \n";
    fileHeader << "typedef enum {\n";
    //fileHeader << "MainBlock_0_SUCCESS,\n";
    QStringList lines = teStates->toPlainText()
                          .split('\n', QString::SkipEmptyParts);
    for(int i = 0 ; i < lines.size(); i++)
    {
       QStringList states = lines.at(i).split(QRegExp("\\s+"), QString::SkipEmptyParts);
       fileHeader << states.at(0).toStdString() << ",\n"
                     ;
    }

    fileHeader << "NUM_STATES\n"
                  "}" << leName->text().toStdString() << "_StateType;\n\n";
    fileHeader << "typedef struct {\n"
                  "" << leName->text().toStdString() << "_StateType state;\n"
                  "char funcName[100];\n"
                  "} StateMachineType;\n";
    fileHeader << "void * " << leName->text().toStdString() << "(void *dat);\n";
    fileHeader << "#endif\n";

    fileHeader.close();

    std::ofstream file(QString(dir+leName->text()).toLatin1()+".c");
    file << "#include \"" << leName->text().toStdString() << ".h\"\n";
    file << "#include \"linkedList.h\"\n";
    file << "#include \"packer.h\"\n";
    file << "#include <string.h>\n"
            "#include <math.h>\n";
    file << "#include <stdio.h>\n\n";
    file << "extern pthread_mutex_t lock;\n"
            "extern PData_t *gPData;\n"
            "char *global_data;\n\n"
            ;
    file << "StateMachineType stateMachine[] = {\n";
    for(int i = 0 ; i < lines.size(); i++)
    {
       QStringList states = lines.at(i).split(QRegExp("\\s+"), QString::SkipEmptyParts);
       if(states.size() >= 2)
       {
            file << " {" << states.at(0).toStdString() << ", \"" << states.at(1).toStdString() << "\"}";
       }
       else if(states.size() == 1)
       {
            file << " {" << states.at(0).toStdString() << ", \"*\" }";
       }

       if(i != lines.size() - 1)
       {
           file << ",\n";
       }
    }
    file << "\n};\n";


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
            "getData(-2, data, &type, &size, &in);\n"
            "deleteData(-1, &data);\n"
            "size_t add = 0;\n"
            "if(type == Pack_State)\n"
            "{\n"
                "DeMuxBlock_0_StateType state;\n"
                "memcpy(&state, in, sizeof (state));\n"
                "if(state < NUM_STATES)\n{\n"
                "   packData(&data, -1, Pack_func, strlen (stateMachine[state].funcName) + 1, stateMachine[state].funcName);\n"
                "   localProcedureCall(stateMachine[state].funcName, 1, 1, data);\n"
                "}\n"
            "}\n"
            ;

    file <<
            "if(data != NULL)\n{\n"
            "free(data);\n}\n\n"
            "if(in != NULL)\n{\n"
            "free(in);\n}\n\n"
            ;
    file << "printf(\""<<leName->text().toStdString()<<" END\\n\");\n";

    file << "pthread_exit(NULL);\n"
            "}";
    file.close();
}

