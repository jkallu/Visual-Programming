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
    void generateOutputs();
    void generateCode(QString dir);

    QLineEdit *leExpression;
    QLabel *lblExp;

    QTextEdit *teScript;
    QLabel *lblScript;
};

#endif // EXPRESSIONBLOCK_H
