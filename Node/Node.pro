QT += gui widgets opengl script 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation printsupport svg network

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
    condition.cpp \
    datapack.cpp \
    simulate.cpp \
    simlinklist.cpp \
    ./nodegencodes/packer.c \
    ./nodegencodes/linkedList.c \
    gsltest.cpp \
    blocks/accumulatorblock.cpp \
    blocks/adderblock.cpp \
    blocks/block.cpp \
    blocks/blockio.cpp \
    blocks/constantblock.cpp \
    blocks/constarrayblock.cpp \
    blocks/datasplitblock.cpp \
    blocks/delayblock.cpp \
    blocks/demux.cpp \
    blocks/expressionblock.cpp \
    blocks/generategausblock.cpp \
    blocks/generatexyblock.cpp \
    blocks/getmaxblock.cpp \
    blocks/graph.cpp \
    blocks/gslblock.cpp \
    blocks/histfromarrblock.cpp \
    blocks/ifblock.cpp \
    blocks/linedisplayblock.cpp \
    blocks/localprocedureblock.cpp \
    blocks/mainblock.cpp \
    blocks/manageblocks.cpp \
    blocks/networkclientblock.cpp \
    blocks/networkserverblock.cpp \
    blocks/readfileblock.cpp \
    blocks/readmultifilesblock.cpp \
    blocks/simulate2dblock.cpp \
    blocks/simulate3d.cpp \
    blocks/simulate3dblock.cpp \
    gui/blockitem.cpp \
    gui/blockscene.cpp \
    gui/glwidget.cpp \
    gui/mainwindow.cpp \
    gui/mygraphicsview.cpp \
    gui/node.cpp \
    gui/edge.cpp \
    compiler/compiletoc.cpp \
    compiler/earleyparser.cpp \
    compiler/fsm.cpp \
    compiler/grammar.cpp \
    compiler/lexer.cpp \
    compiler/numberfsm.cpp \
    compiler/parserhelper.cpp \
    compiler/rule.cpp \
    compiler/token.cpp \
    blocks/fillhist.cpp \
    gui/formulawidget.cpp \
    gnuplot/QtGnuplotWidget.cpp \
    gnuplot/QtGnuplotScene.cpp \
    gnuplot/QtGnuplotItems.cpp \
    gnuplot/QtGnuplotInstance.cpp \
    gnuplot/QtGnuplotEvent.cpp \
    gnuplot/embed_example.cpp \
    gnuplot/gnuplotblock.cpp

HEADERS += \
    condition.h \
    datapack.h \
    simulate.h \
    simlinklist.h \
    ./nodegencodes/packer.h \
    ./nodegencodes/linkedList.h \
    commonheader.h \
    gsltest.h \
    blocks/block.h \
    blocks/blockio.h \
    blocks/accumulatorblock.h \
    blocks/adderblock.h \
    blocks/constantblock.h \
    blocks/constarrayblock.h \
    blocks/datasplitblock.h \
    blocks/delayblock.h \
    blocks/demux.h \
    blocks/expressionblock.h \
    blocks/generategausblock.h \
    blocks/generatexyblock.h \
    blocks/getmaxblock.h \
    blocks/graph.h \
    blocks/gslblock.h \
    blocks/histfromarrblock.h \
    blocks/ifblock.h \
    blocks/linedisplayblock.h \
    blocks/localprocedureblock.h \
    blocks/mainblock.h \
    blocks/manageblocks.h \
    blocks/networkclientblock.h \
    blocks/networkserverblock.h \
    blocks/readfileblock.h \
    blocks/readmultifilesblock.h \
    blocks/simulate2dblock.h \
    blocks/simulate3d.h \
    blocks/simulate3dblock.h \
    gui/blockitem.h \
    gui/blockscene.h \
    gui/edge.h \
    gui/glwidget.h \
    gui/mainwindow.h \
    gui/mygraphicsview.h \
    gui/node.h \
    compiler/rule.h \
    compiler/compiletoc.h \
    compiler/grammar.h \
    compiler/lexer.h \
    compiler/earleyparser.h \
    compiler/token.h \
    compiler/fsm.h \
    compiler/numberfsm.h \
    compiler/parserhelper.h \
    blocks/fillhist.h \
    gui/formulawidget.h \
    gnuplot/embed_example.h \
    gnuplot/QtGnuplotEvent.h \
    gnuplot/QtGnuplotInstance.h \
    gnuplot/QtGnuplotItems.h \
    gnuplot/QtGnuplotScene.h \
    gnuplot/QtGnuplotWidget.h \
    gnuplot/gnuplotblock.h

RESOURCES += \
    node.qrc

INCLUDEPATH += ./blocks ./compiler ./gui ./gnuplot /home/jin/Downloads/gnuplot-5.2.7/src/qtterminal
LIBS += -ldl -lgsl -lgslcblas -lm
#INCLUDEPATH += /Applications/root_v6.12.06/include

#LIBS += -L/Applications/root_v6.12.06/lib/  `/Applications/root_v6.12.06/bin/root-config --glibs --libs` -lSpectrum

DISTFILES += \
    vp.png \
    build/Makefile

