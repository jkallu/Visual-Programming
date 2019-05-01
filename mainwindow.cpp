#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow()
{
    createToolBox();
    createActions();
    createFileMenu();
    createToolbars();





    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);

    //view = new QGraphicsView();
    //view->setMinimumWidth(600);
    //view->setMouseTracking(true);

    mView = new MyGraphicsView;
    mView->setMinimumWidth(600);
    mView->setMouseTracking(true);


    teOuts = new QTextEdit;

    QVBoxLayout *layoutViewOut = new QVBoxLayout;
    layoutViewOut->addWidget(mView);
    layoutViewOut->addWidget(teOuts);

    teOuts ->append("<h1>Compiler Output</h1>");
    //teOuts->append("Starting the IDE");


    layout->addLayout(layoutViewOut);

    //layout->addWidget(view);


    blockScene = new BlockScene(itemMenu);
    mView->setScene(blockScene);

    //vbLayOutProp = new QVBoxLayout();
    vbLayOutProp = blockScene->vbLayOutProp;

    layout->addLayout(vbLayOutProp);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Diagramscene"));
    //setUnifiedTitleAndToolBarOnMac(true);




    /*pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton, int(DiagramScene::InsertLine));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));*/

    connect(blockScene, SIGNAL(itemInserted(BlockItem*)),
            this, SLOT(itemInserted(BlockItem*)));

    connect(blockScene, SIGNAL(outputTextReady(QString)), this, SLOT(updateTEOuts(QString)));

    //setUnifiedTitleAndToolBarOnMac(true);


    //simulate->start("generateArray");
}

void MainWindow::createToolBox(){
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);

    connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Constant"), BlockItem::Constant), 0, 0);
    layout->addWidget(createCellWidget(tr("Array"), BlockItem::Array),0, 1);
    layout->addWidget(createCellWidget(tr("Expression"), BlockItem::Expression), 1, 0);
    layout->addWidget(createCellWidget(tr("Graph"), BlockItem::Graph), 1, 1);
    layout->addWidget(createCellWidget(tr("Split"), BlockItem::Split), 2, 0);
    layout->addWidget(createCellWidget(tr("Adder"), BlockItem::Adder), 2, 1);
    layout->addWidget(createCellWidget(tr("Delay"), BlockItem::Delay), 3, 0);
    layout->addWidget(createCellWidget(tr("Accumulator"), BlockItem::Accumulator), 3, 1);
    layout->addWidget(createCellWidget(tr("ReadFile"), BlockItem::ReadFile), 4, 0);
    layout->addWidget(createCellWidget(tr("GetMax"), BlockItem::GetMax), 4, 1);
    layout->addWidget(createCellWidget(tr("LineDisplay"), BlockItem::LineDisplay), 5, 0);
    layout->addWidget(createCellWidget(tr("IfBlock"), BlockItem::IfBlock), 5, 1);
    layout->addWidget(createCellWidget(tr("HistFromArrayBlock"), BlockItem::HistFromArrayBlock), 6, 0);
    layout->addWidget(createCellWidget(tr("FillHistBlock"), BlockItem::FillHist), 6, 1);
    layout->addWidget(createCellWidget(tr("ReadMultiFileBlock"), BlockItem::ReadMultiFile), 7, 0);
    layout->addWidget(createCellWidget(tr("GenerateGausBlock"), BlockItem::GenerateGaus), 7, 1);
    layout->addWidget(createCellWidget(tr("GenerateXYBlock"), BlockItem::GenerateXY), 8, 0);
    layout->addWidget(createCellWidget(tr("MainBlock"), BlockItem::MainBlock), 8, 1);
    layout->addWidget(createCellWidget(tr("DeMuxBlock"), BlockItem::DeMux), 9, 0);
    layout->addWidget(createCellWidget(tr("LocalProcedureBlock"), BlockItem::LocalProcedure), 9, 1);
    layout->addWidget(createCellWidget(tr("NetworkClientBlock"), BlockItem::NetworkClient), 10, 0);
    layout->addWidget(createCellWidget(tr("NetworkServerBlock"), BlockItem::NetworkServer), 10, 1);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    //toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    //toolBox->setMinimumWidth(itemWidget->minimumSizeHint().width());
    toolBox->setMaximumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Programming Blocks"));
    //toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}

