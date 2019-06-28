#include "gnuplotblock.h"

GnuplotBlock::GnuplotBlock(int i):
    BlockIO(i, 2, 0, BlockItem::BlockType::Gnuplot)
{
    init();
}

void GnuplotBlock::init()
{
    widget = new GnuplotWidget();
    widget->plot();

    boxLayout->addWidget(widget, 4, 0, 1, 2);
    lblData->setVisible(false);
    teData->setVisible(false);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Gnuplot Block");
}

void GnuplotBlock::generateCode(QString dir)
{

}

void GnuplotBlock::setData(char *data)
{

}
