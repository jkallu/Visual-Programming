#ifndef EDGE_H
#define EDGE_H

#include "node.h"
#include <QGraphicsItem>
#include <QPainter>
#include <qmath.h>
#include <QDebug>
#include <QPen>


class QMenu;
class QGraphicsScene;
class QGraphicsSceneContextMenuEvent;

class Node;

class Edge : public QGraphicsItem
{
public:
    enum { Type = UserType + 3 };
    int type() const { return Type; }

    Edge(int id_l, Node *sourceNode, Node *destNode, QMenu *contextMenu);

    Node *sourceNode() const {return source;}
    Node *destNode() const {return dest;}
    void adjust();
    bool isEnabledOnScreen(){return flagEnabled;}
    void setFlagEnabledOnScreen(bool flagEn){flagEnabled = flagEn;}
    void resetEdges();
    int getId(){return id;}

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    int id;
    Node *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;

    qreal arrowSize;
    QColor myColor;
    bool flagEnabled;

    QMenu *myContextMenu;

};

#endif // EDGE_H