void MainWindow::buttonGroupClicked(int id){
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (buttonGroup->button(id) != button)
            button->setChecked(false);
    }

    switch (BlockItem::BlockType(id)) {
        case BlockItem::Array:{
            ioBox(BlockItem::Array, ConstArrayBlock::getNumInputs(), ConstArrayBlock::getNumOutputs());
            break;
        }
        case BlockItem::DeMux:{
            ioBox(BlockItem::DeMux, 1, 1);
            break;
        }
        case BlockItem::LocalProcedure:{
            ioBox(BlockItem::LocalProcedure, 1, 0);
            break;
        }
        case BlockItem::NetworkClient:{
            ioBox(BlockItem::NetworkClient, 1, 0);
            break;
        }
        case BlockItem::NetworkServer:{
            ioBox(BlockItem::NetworkServer, 1, 0);
            break;
        }
        case BlockItem::Graph:{
            ioBox(BlockItem::Graph, Graph::getNumInputs(), Graph::getNumOutputs());
            break;
        }
        default:
            blockScene->removeAllWidgetsFromProperties();
    }


    blockScene->setItemType(BlockItem::BlockType(id));
    blockScene->setMode(BlockScene::InsertItem);

    // deselect all items
    QList<QGraphicsItem *> items = blockScene->selectedItems();
    foreach( QGraphicsItem *item, items ) {
        item->setSelected(false);
    }

}

void MainWindow::ioBox(BlockItem::BlockType type, int in, int out)
{
    /*QLabel *lblIns, *lblOuts;
    QLineEdit *leIns, *leOuts;

    QHBoxLayout *hbIO;
    QGroupBox *gbIO;*/

    lblIns = new QLabel("Inputs");
    lblOuts = new QLabel("Outputs");

    sbIns = new QSpinBox;
    sbOuts = new QSpinBox;

    sbIns->setRange(0, 10);
    sbOuts->setRange(0, 10);

    blockScene->sbIns = sbIns;
    blockScene->sbOuts = sbOuts;

    hbIO = new QHBoxLayout;
    gbIO = new QGroupBox("Edit IO");

    hbIO->addWidget(lblIns);
    hbIO->addWidget(sbIns);
    hbIO->addWidget(lblOuts);
    hbIO->addWidget(sbOuts);

    gbIO->setLayout(hbIO);

    blockScene->removeAllWidgetsFromProperties();
    switch (type)
    {
        case BlockItem::Array:
            sbIns->setValue(ConstArrayBlock::getNumInputs());
            sbOuts->setValue(ConstArrayBlock::getNumOutputs());
        break;

        case BlockItem::DeMux:
            sbIns->setValue(DeMux::getNumInputs());
            sbOuts->setValue(DeMux::getNumOutputs());
        break;

        case BlockItem::LocalProcedure:
            sbIns->setValue(LocalProcedureBlock::getNumInputs());
            sbOuts->setValue(LocalProcedureBlock::getNumOutputs());
        break;
        case BlockItem::NetworkClient:
            sbIns->setValue(NetworkClientBlock::getNumInputs());
            sbOuts->setValue(NetworkClientBlock::getNumOutputs());
        break;
        case BlockItem::NetworkServer:
            sbIns->setValue(NetworkServerBlock::getNumInputs());
            sbOuts->setValue(NetworkServerBlock::getNumOutputs());
        break;
        case BlockItem::Graph:
            sbIns->setValue(Graph::getNumInputs());
            sbOuts->setValue(Graph::getNumOutputs());
        break;
    }

    //sbIns->setText(QString::number(ConstArrayBlock::getNumInputs()));
    //sbOuts->setText(QString::number(ConstArrayBlock::getNumOutputs()));
    if(in == 1)
    {
        sbIns->setEnabled(true);
    }
    else
    {
        sbIns->setEnabled(false);
    }
    if(out == 1)
    {
        sbOuts->setEnabled(true);
    }
    else
    {
        sbOuts->setEnabled(false);
    }

    vbLayOutProp ->addWidget(gbIO);
}

