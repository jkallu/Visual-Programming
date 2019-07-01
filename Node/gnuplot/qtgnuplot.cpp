#include "qtgnuplot.h"

QtGnuplot::QtGnuplot()
{
    widget = new QtGnuplotWidget;
    instance = new QtGnuplotInstance;
    instance->setWidget(widget);
}

void QtGnuplot::plot()
{
    *instance <<  "plot x w l lt 3\n";
}
