#include "blockscene.h"

BlockScene::BlockScene(QMenu *itemMenu, QObject *parent):
    QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    flagConnectionStarted = false;

    countBlockItem = 0;
    countEdge = 0;

    manageBlocks = new ManageBlocks();

    countConstant = countArray = countExpression = countGraph = countSplit = countAdder = countDelay = countAccumulator = countReadFile = countGetMax = countLineDisplay = 0;
    countIfBlock = 0;
    countHistFromArrayBlock = 0;
    countFillHist = 0;
    countReadMultiFile = 0;
    countGenerateGaus = 0;
    countGenerateXY = 0;
    countMain = 0;
    countDeMux = 0;
    countLocalProcedure = 0;
    countNetworkClient = 0;
    countNetworkServer = 0;

    vbLayOutProp = new QVBoxLayout();




    auto marginRect = addRect(sceneRect().adjusted(-25000, -25000, 25000, 25000));
    sceneRect(); // hack to force update of scene bounding box
    delete marginRect;

}

void BlockScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    //    if (myMode == InsertLine && line != 0) {
    //        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
    //        line->setLine(newLine);
    //    } else if (myMode == MoveItem) {
    //        QGraphicsScene::mouseMoveEvent(mouseEvent);
    //    }


    // draw temporary connection guide line
    if (myMode == InsertLine) {
        if(line != 0) {
            QLineF newLine(line->line().p1(), mouseEvent->scenePos());
            line->setLine(newLine);
        }
    } else if (myMode == MoveItem) {
        for(int i = 0; i < countEdge; i++){
            edge[i]->update();
        }
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }

    QGraphicsScene::update();

    //qDebug() << "Moving";
}

void BlockScene::nodeConnectionStarted(Node *node, QGraphicsSceneMouseEvent *mouseEvent){
    if(!flagConnectionStarted && node->getIOType() == Node::Output){
        flagConnectionStarted = true;
        nodeStart = node;

        // create the temporary connection guide
        createTemporaryGuideLine(mouseEvent);
        //

        myMode = BlockScene::InsertLine;
    }
    else if(flagConnectionStarted && node->getIOType() == Node::Input){
        nodeEnd  = node;
        makeNodeConnection();

        // delete temporary connection guide line
        deleteTemporaryGuideLine();
        //

        flagConnectionStarted = false;
        myMode = BlockScene::MoveItem;
    }
}

void BlockScene::makeNodeConnection(){
    edge[countEdge] = new Edge(countEdge, nodeStart, nodeEnd, myItemMenu);
    addItem(edge[countEdge]);
    nodeStart->setConnectionFlag(true);
    nodeEnd->setConnectionFlag(true);

    connectDesignToBackend(countEdge);

    countEdge++;
}

void BlockScene::setMode(Mode mode){
    myMode = mode;
}

void BlockScene::setItemType(BlockItem::BlockType type){
    myItemType = type;
}

void BlockScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton){

        // Delete the temporary guide line if teh connection started and the right button clicked
        if (mouseEvent->button() == Qt::RightButton){
            switch (myMode) {
            case InsertLine:
                qDebug() << "Clicked";
                deleteTemporaryGuideLine();
                myMode = MoveItem;
                flagConnectionStarted = false;
                break;

            }
        }
        return;
    }

    switch (myMode) {
    case InsertItem:

        int typeID;
        int ins, outs;
        switch (myItemType) {
        case BlockItem::Constant:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addConstantBlock(), 0);
            typeID = countConstant;
            countConstant++;
            break;
        case BlockItem::Array:{
            ins = sbIns->value();
            outs = sbOuts->value();
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addContArrayBlock(ins, outs), 0);
            typeID = countArray;
            countArray++;
            break;
        }
        case BlockItem::Expression:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addExpressionBlock());
            typeID = countExpression;
            countExpression++;
            break;
        case BlockItem::Graph:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addGraphBlock());
            typeID = countGraph;
            countGraph++;
            break;
        case BlockItem::Split:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addDataSplitBlock());
            typeID = countSplit;
            countSplit++;
            break;
        case BlockItem::Adder:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addAdderBlock());
            typeID = countAdder;
            countAdder++;
            break;
        case BlockItem::Delay:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addDelayBlock(), 0, 0);
            typeID = countDelay;
            countDelay++;
            break;
        case BlockItem::Accumulator:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addAccumulatorBlock(), 0, 0);
            typeID = countAccumulator;
            countAccumulator++;
            break;

        case BlockItem::ReadFile:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addReadFileBlock(), 0, 0);
            typeID = countReadFile;
            countReadFile++;
            break;

        case BlockItem::GetMax:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addGetMaxBlock(), 0, 0);
            typeID = countGetMax;
            countGetMax++;
            break;

        case BlockItem::LineDisplay:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addLineDisplayBlock(), 0, 0);
            typeID = countLineDisplay;
            countLineDisplay++;
            break;

        case BlockItem::IfBlock:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addIfBlock(), 0, 0);
            typeID = countIfBlock;
            countIfBlock++;
            break;

        case BlockItem::HistFromArrayBlock:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addHistFromArrBlock(), 0, 0);
            typeID = countHistFromArrayBlock;
            countHistFromArrayBlock++;
            break;

        case BlockItem::FillHist:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addFillHistBlock(), 0, 0);
            typeID = countFillHist;
            countFillHist++;
            break;

        case BlockItem::ReadMultiFile:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addReadMultiFilesBlock(), 0, 0);
            typeID = countReadMultiFile;
            countReadMultiFile++;
            break;

        case BlockItem::GenerateGaus:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addGenerateGausBlock(), 0, 0);
            typeID = countGenerateGaus;
            countGenerateGaus++;
            break;

        case BlockItem::GenerateXY:
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addGenerateXYBlock(), 0, 0);
            typeID = countGenerateXY;
            countGenerateXY++;
            break;

        case BlockItem::MainBlock:
            removeAllWidgetsFromProperties();
            ins = 0;//sbIns->value();
            outs = 1;//sbOuts->value();
            vbLayOutProp->addWidget(manageBlocks->addGenerateMainBlock(), 0, 0);
            typeID = countMain;
            countMain++;
            break;

        case BlockItem::DeMux:{
            ins = sbIns->value();
            outs = sbOuts->value();
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addDeMuxBlock(ins, outs), 0);
            typeID = countDeMux;
            countDeMux++;
            break;
        }

        case BlockItem::LocalProcedure:{
            ins = sbIns->value();
            outs = sbOuts->value();
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addLocalProcedureBlock(ins, outs), 0);
            typeID = countLocalProcedure;
            countLocalProcedure++;
            break;
        }
        case BlockItem::NetworkClient:{
            ins = sbIns->value();
            outs = sbOuts->value();
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addNetworkClientBlock(ins, outs), 0);
            typeID = countNetworkClient;
            countNetworkClient++;
            break;
        }
        case BlockItem::NetworkServer:{
            ins = sbIns->value();
            outs = sbOuts->value();
            removeAllWidgetsFromProperties();
            vbLayOutProp->addWidget(manageBlocks->addNetworkServerBlock(ins, outs), 0);
            typeID = countNetworkServer;
            countNetworkServer++;
            break;
        }

        }

        blockItem[countBlockItem] = new BlockItem(myItemType, countBlockItem, typeID, myItemMenu, ins, outs);
        // signal and slot for the node edge connection
        connect(blockItem[countBlockItem], SIGNAL(nodeConnectionStarted(Node*, QGraphicsSceneMouseEvent *)), this, SLOT(nodeConnectionStarted(Node*, QGraphicsSceneMouseEvent *)));
        // signal and slot for only selecting one item at a time
        connect(blockItem[countBlockItem], SIGNAL(blockItemClicked(BlockItem*,QGraphicsSceneMouseEvent*)), this, SLOT(blockItemClicked(BlockItem*, QGraphicsSceneMouseEvent *)));
        //blockItem[countBlockItem]->setBrush(myItemColor);
        addItem(blockItem[countBlockItem]);
        blockItem[countBlockItem]->setPos(mouseEvent->scenePos());
        emit itemInserted(blockItem[countBlockItem]);


        countBlockItem++;
        break;

    case MoveItem:
        BlockItem *child = dynamic_cast<BlockItem*>(itemAt(mouseEvent->scenePos(), QTransform()));
        if(child){
            displayBlockProperties(child->getType(), child->getTypeId());
            //qDebug() << child->getType()<< child->getTypeId();
        }
        break;


        /*case InsertText:
            textItem = new DiagramTextItem();
            textItem->setFont(myFont);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setZValue(1000.0);
            connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                    this, SLOT(editorLostFocus(DiagramTextItem*)));
            connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                    this, SIGNAL(itemSelected(QGraphicsItem*)));
            addItem(textItem);
            textItem->setDefaultTextColor(myTextColor);
            textItem->setPos(mouseEvent->scenePos());
            emit textInserted(textItem);*/
        //default:
        //   ;
    }

    //qDebug() << mouseEvent->pos();

    QGraphicsScene::update();

    QGraphicsScene::mousePressEvent(mouseEvent);

}

