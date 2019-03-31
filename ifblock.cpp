#include "ifblock.h"

IfBlock::IfBlock(int i):
    BlockIO(i, 1, 2, BlockItem::BlockType::IfBlock)
{
    lblExp  = new QLabel("Expression");

    leExp = new QLineEdit;

    boxLayout->addWidget(lblExp);
    boxLayout->addWidget(leExp);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("If Block");
}

void IfBlock::generateOutputs(){
    int size =  getSize(0, 0);

    createIOArray(1, 0, size);
    createIOArray(1, 1, size);

    for(int j = 0; j < size; j++){
        QString str_x_expression = leExp->text();
        str_x_expression.replace(lblInData[0]->text(), QString::number(in[0][j]));
        QScriptEngine x_expression;
        QString str_fin_exp = "str_x_expression ";
        bool res = x_expression.evaluate(str_x_expression).toBool();
        qDebug() << str_x_expression << x_expression.evaluate(str_x_expression).toBool() << " resss";
        if(res){
            out[0][j] = in[0][j];
            out[1][j] = 0;
        }
        else{
            out[1][j] = in[0][j];
            out[0][j] = 0;
        }
    }

    flagOut[0] = true;
    flagOut[1] = true;
}
