#ifndef BLOCKSCENE_H
#define BLOCKSCENE_H

#include "node.h"
#include <QGraphicsScene>
#include "edge.h"
#include "blockitem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QVBoxLayout>
#include "manageblocks.h"
#include <QWidget>
#include <exception>
#include <QSpinBox>


#define MAX_BLOCKS 10000

class ManageBlocks;
class BlockItem;
class Edge;
class Node;
class QGraphicsSceneMouseEvent;

class BlockScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };
    explicit BlockScene(QMenu *itemMenu, QObject *parent = 0);
    void makeNodeConnection();
    void removeAllWidgetsFromProperties();
    void connectDesignToBackend(int i);
    void runDesign();
    void displayBlockProperties(int type, int id);
    void createTemporaryGuideLine(QGraphicsSceneMouseEvent *mouseEvent);
    void deleteTemporaryGuideLine();
    void setBlockEnable(BlockItem *blockIt, bool flagEn);
    void setEdgeEnable(int idEdge, bool flagEn);
    void removeAssociatedEdges(BlockItem *blockIt);
    void stop();
    void createConnectionTree();
    void createConnTreeIter(CTree_t *cTree);
    void iterateConnTree(CTree_t *cTree);

    QVBoxLayout *vbLayOutProp;
    QSpinBox *sbIns, *sbOuts;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

public slots:
    void nodeConnectionStarted(Node *node, QGraphicsSceneMouseEvent *mouseEvent);
    void setMode(Mode mode);
    void setItemType(BlockItem::BlockType type);
    void blockItemClicked(BlockItem *item, QGraphicsSceneMouseEvent *mouseEven);

signals:
    void itemInserted(BlockItem *item);
    void outputTextReady(QString strOut);

private:
    Edge *edge[MAX_BLOCKS];
    int countEdge;

    BlockItem *blockItem[MAX_BLOCKS];
    int countBlockItem;

    bool flagConnectionStarted;
    Node *nodeStart, *nodeEnd;

    BlockItem::BlockType myItemType;
    Mode myMode;

    ManageBlocks *manageBlocks;


    int countConstant, countArray, countExpression, countGraph,
        countSplit, countAdder, countDelay, countAccumulator,
        countReadFile, countGetMax, countLineDisplay,
        countIfBlock, countHistFromArrayBlock, countFillHist,
        countReadMultiFile, countGenerateGaus, countGenerateXY,
        countMain, countDeMux, countLocalProcedure,
        countNetworkClient, countNetworkServer
    ;

    QGraphicsLineItem *line;

    QMenu *myItemMenu;

};

#endif // BLOCKSCENE_H
