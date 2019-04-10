#ifndef BLOCKITEM_H
#define BLOCKITEM_H

#include "node.h"
#include <QDebug>
#include <QPainter>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

class Node;
//class QGraphicsSceneMouseEvent;
//class QGraphicsItem;
//class QGraphicsScene;
class QMenu;
class QStyleOptionGraphicsItem;
class QGraphicsSceneMouseEvent;
class QGraphicsScene;
class QGraphicsSceneContextMenuEvent;

class BlockItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + 2 };
    int type() const { return Type; }

    enum Mode {MoveItem, ConnectItem};
    enum BlockType {Constant, Array, Expression, Graph, Split, Adder, Delay, Accumulator, ReadFile,
                    GetMax, LineDisplay, IfBlock, HistFromArrayBlock, FillHist, ReadMultiFile, GenerateGaus,
                   GenerateXY, MainBlock, DeMux, LocalProcedure, NetworkClient, NetworkServer};
    BlockItem(BlockType blockType, int id_l, int tpId, QMenu *contextMenu, int nIn, int nOut);
    BlockType diagramType() const { return myBlockType; }
    QPolygonF polygon() const { return myPolygon; }
    //int type() const override { return Type;}
    void createInputNodes(int num);
    void creatOutputNodes(int num);

    int getNoInputNodes() {return noInputNodes;}
    int getNoOutputNodes() {return noOutputNodes;}
    int getId(){return id;}
    int getTypeId(){return typeId;}
    int getType(){return myBlockType;}

    bool isEnabled(){return flagEnabled;}
    void setEnabled(bool flagEn){flagEnabled = flagEn;}

    Node *getInputNode(int i) {if(i < noInputNodes) return inputNodes[i];}
    Node *getOutputNode(int i) {if(i < noOutputNodes) return outputNodes[i];}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    QPixmap image() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

public slots:
    void nodeEmittedClickeEvent(Node *node, QGraphicsSceneMouseEvent *mouseEvent);

signals:
    void nodeConnectionStarted(Node *node,QGraphicsSceneMouseEvent *mouseEvent);
    void blockItemClicked(BlockItem *item, QGraphicsSceneMouseEvent *mouseEvent);


private:
    BlockType myBlockType;
    QPolygonF myPolygon;
    QPainterPath painterpath;
    Node **inputNodes, **outputNodes;
    QPoint arrayWH;

    int noInputNodes, noOutputNodes;
    int id, typeId;
    QString name;
    bool flagEnabled;
    QMenu *myContextMenu;

    QColor colorLight, colorDark;



};

#endif // BLOCKITEM_H
