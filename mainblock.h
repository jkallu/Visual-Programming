#ifndef MAINBLOCK_H
#define MAINBLOCK_H

#include "datapack.h"
#include "blockio.h"

#include <QTextEdit>

class BlockIO;
class DataPack;

class MainBlock : virtual public BlockIO
{
public:
    MainBlock(int i);

    void generateCode(QString dir) override;
    void init() override;

    void addHeader(QString header);
    void resetHeader();
    void generateMakefile(QString dir);
    void preprocessScript();
    void createEventLoopFiles(QString dir);
    void generateQtProjFile(QString dir);

    QTextEdit *teScript;
    QLabel *lblScript;

    QString strHeader, strSources;

    DataPack *dataPack;
};

#endif // MAINBLOCK_H
