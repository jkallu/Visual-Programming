#include <QPainter>
#include "formulawidget.h"
#include <QDebug>

FormulaWidget::FormulaWidget(QWidget *parent) : QWidget(parent)
{
    strFormula = "hi";
}

void FormulaWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter qp(this);
    drawFormula(&qp);
}

void FormulaWidget::drawFormula(QPainter *qp)
{
    QPen pen(Qt::blue, 2, Qt::SolidLine);
    qp->setPen(pen);

    drawSqrt(QPoint(0, 0), strFormula, qp);
}

void FormulaWidget::updateFormula(const QString &strForm)
{
    strFormula = strForm;
    this->repaint();
}

QPoint FormulaWidget::drawSqrt(const QPoint& pos, QString strVal, QPainter *qp)
{
    int strValWidth = qp->fontMetrics().width(strVal);
    int strValHeight = qp->fontMetrics().height();

    qp->drawLine(pos.x(), 4 + strValHeight / 2, pos.x() + 5, 4 + strValHeight);
    qp->drawLine(pos.x() + 5, 4 + strValHeight, pos.x() + 10, pos.y() + 1);
    qp->drawLine(pos.x() + 10, pos.y() + 1, pos.x() + 14 + strValWidth, pos.y() + 1);

    qp->drawText(QRect(pos.x() + 12, pos.y() + 4, pos.x() + 12 + strValWidth, pos.y() + 4 + strValHeight), strVal);
    return QPoint(pos.x() + strValWidth + 20, pos.y());
}
