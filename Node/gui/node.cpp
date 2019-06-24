#include "node.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

Node::Node(IO io, int bType, int id_l, int tpId, int num, int totIn, int totOut, QGraphicsItem *parent):
    QGraphicsObject(parent)
{
    myIOType = io;
    myBlockType = bType;
    id = id_l;
    typeId = tpId;
    ioNumber = num;
    totOuts = totOut;
    totIns = totIn;
    //setFlag(ItemIsMovable);


    flagConnected = false;

    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    radius = 10;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    //painter->setBrush(Qt::darkGray);
    //painter->drawEllipse(-7, -7, 10, 10);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, radius, radius);
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 10 + adjust, 10 + adjust);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if(!flagConnected){
        emit connectionStarted(this, mouseEvent);
    }
}