QWidget *MainWindow::createCellWidget(const QString &text, BlockItem::BlockType type)
{

    BlockItem item(type, 1000000000, 0, itemMenu, 0, 0);
    QIcon icon(item.image());

    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(10, 10));
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

void MainWindow::itemInserted(BlockItem *item){
    //pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    //blockScene->setMode(BlockScene::Mode(pointerTypeGroup->checkedId()));
    blockScene->setMode(BlockScene::MoveItem);
    buttonGroup->button(int(item->diagramType()))->setChecked(false);
}

void MainWindow::createFileMenu(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(runAction);
    fileMenu->addAction(stopAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(openAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);

}

void MainWindow::createActions(){
    runAction = new QAction(QIcon(":/icons/run.png"), tr("R&un"), this);
    //runAction->setShortcuts(QKeySequence::Quit);
    runAction->setStatusTip(tr("Run"));
    connect(runAction, SIGNAL(triggered()), this, SLOT(run()));

    stopAction = new QAction(QIcon(":/icons/stop.png"), tr("S&top"), this);
    //runAction->setShortcuts(QKeySequence::Quit);
    stopAction->setStatusTip(tr("Stop"));
    connect(stopAction, SIGNAL(triggered()), this, SLOT(stop()));

    deleteAction = new QAction(QIcon(":/icons/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    saveAction = new QAction(QIcon(":/icons/delete.png"), tr("&Save"), this);
    saveAction->setShortcut(tr("Save"));
    saveAction->setStatusTip(tr("Save design"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    openAction = new QAction(QIcon(":/icons/delete.png"), tr("&Open"), this);
    openAction->setShortcut(tr("Open"));
    openAction->setStatusTip(tr("Open design"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
}

void MainWindow::run(){
    blockScene->runDesign();
    runToolBar->setDisabled(true);
    stopToolBar->setEnabled(true);
}

void MainWindow::stop()
{
    blockScene->stop();
    runToolBar->setEnabled(true);
    stopToolBar->setDisabled(true);
}

void MainWindow::save()
{
    teOuts->append("Saving design...\n");
    blockScene->saveDesign();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Design Files (*.txt)"));

    blockScene->openDesign(fileName);

    teOuts->append("Opening design " + fileName + "\n");
}

void MainWindow::deleteItem(){
    foreach (QGraphicsItem *item, blockScene->selectedItems()) {
        if (item->type() == Edge::Type) {
            blockScene->removeItem(item);
            Edge *edge = dynamic_cast<Edge *>(item);
            blockScene->setEdgeEnable(edge->getId(), false);
        }
    }

    foreach (QGraphicsItem *item, blockScene->selectedItems()) {
        qDebug() << item->type() << BlockItem::Type;
        if (item->type() == BlockItem::Type){
            BlockItem *itemBlock = dynamic_cast<BlockItem *>(item);
            if(itemBlock)
                blockScene->setBlockEnable(itemBlock, false);
            else{
                qDebug() << "Serious error";
            }
        }
        else{
            qDebug() << "Not a block item";
        }
        blockScene->removeItem(item);
        //delete item;
    }
}

void MainWindow::createToolbars(){
    runToolBar = addToolBar(tr("Run"));
    runToolBar->addAction(runAction);

    stopToolBar = addToolBar(tr("Stop"));
    stopToolBar->addAction(stopAction);
    stopToolBar->setDisabled(true);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);




}

void MainWindow::updateTEOuts(QString strOut){
    teOuts->append(strOut);
}




