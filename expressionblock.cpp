#include "expressionblock.h"

ExpressionBlock::ExpressionBlock(int i):
    BlockIO(i, 1, 1, BlockItem::BlockType::Expression)
{
    lblExp = new QLabel("Expression");

    leExpression = new QLineEdit;

    lblScript = new QLabel("Script");
    teScript = new QTextEdit;

    boxLayout->addWidget(lblExp);
    boxLayout->addWidget(leExpression);

    boxLayout->addWidget(lblScript);
    boxLayout->addWidget(teScript);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);

    groupBox->setTitle("Expression Block");
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
    file << "extern pthread_mutex_t lock;\n\n";
    file << "void * " << leName->text().toStdString() << "(void *dat) \n{\n";
    file << "char callFunc[] = \"" << lblOutConToBlock[0]->text().toStdString() << "\";\n";
    file << "size_t size = 200000;\n"
            "int *arr = (int *) malloc(size * sizeof (int));\n"
            "for(size_t i = 0; i < size; i++)\n"
            "{\n"
                "arr[i] = (int)i;\n"
            "}\n"
            "char *data = NULL; // always init pointer to NULL\n"
            "packData(&data, Pack_func, strlen (callFunc) , callFunc);\n"
            "packData(&data, Pack_Int, size, arr);\n"

            "pthread_mutex_lock(&lock);\n"
            "pushToBegin(&gPData, data);\n"
            "pthread_mutex_unlock(&lock);\n"
            "free(data);\n";
    file << teScript->toPlainText().toStdString() << "\n";
    file << "}";

    file.close();
}


