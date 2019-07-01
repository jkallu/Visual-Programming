#include "blockitem.h"
#include <QMenu>

BlockItem::BlockItem(BlockType blockType, int id_l, int tpId, QMenu *contextMenu, int nIn, int nOut)
{
    myBlockType = blockType;
    myContextMenu = contextMenu;
    id=  id_l;
    typeId = tpId;

    flagEnabled = true;

    //
    arrayWH.setX(100);
    arrayWH.setY(50);
    //

    noInputNodes = nIn;
    noOutputNodes = nOut;

    colorLight = QColor(Qt::gray);
    colorDark = QColor(Qt::darkGray);

    switch (myBlockType) {
    case Constant:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(0);
        creatOutputNodes(1);
        name = "Const_" + QString::number(typeId);

        painterpath.addRect(30, 30, 30, 30);

        break;
    case Array:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry() + nOut * arrayWH.ry() / 4) << QPointF(0, arrayWH.ry() + nOut * arrayWH.ry() / 4)
                  << QPointF(0, 0);

        createInputNodes(nIn);
        creatOutputNodes(nOut);
        name = "Array_" + QString::number(typeId);

        painterpath.addRect(0, 30, 30, 30);
        painterpath.addRect(30, 30, 30, 30);
        painterpath.addRect(60, 30, 30, 30);

        colorLight = QColor(Qt::gray);
        colorDark = QColor(Qt::darkGray);

        break;
    case Expression:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(1);
        creatOutputNodes(1);
        name = "Expr_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 40), "sin(x) + ..");

        colorLight = QColor(Qt::red);
        colorDark = QColor(Qt::darkRed);

        break;
    case Graph:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(2);
        creatOutputNodes(0);
        name = "Graph_" + QString::number(typeId);

        painterpath.addRect(0, 0, 100, 100);
        painterpath.addRect(10, 10, 80, 80);

        colorLight = QColor(Qt::green);
        colorDark = QColor(Qt::darkGreen);

        break;
    case Split:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);
        createInputNodes(1);
        creatOutputNodes(2);
        name = "Duplicate_" + QString::number(typeId);

        painterpath.moveTo(QPointF(0, 50));
        painterpath.lineTo(QPointF(50, 50));
        painterpath.lineTo(QPointF(100, 0));
        painterpath.moveTo(QPointF(50, 50));
        painterpath.lineTo(QPointF(100, 100));

        colorLight = QColor(Qt::blue);
        colorDark = QColor(Qt::darkBlue);

        break;
    case  Adder:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);
        createInputNodes(2);
        creatOutputNodes(1);
        name = "Adder_" + QString::number(typeId);

        painterpath.moveTo(QPointF(50, 0));
        painterpath.lineTo(QPointF(50, 100));
        painterpath.moveTo(QPointF(0, 50));
        painterpath.lineTo(QPointF(100, 50));

        colorLight = QColor(Qt::cyan);
        colorDark = QColor(Qt::darkCyan);

        break;
    case Delay:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(1);
        creatOutputNodes(1);
        name = "Delay_" + QString::number(typeId);

        //QFont font;
        //font.setStyleHint(QFont::Times, QFont::PreferAntialias);
        //font.setPointSize(30);

        painterpath.addText(0, 50, QFont("Times", 40), "Delay");
        //painterpath.drawPath(textPath);

        //painterpath.end();

        colorLight = QColor(Qt::yellow);
        colorDark = QColor(Qt::darkYellow);

        break;
    case Accumulator:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(1);
        creatOutputNodes(1);
        name = "Accum_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 40), "Acc");

        colorLight = QColor(Qt::magenta);
        colorDark = QColor(Qt::darkMagenta);

        break;
    case ReadFile:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(0);
        creatOutputNodes(1);
        name = "ReadFile_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 30), "File In");

        colorLight = QColor(Qt::gray);
        colorDark = QColor(Qt::darkGray);

        break;

    case GetMax:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(1);
        creatOutputNodes(1);
        name = "GetMax_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 30), "GetMax");

        colorLight = QColor(200, 100, 100);
        colorDark = QColor(150, 50, 50);

        break;

    case LineDisplay:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(1);
        creatOutputNodes(0);
        name = "LineDisplay_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 30), "LineDisplay");

        colorLight = QColor(100,200, 100);
        colorDark = QColor(50, 150, 50);

        break;

    case IfBlock:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(1);
        creatOutputNodes(2);
        name = "IfBlock_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 30), "IfBlock");

        colorLight = QColor(100, 100, 200);
        colorDark = QColor(50, 50, 150);

        break;

    case HistFromArrayBlock:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(1);
        creatOutputNodes(2);
        name = "HistFromArrayBlock_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 30), "HistFromArrayBlock");

        colorLight = QColor(100, 200, 200);
        colorDark = QColor(50, 150, 150);

        break;

    case FillHist:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(1);
        creatOutputNodes(2);
        name = "FillHistBlock_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 30), "FillHistBlock");

        colorLight = QColor(100, 100, 100);
        colorDark = QColor(50, 50, 50);

        break;

    case ReadMultiFile:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(0);
        creatOutputNodes(1);
        name = "ReadMultiFileBlock_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 30), "ReadMultiFileBlock");

        colorLight = QColor(200, 100, 100);
        colorDark = QColor(150, 50, 50);

        break;

    case GenerateGaus:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(0);
        creatOutputNodes(1);
        name = "GenerateGaus_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 30), "GenerateGausBlock");

        colorLight = QColor(20, 100, 100);
        colorDark = QColor(10, 50, 50);

        break;

    case GenerateXY:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(1);
        creatOutputNodes(2);
        name = "GenerateXY_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 30), "GenerateXYBlock");

        colorLight = QColor(20, 100, 100);
        colorDark = QColor(10, 50, 50);

        break;

    case MainBlock:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(0);
        creatOutputNodes(1);
        name = "Main_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 40), "M");

        colorLight = QColor(Qt::white);
        colorDark = QColor(Qt::white);

        break;

    case DeMux:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), 2 * arrayWH.ry()) << QPointF(0, 2 * arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(nIn);
        creatOutputNodes(nOut);
        name = "DeMux_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 40), "DeMux");

        colorLight = QColor(Qt::red);
        colorDark = QColor(Qt::darkRed);

        break;

    case LocalProcedure:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(nIn);
        creatOutputNodes(nOut);
        name = "LocalProcedure_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 40), "LocalProcedure");

        colorLight = QColor(Qt::red);
        colorDark = QColor(Qt::darkRed);

        break;

    case NetworkClient:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(nIn);
        creatOutputNodes(nOut);
        name = "NetworkClient_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 40), "NetworkClient");

        colorLight = QColor(Qt::red);
        colorDark = QColor(Qt::darkRed);

        break;

    case NetworkServer:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(nIn);
        creatOutputNodes(nOut);
        name = "NetworkServer_" + QString::number(typeId);

        painterpath.addText(0, 50, QFont("Times", 40), "NetworkServer");

        colorLight = QColor(Qt::red);
        colorDark = QColor(Qt::darkRed);

        break;

    case Simulate:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(2);
        creatOutputNodes(0);
        name = "Simulate_" + QString::number(typeId);

        painterpath.addRect(0, 0, 100, 100);
        painterpath.addRect(10, 10, 80, 80);

        colorLight = QColor(Qt::green);
        colorDark = QColor(Qt::darkGreen);

        break;

    case GSL:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(1);
        creatOutputNodes(1);
        name = "GSL_" + QString::number(typeId);

        painterpath.addRect(0, 0, 100, 100);
        painterpath.addRect(10, 10, 80, 80);

        colorLight = QColor(Qt::green);
        colorDark = QColor(Qt::darkGreen);

        break;

    case Gnuplot:
        myPolygon << QPointF(0, 0) << QPointF(arrayWH.rx(), 0)
                  << QPointF(arrayWH.rx(), arrayWH.ry()) << QPointF(0, arrayWH.ry())
                  << QPointF(0, 0);

        createInputNodes(2);
        creatOutputNodes(0);
        name = "Gnuplot_" + QString::number(typeId);

        painterpath.addRect(0, 0, 100, 100);
        painterpath.addRect(10, 10, 80, 80);

        colorLight = QColor(Qt::green);
        colorDark = QColor(Qt::darkGreen);

        break;

    default:
        myPolygon << QPointF(-120, -80) << QPointF(-70, 80)
                  << QPointF(120, 80) << QPointF(70, -80)
                  << QPointF(-120, -80);
        break;
    }


    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);


}

