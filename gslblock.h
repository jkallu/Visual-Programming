#ifndef GSLBLOCK_H
#define GSLBLOCK_H

#include "blockio.h"
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QTextDocument>
#include <QString>
#include <QTextBlock>

#include "lexer.h"
#include "earleyparser.h"

class BlockIO;
class Lexer;
class EarleyParser;

class GSLBlock : virtual public BlockIO
{
public:
    GSLBlock(int i, BlockItem::BlockType type);

    void init() override;
    void generateCode(QString dir) override;

    QLineEdit *leExpression;
    QLabel *lblExp;

    QLabel *lblParms;
    QTextEdit *teParms;

    Lexer *lexer;
    EarleyParser *earleyParser;
};

#endif // GSLBLOCK_H
