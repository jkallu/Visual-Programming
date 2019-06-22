#include "expressionblock.h"

ExpressionBlock::ExpressionBlock(int i):
    BlockIO(i, 1, 1, BlockItem::BlockType::Expression)
{
    init();

    //gslTest = new GSLTest;
    //gslTest->odeSolution();
}

void ExpressionBlock::init()
{
    lblExp = new QLabel("Expression");

    leExpression = new QLineEdit("sin(x)");

    lblScript = new QLabel("Script");
    teScript = new QTextEdit;

    lblFormula = new QLabel("Formula");
    formulaWidget = new FormulaWidget;
    formulaWidget->setFixedHeight(100);


    boxLayout->addWidget(lblExp);
    boxLayout->addWidget(leExpression);

    boxLayout->addWidget(lblFormula);
    boxLayout->addWidget(formulaWidget);

    boxLayout->addWidget(lblScript);
    boxLayout->addWidget(teScript);


    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);

    groupBox->setTitle("Expression Block");

    connect(leExpression, SIGNAL(textChanged(const QString &)), formulaWidget, SLOT(updateFormula(const QString &)));
}

void ExpressionBlock::generateOutputs(){
    int size =  getSize(0, 0);
    createIOArray(1, 0, size);
    for(int j = 0; j < size; j++){
        QString str_x_expression = leExpression->text();
        str_x_expression.replace(lblInData[0]->text(), QString::number(in[0][j]));
        QScriptEngine x_expression;
        out[0][j] = x_expression.evaluate(str_x_expression).toNumber();
        //qDebug() << out[0][j];
    }
    flagOut[0] = true;
}

void ExpressionBlock::generateCode(QString dir)
{
    lexer = new Lexer(leExpression->text().toStdString(), false);
    earleyParser = new EarleyParser;
    string compiledExp = earleyParser->parse(lexer->allTokens(), "EXP");

    delete lexer;
    delete earleyParser;


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
            "#include <math.h>\n";
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
            "size_t add = 0;\n"
            "if(type == Pack_Int)\n"
            "{\n"
                "for(size_t i = 0; i < size; i++)\n"
                "{\n"
                    "int d;\n"
                    "memcpy(&d, in + add, sizeof (int));\n"
                    //"d = " << leExpression->text().toStdString() <<"((double)d);\n"
                    "d = " << compiledExp << ";\n"
                    "memcpy(in + add, &d, sizeof (int));\n"
                    "add += sizeof (int);\n"
                "}\n"
            "}\n"
            "else if(type == Pack_Float)\n"
            "{\n"
                "for(size_t i = 0; i < size; i++)\n"
                "{\n"
                    "float d;\n"
                    "memcpy(&d, in + add, sizeof (float));\n"
                    //"d =  " << leExpression->text().toStdString() <<"((double)d);\n"
                    "d = " << compiledExp << ";\n"
                    "memcpy(in + add, &d, sizeof (float));\n"
                    "add += sizeof (float);\n"
                "}\n"
            "}\n"
            "else if(type == Pack_Double)\n"
            "{\n"
                "for(size_t i = 0; i < size; i++)\n"
                "{\n"
                    "double d;\n"
                    "memcpy(&d, in + add, sizeof (double));\n"
                    //"d =  " << leExpression->text().toStdString() <<"(d);\n"
                    "d = " << compiledExp << ";\n"
                    "memcpy(in + add, &d, sizeof (double));\n"
                    "add += sizeof (double);\n"
                "}\n"
            "}\n"
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
            "free(in);\n}\n\n"
            ;
    file << "printf(\""<<leName->text().toStdString()<<" END\\n\");\n";

    file << "pthread_exit(NULL);\n"
            "}";
    file.close();
}


