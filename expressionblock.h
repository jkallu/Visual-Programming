#ifndef EXPRESSIONBLOCK_H
#define EXPRESSIONBLOCK_H
#include "blockio.h"

#include <QtScript>
#include <QLineEdit>
#include <QTextEdit>

#include "formulawidget.h"
#include "lexer.h"
#include "earleyparser.h"


class BlockIO;
class FormulaWidget;
class Lexer;
class EarleyParser;

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

    QLabel *lblFormula;
    FormulaWidget *formulaWidget;

    Lexer *lexer;
    EarleyParser *earleyParser;
};

#endif // EXPRESSIONBLOCK_H
