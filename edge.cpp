#include "edge.h"
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

Edge::Edge(int id_l, Node *sourceNode, Node *destNode, QMenu *contextMenu):
    arrowSize(10)
{
    myContextMenu = contextMenu;
    id = id_l;
    source = sourceNode;
    dest = destNode;


    myColor = Qt::darkGreen;

    adjust();

    flagEnabled = true;

    //setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;


    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    arrowSize = dest->getRadius() / 2;

    sourcePoint = QPoint(source->scenePos().rx() - source->getRadius() / 2, source->scenePos().ry() - source->getRadius() / 2);
    destPoint = QPoint(dest->scenePos().rx() - dest->getRadius() / 2, dest->scenePos().ry() - dest->getRadius() / 2);

    //qDebug() << sourcePoint << destPoint;

    // Draw the line itself
    if(isSelected())
    painter->setPen(QPen(myColor, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

    else
        painter->setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));


    painter->drawLine(line);

    // Draw the arrows
    double angle = std::atan2(-line.dy(), line.dx());

    QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI / 3) * arrowSize);
    QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI - M_PI / 3) * arrowSize);
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->setBrush(myColor);
    //painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}

void Edge::adjust(){
    /*if (!source || !dest)
        return;

    //QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    QLineF line(source->pos(), dest->pos());
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }*/

    sourcePoint = source->scenePos();
    destPoint = dest->scenePos();
}

void Edge::resetEdges(){
    source->setConnectionFlag(false);
    dest->setConnectionFlag(false);
}

void Edge::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}
