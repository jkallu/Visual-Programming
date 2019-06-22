#ifndef FORMULAWIDGET_H
#define FORMULAWIDGET_H

#include <QWidget>

class FormulaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FormulaWidget(QWidget *parent = nullptr);
    QPoint drawSqrt(const QPoint &pos, QString strVal, QPainter *qp);

signals:

public slots:
    void updateFormula(const QString &strForm);
protected:
    void paintEvent(QPaintEvent *event);
    void drawFormula(QPainter *qp);

private:
    QString strFormula;
};

#endif // FORMULAWIDGET_H
