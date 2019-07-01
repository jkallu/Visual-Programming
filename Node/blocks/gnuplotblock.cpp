#include "gnuplotblock.h"

GnuplotBlock::GnuplotBlock(int i):
    BlockIO(i, 2, 0, BlockItem::BlockType::Gnuplot)
{
    init();
}

void GnuplotBlock::init()
{
    widget = new QtGnuplotWidget;
    instance = new QtGnuplotInstance;


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
    draw();
}

void GnuplotBlock::draw()
{
    instance->setWidget(widget);
    *instance << "plot x w l lt 3\n";
    widget->show();
}
