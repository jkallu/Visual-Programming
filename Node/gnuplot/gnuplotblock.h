#ifndef GNUPLOTBLOCK_H
#define GNUPLOTBLOCK_H

#include "blockio.h"
#include "embed_example.h"

class GnuplotWidget;
class BlockIO;

class GnuplotBlock : virtual public BlockIO
{
public:
    GnuplotBlock(int i);

    void generateCode(QString dir) override;
    void init() override;
    void setData(char *data) override;

    GnuplotWidget* widget = new GnuplotWidget();
};

#endif // GNUPLOTBLOCK_H
