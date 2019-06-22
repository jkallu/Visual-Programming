#ifndef READFILEBLOCK_H
#define READFILEBLOCK_H
#include "blockio.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

class BlockIO;

class ReadFileBlock : virtual public BlockIO
{
public:
    ReadFileBlock(int i);
    void generateArrayOutputs();

    QLabel *lblFile;
    QLineEdit *leFilePath;

};

#endif // READFILEBLOCK_H
