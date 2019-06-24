#ifndef READMULTIFILESBLOCK_H
#define READMULTIFILESBLOCK_H
#include "blockio.h"
#include <QFile>
#include <QTextStream>
#include <QPlainTextEdit>
#include <QDebug>

class BlockIO;

class ReadMultiFilesBlock : virtual public BlockIO
{
public:
    ReadMultiFilesBlock(int i);
    void generateArrayOutputs(int num);
    int numberOfFiles();

    QLabel *lblFile;
    QPlainTextEdit *pteFilePaths;
    QStringList stringList;
};

#endif // READMULTIFILESBLOCK_H
