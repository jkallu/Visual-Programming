#ifndef GNUPLOTBLOCK_H
#define GNUPLOTBLOCK_H

#include "blockio.h"
#include "embed_example.h"


#include "QtGnuplotWidget.h"
#include "QtGnuplotInstance.h"

class QtGnuplotWidget;
class QtGnuplotInstance;


class GnuplotWidget;
class BlockIO;
class QtGnuplot;

class GnuplotBlock : virtual public BlockIO
{
public:
    GnuplotBlock(int i);

    void generateCode(QString dir) override;
    void init() override;
    void setData(char *data) override;

    void draw(QVector<QPointF> *points);

    //GnuplotWidget* widget;

    QtGnuplotWidget* widget;
    QtGnuplotInstance *instance;
};

#endif // GNUPLOTBLOCK_H