void BlockScene::removeAllWidgetsFromProperties(){
    QLayoutItem *childWid;
    while ((childWid = vbLayOutProp->takeAt(0)) != 0) {
        vbLayOutProp->removeWidget(childWid->widget());
        childWid->widget()->hide();
    }

}

void BlockScene::connectDesignToBackend(int i){
    QString varOut;
    qDebug() << int(edge[i]->sourceNode()->getIOType()) << int(edge[i]->destNode()->getIOType());
    // get right block's io number to the previus blocks out io
    cout << "IO Nums " << edge[i]->sourceNode()->getNumber() << " " << edge[i]->destNode()->getNumber() << endl;
    //BlockIO *blockIo;
    //get outputs name
    for(size_t j = 0; j < manageBlocks->blockIO.size(); j++)
    {
        if(int(edge[i]->sourceNode()->getBlockType()) == manageBlocks->blockIO.at(j)->type &&
                edge[i]->sourceNode()->gettypeId() == manageBlocks->blockIO.at(j)->getId())
        {
            varOut = manageBlocks->blockIO.at(j)->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
            manageBlocks->blockIO.at(j)->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
            manageBlocks->blockIO.at(j)->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();

            break;
        }
    }

    if(int(edge[i]->sourceNode()->getBlockType()) == 5){
        varOut = manageBlocks->adderBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->adderBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->adderBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 6){
        varOut = manageBlocks->delayBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->delayBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->delayBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 7){
        varOut = manageBlocks->accumulatorBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->accumulatorBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->accumulatorBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 8){
        varOut = manageBlocks->readFileBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->readFileBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->readFileBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 9){
        varOut = manageBlocks->getMaxBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->getMaxBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->getMaxBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 10){
        varOut = manageBlocks->lineDisplayBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->lineDisplayBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->lineDisplayBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 11){
        varOut = manageBlocks->ifBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->ifBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->ifBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 12){
        varOut = manageBlocks->histFromArrBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->histFromArrBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->histFromArrBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 13){
        varOut = manageBlocks->fillHistBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->fillHistBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->fillHistBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 14){
        varOut = manageBlocks->readMultiFilesBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->readMultiFilesBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->readMultiFilesBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 15){
        varOut = manageBlocks->generateGausBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->generateGausBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->generateGausBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 16){
        varOut = manageBlocks->generateXYBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->generateXYBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->generateXYBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 17){
        //varOut = manageBlocks->generateMainBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        //manageBlocks->generateMainBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        //manageBlocks->generateMainBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 18){
        varOut = manageBlocks->deMuxBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->deMuxBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->deMuxBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 19){
        varOut = manageBlocks->localProcedureBlock[edge[i]->sourceNode()->gettypeId()]->lblOutData[edge[i]->sourceNode()->getNumber()]->text();
        manageBlocks->localProcedureBlock[edge[i]->sourceNode()->gettypeId()]->conToIONum[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getNumber();
        manageBlocks->localProcedureBlock[edge[i]->sourceNode()->gettypeId()]->conToTotIns[edge[i]->sourceNode()->getNumber()] = edge[i]->destNode()->getTotIns();
    }

    // set output name to inputs and copy inputs name
    QString varIn;
    for(size_t j = 0; j < manageBlocks->blockIO.size(); j++)
    {
        if(int(edge[i]->destNode()->getBlockType()) == manageBlocks->blockIO.at(j)->type &&
                edge[i]->destNode()->gettypeId() == manageBlocks->blockIO.at(j)->getId())
        {
            manageBlocks->blockIO.at(j)->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
            varIn = manageBlocks->blockIO.at(j)->leName->text();

            break;
        }
    }

    if(int(edge[i]->destNode()->getBlockType()) == 3){
        manageBlocks->graphs[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->graphs[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 5){
        manageBlocks->adderBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->adderBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 6){
        manageBlocks->delayBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->delayBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 7){
        manageBlocks->accumulatorBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->accumulatorBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 8){
        manageBlocks->readFileBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->readFileBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 9){
        manageBlocks->getMaxBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->getMaxBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 10){
        manageBlocks->lineDisplayBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->lineDisplayBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 11){
        manageBlocks->ifBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        manageBlocks->ifBlock[edge[i]->destNode()->gettypeId()]->leExp->setText(varOut);
        varIn = manageBlocks->ifBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 12){
        manageBlocks->histFromArrBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->histFromArrBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 13){
        manageBlocks->fillHistBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->fillHistBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 14){
        manageBlocks->readMultiFilesBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->readMultiFilesBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 15){
        manageBlocks->generateGausBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->generateGausBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 16){
        manageBlocks->generateXYBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->generateXYBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 17){
        //manageBlocks->generateMainBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        //varIn = manageBlocks->generateMainBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }
    else if(int(edge[i]->destNode()->getBlockType()) == 18){
        manageBlocks->deMuxBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->deMuxBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }

    else if(int(edge[i]->destNode()->getBlockType()) == 19){
        manageBlocks->localProcedureBlock[edge[i]->destNode()->gettypeId()]->lblInData[edge[i]->destNode()->getNumber()]->setText(varOut);
        varIn = manageBlocks->localProcedureBlock[edge[i]->destNode()->gettypeId()]->leName->text();
    }

    // set input name to output (right node name to left)
    for(size_t j = 0; j < manageBlocks->blockIO.size(); j++)
    {
        if(int(edge[i]->sourceNode()->getBlockType()) == manageBlocks->blockIO.at(j)->type &&
                edge[i]->sourceNode()->gettypeId() == manageBlocks->blockIO.at(j)->getId())
        {
            manageBlocks->blockIO.at(j)->lblOutConToBlock[edge[i]->sourceNode()->getNumber()]->setText(varIn);

            break;
        }
    }

    if(int(edge[i]->sourceNode()->getBlockType()) == 17){
        //manageBlocks->generateMainBlock[edge[i]->sourceNode()->gettypeId()]->lblOutConToBlock[edge[i]->sourceNode()->getNumber()]->setText(varIn);
        //manageBlocks->generateMainBlock[edge[i]->sourceNode()->gettypeId()]->teScript->append(varIn /*+ "(data);"*/);
    }
    else if(int(edge[i]->sourceNode()->getBlockType()) == 18){
        manageBlocks->deMuxBlock[edge[i]->sourceNode()->gettypeId()]->lblOutConToBlock[edge[i]->sourceNode()->getNumber()]->setText(varIn);
    }
}

void BlockScene::runDesign(){
    // check for any unconnected nodes
    emit outputTextReady("Compiler started");
    bool flagRun = true;
    int unconnectedNodes = 0;
    for(int i = 0; i < countBlockItem; i++){
        if(blockItem[i]->isEnabled()){
            for(int j = 0; j < blockItem[i]->getNoInputNodes(); j++){
                if(!blockItem[i]->getInputNode(j)->getConnectionFlag()){
                    flagRun = false;
                    unconnectedNodes++;
                }
            }
            for(int j = 0; j < blockItem[i]->getNoOutputNodes(); j++){
                if(!blockItem[i]->getOutputNode(j)->getConnectionFlag()){
                    flagRun = false;
                    unconnectedNodes++;
                }
            }
        }
    }

    if(1/*flagRun*/){
        createConnectionTree();
        iterateConnTree(manageBlocks->connTree);
        manageBlocks->runDesign();
        emit outputTextReady("<font color='green'>Program compiled successfully </font>");
    }
    else{
        emit outputTextReady("<font color='red'> Error! " + QString::number(unconnectedNodes) +  " unconnected nodes </font>");
        manageBlocks->resetOutputs();
    }
}

void BlockScene::createConnTreeIter(CTree_t *cTree)
{
    if(cTree->blockIO->numOfOutputs <= 0)
    {
        return;
    }

    for(int i = 0; i < countEdge; i++)
    {
        if(!edge[i]->isEnabledOnScreen() ||
                edge[i]->sourceNode()->getBlockType() != cTree->blockIO->getType() ||
                edge[i]->sourceNode()->gettypeId() !=  cTree->blockIO->getId()
                )
        {
            continue;
        }

        for(size_t j = 0; j < manageBlocks->blockIO.size(); j++)
        {
            if(int(edge[i]->destNode()->getBlockType()) != manageBlocks->blockIO.at(j)->type ||
                    edge[i]->destNode()->gettypeId() != manageBlocks->blockIO.at(j)->getId())
            {
                continue;
            }

            CTree_t *tmpTree = new CTree_t[1];
            tmpTree->parent = cTree;
            tmpTree->blockIO = manageBlocks->blockIO.at(j);

            cTree->child.push_back(tmpTree);

            createConnTreeIter(cTree->child.at(cTree->child.size() - 1));
        }
    }
}

void BlockScene::createConnectionTree()
{
    for (size_t i = 0; i < manageBlocks->blockIO.size(); i++)
    {
        if(manageBlocks->blockIO.at(i)->getType() != BlockItem::MainBlock ||
                !manageBlocks->blockIO.at(i)->isBlockEnabled())
        {
            continue;
        }

        if(manageBlocks->connTree == nullptr)
        {
            manageBlocks->connTree = new CTree_t[1];
            manageBlocks->connTree->parent = nullptr;
            manageBlocks->connTree->blockIO = nullptr;
        }

        CTree_t *tmpTree = new CTree_t[1];
        tmpTree->parent = nullptr;
        tmpTree->blockIO = manageBlocks->blockIO.at(i);

        manageBlocks->connTree->child.push_back(tmpTree);

        createConnTreeIter(manageBlocks->connTree->child.at(manageBlocks->connTree->child.size() - 1));
    }
}

void BlockScene::iterateConnTree(CTree_t *cTree)
{
    if(cTree->blockIO != nullptr)
    {
        cout << " Block " << cTree->blockIO->leName->text().toStdString() << endl;
    }
    if(cTree->parent != nullptr && cTree->parent->blockIO != nullptr)
    {
        cout << " Parent " << cTree->parent->blockIO->leName->text().toStdString() << endl << endl;
    }

    if(cTree->child.size() == 0)
    {
        return;
    }

    for(size_t i = 0; i < cTree->child.size(); i++)
    {
        iterateConnTree(cTree->child.at(i));
    }
}

void BlockScene::displayBlockProperties(int type, int id){
    QGroupBox *gb = manageBlocks->getBlock(type, id);

    /*
    QLayoutItem *childWid;
    QGroupBox *childWidItem;
    if((childWid = vbLayOutProp->takeAt(0)) != 0){
        if((childWidItem = dynamic_cast<QGroupBox *>(childWid))){
            if(childWidItem == gb){
                return;
            }
        }

    }
    if((childWidItem = dynamic_cast<QGroupBox *>(vbLayOutProp->takeAt(0))) != 0){
        if(childWidItem == gb && vbLayOutProp->count() == 1){
            return;
        }
    }*/

    removeAllWidgetsFromProperties();


    gb->show();
    vbLayOutProp->addWidget(gb);
}

void BlockScene::createTemporaryGuideLine(QGraphicsSceneMouseEvent *mouseEvent){
    line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
    line->setPen(QPen(Qt::darkGreen, 2, Qt::DashLine));
    addItem(line);

}

void BlockScene::deleteTemporaryGuideLine(){
    if (line != 0 && myMode == InsertLine) {
        removeItem(line);
        delete line;
        qDebug() << "Connection End";
    }
}

void BlockScene::blockItemClicked(BlockItem *item, QGraphicsSceneMouseEvent *mouseEvent){
    QList<QGraphicsItem *> items = selectedItems();
    foreach( QGraphicsItem *it, items ) {
        if(item != it)
            it->setSelected(false);
    }
}

// disable the block
void BlockScene::setBlockEnable(BlockItem *blockIt, bool flagEn){
    manageBlocks->setBlockEnable(blockIt->getType(), blockIt->getTypeId(), flagEn);
    removeAssociatedEdges(blockIt);
    blockIt->setEnabled(flagEn);
}

// disable the edge
void BlockScene::setEdgeEnable(int idEdge, bool flagEn){
    edge[idEdge]->setFlagEnabledOnScreen(flagEn);
    edge[idEdge]->resetEdges();
}

void BlockScene::removeAssociatedEdges(BlockItem *blockIt){
    for(int i = 0; i < countEdge; i++){
        if(edge[i]->isEnabledOnScreen()){
            if(edge[i]->sourceNode()->getId() == blockIt->getId() || edge[i]->destNode()->getId() == blockIt->getId()){
                edge[i]->setFlagEnabledOnScreen(false);
                edge[i]->resetEdges();
                removeItem(edge[i]);
            }
        }
    }

}

void BlockScene::stop()
{
    manageBlocks->stop();
}

