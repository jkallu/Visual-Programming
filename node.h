#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QDebug>

class QGraphicsSceneMouseEvent;
class QGraphicsItem;
class QGraphicsScene;

class Node : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + 1};
    int type() const { return Type; }

    enum IO{Input, Output};

    Node(IO io, int bType, int id_l, int tpId, int num, int totIn, int totOut, QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    void setConnectionFlag(bool flag){flagConnected = flag;}
    bool getConnectionFlag() {return flagConnected;}

    IO getIOType(){ return myIOType;}
    int getId(){return id;}
    int gettypeId(){return typeId;}
    int getNumber(){return ioNumber;}
    int getBlockType(){return myBlockType;}
    int getRadius(){return radius;}
    int getTotIns(){return totIns;}
    int getTotOuts(){return totOuts;}

signals:
    void connectionStarted(Node *node, QGraphicsSceneMouseEvent *mouseEvent);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    bool flagConnected;
    IO myIOType;
    int myBlockType;
    int id, typeId;
    int ioNumber;
    int radius;
    int totIns;
    int totOuts;

};

#endif // NODE_H
