#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWheelEvent>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
protected:
    void wheelEvent(QWheelEvent *event)
    {
        qreal deltaScale = 1;
        deltaScale += event->delta() > 0 ? 0.1 : -0.1;
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        scale(deltaScale, deltaScale);
    }
public:
    MyGraphicsView();
};

#endif // MYGRAPHICSVIEW_H