void BlockItem::createInputNodes(int num){
    noInputNodes = num;
    inputNodes = new Node*[num];
    int y_in_dist = arrayWH.ry() / (1 + num);
    int x_in = 6;
    for(int i = 0; i < num; i++){
        inputNodes[i] = new Node(Node::Input, myBlockType, id, typeId, i, noInputNodes, noOutputNodes, this);
        connect(inputNodes[i], SIGNAL(connectionStarted(Node *, QGraphicsSceneMouseEvent *)), this, SLOT(nodeEmittedClickeEvent(Node *, QGraphicsSceneMouseEvent *)));
        //QPoint xy = QPoint(this->boundingRect().width(), this->boundingRect().height());
        inputNodes[i]->setParentItem(this);
        inputNodes[i]->setPos(QPoint(x_in, (i + 1) * y_in_dist));
    }
}

void BlockItem::creatOutputNodes(int num){
    noOutputNodes = num;
    int y_in_dist = arrayWH.ry() / (1 + num);
    int x_in = arrayWH.rx();
    outputNodes = new Node*[num];
    for(int i = 0; i < num; i++){
        outputNodes[i] = new Node(Node::Output, myBlockType, id, typeId, i, noInputNodes, noOutputNodes,this);
        connect(outputNodes[i], SIGNAL(connectionStarted(Node *, QGraphicsSceneMouseEvent *)), this, SLOT(nodeEmittedClickeEvent(Node *, QGraphicsSceneMouseEvent *)));
        //QPoint xy = QPoint(this->boundingRect().width(), this->boundingRect().height());
        outputNodes[i]->setParentItem(this);
        outputNodes[i]->setPos(QPoint(x_in, (i + 1) * y_in_dist));
    }
}

void BlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{

    QRadialGradient gradient(-3, -3, 10);
    /*
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, colorLight.light(120));
        gradient.setColorAt(0, colorDark.light(120));
    } else {
        gradient.setColorAt(0, colorLight);
        gradient.setColorAt(1, colorDark);
    }
    */
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::white);

    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::darkBlue,2));

    //painter->setPen(QPen(Qt::black, 0));
    painter->drawPolygon(myPolygon);

    QFont font = painter->font();
    font.setPixelSize(10);
    painter->setFont(font);

    QPen pen = painter->pen();
    pen.setColor(Qt::darkBlue);
    painter->setPen(pen);
    painter->drawText(QPoint(10, arrayWH.ry() / 2), name);

}

QRectF BlockItem::boundingRect() const
{
    qreal adjustW = 100;
    qreal adjustH = 50;
    return QRectF( 0 - 20, 0 - 20, adjustW + 20, adjustH + 20);
}

void BlockItem::nodeEmittedClickeEvent(Node *node, QGraphicsSceneMouseEvent *mouseEvent){
    qDebug() << "Clicked Node";
    emit nodeConnectionStarted(node, mouseEvent);
}

QPixmap BlockItem::image() const
{
    QPixmap pixmap(100, 100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::blue, 5));
    //painter.translate(0, 0);
    //painter.drawPolyline(myPolygon);
    painter.drawPath(painterpath);

    return pixmap;
}

void BlockItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    emit blockItemClicked(this, mouseEvent);
}

void BlockItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}
