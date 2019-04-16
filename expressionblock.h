#ifndef EXPRESSIONBLOCK_H
#define EXPRESSIONBLOCK_H
#include "blockio.h"

#include <QtScript>
#include <QLineEdit>
#include <QTextEdit>

class BlockIO;

class ExpressionBlock : virtual public BlockIO
{
public:
    ExpressionBlock(int i);

    void generateCode(QString dir) override;
    void init() override;

    void generateOutputs();


    QLineEdit *leExpression;
    QLabel *lblExp;

    QTextEdit *teScript;
    QLabel *lblScript;
};

#endif // EXPRESSIONBLOCK_H
