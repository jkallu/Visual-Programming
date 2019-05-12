QT += gui widgets opengl script

#mac# LIBS += -framework GLUT -framework OpenGL

CONFIG += c++14
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    mainwindow.cpp \
    node.cpp \
    blockitem.cpp \
    blockscene.cpp \
    edge.cpp \
    accumulatorblock.cpp \
    adderblock.cpp \
    block.cpp \
    blockio.cpp \
    constantblock.cpp \
    constarrayblock.cpp \
    delayblock.cpp \
    expressionblock.cpp \
    glwidget.cpp \
    graph.cpp \
    manageblocks.cpp \
    datasplitblock.cpp \
    readfileblock.cpp \
    getmaxblock.cpp \
    linedisplayblock.cpp \
    condition.cpp \
    ifblock.cpp \
    histfromarrblock.cpp \
    fillhist.cpp \
    readmultifilesblock.cpp \
    generategausblock.cpp \
    generatexyblock.cpp \
    mainblock.cpp \
    demux.cpp \
    localprocedureblock.cpp \
    datapack.cpp \
    simulate.cpp \
    simlinklist.cpp \
    mygraphicsview.cpp \
    ./nodegencodes/packer.c \
    ./nodegencodes/linkedList.c \
    networkclientblock.cpp \
    networkserverblock.cpp \
    formulawidget.cpp \
    lexer.cpp \
    token.cpp \
    fsm.cpp \
    numberfsm.cpp

HEADERS += \
    mainwindow.h \
    node.h \
    blockitem.h \
    blockscene.h \
    edge.h \
    accumulatorblock.h \
    adderblock.h \
    block.h \
    blockio.h \
    constantblock.h \
    constarrayblock.h \
    delayblock.h \
    expressionblock.h \
    glwidget.h \
    graph.h \
    manageblocks.h \
    datasplitblock.h \
    readfileblock.h \
    getmaxblock.h \
    linedisplayblock.h \
    condition.h \
    ifblock.h \
    histfromarrblock.h \
    fillhist.h \
    readmultifilesblock.h \
    generategausblock.h \
    generatexyblock.h \
    mainblock.h \
    demux.h \
    localprocedureblock.h \
    datapack.h \
    simulate.h \
    simlinklist.h \
    mygraphicsview.h \
    ./nodegencodes/packer.h \
    ./nodegencodes/linkedList.h \
    networkclientblock.h \
    networkserverblock.h \
    formulawidget.h \
    lexer.h \
    token.h \
    fsm.h \
    numberfsm.h

RESOURCES += \
    node.qrc

#INCLUDEPATH += /home/jin/qt_pgms/nodegencodes
LIBS += -ldl
#INCLUDEPATH += /Applications/root_v6.12.06/include

#LIBS += -L/Applications/root_v6.12.06/lib/  `/Applications/root_v6.12.06/bin/root-config --glibs --libs` -lSpectrum

