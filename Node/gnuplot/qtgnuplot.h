#ifndef QTGNUPLOT_H
#define QTGNUPLOT_H

#include "QtGnuplotWidget.h"
#include "QtGnuplotInstance.h"

class QtGnuplotWidget;
class QtGnuplotInstance;

class QtGnuplot
{
public:
    QtGnuplot();
    void plot();

private:
    QtGnuplotWidget* widget;
    QtGnuplotInstance *instance;
};

#endif // QTGNUPLOT_H
