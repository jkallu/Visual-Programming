#ifndef MANAGEBLOCKS_H
#define MANAGEBLOCKS_H
#include <QtScript>
#include "constantblock.h"
#include "expressionblock.h"
#include "constarrayblock.h"
#include "graph.h"
#include "datasplitblock.h"
#include "adderblock.h"
#include "delayblock.h"
#include "accumulatorblock.h"
#include "readfileblock.h"
#include "getmaxblock.h"
#include "linedisplayblock.h"
#include "ifblock.h"
#include "histfromarrblock.h"
#include "fillhist.h"
#include "readmultifilesblock.h"
#include "generategausblock.h"
#include "generatexyblock.h"
#include "mainblock.h"
#include "demux.h"
#include "localprocedureblock.h"

#include "simulate.h"

//#include "sumblock.h"
#include <QString>

#define MAX_BLOCKS 10000


//class SumBlock;
class MainBlock;
class GenerateXYBlock;
class GenerateGausBlock;
class ReadMultiFilesBlock;
class FillHist;
class HistFromArrBlock;
class IfBlock;
class LineDisplayBlock;
class GetMaxBlock;
class ReadFileBlock;
class AccumulatorBlock;
class DelayBlock;
class AdderBlock;
class DataSplitBlock;
class Graph;
class ExpressionBlock;
class ConstantBlock;
class ConstArrayBlock;
class DeMux;
class LocalProcedureBlock;

class Simulate;


class BlockInfo
{
public:
    int id;
    int type;
    int io; // 0: in, 1: out
    int num;
    int status; // 0 : good, -1 : bad
    int size;
};


class ManageBlocks
{
public:
    ManageBlocks();
    QGroupBox* addConstantBlock();
    QGroupBox* addExpressionBlock();
    QGroupBox* addGraphBlock();
    QGroupBox* addContArrayBlock(int nIn = ConstArrayBlock::getNumInputs(), int nOut = ConstArrayBlock::getNumOutputs());
    QGroupBox* addDataSplitBlock();
    QGroupBox* addAdderBlock();
    QGroupBox* addDelayBlock();
    QGroupBox* addAccumulatorBlock();
    QGroupBox* addReadFileBlock();
    QGroupBox* addGetMaxBlock();
    QGroupBox* addLineDisplayBlock();
    QGroupBox* addIfBlock();
    QGroupBox* addHistFromArrBlock();
    QGroupBox* addFillHistBlock();
    QGroupBox* addReadMultiFilesBlock();
    QGroupBox* addGenerateGausBlock();
    QGroupBox* addGenerateXYBlock();
    QGroupBox* addGenerateMainBlock();
    QGroupBox* addDeMuxBlock(int nIn = ConstArrayBlock::getNumInputs(), int nOut = ConstArrayBlock::getNumOutputs());
    QGroupBox* addLocalProcedureBlock(int nIn = LocalProcedureBlock::getNumInputs(), int nOut = LocalProcedureBlock::getNumOutputs());


    //QGroupBox* addSumBlock();

    void normalize_x_y();
    void runDesign();
    void generateCode();

    //
    void generateAllOutOnlyBlocks(int num);
    void generateAllInputBlocks();
    BlockInfo getBlockIOInfo(QString name); // io 0: input, 1: output
    void getConnectedData(BlockInfo blockInfo, double *data);
    void generateAllOutsOfIOBlocks();
    //


    void drawGraphs();
    void resetOutputs();
    bool isExecutedGood();
    void reset();
    void resetLoops();

    void setBlockEnable(int type, int id, bool flagEn);

    QGroupBox* getBlock(int type, int id);



    Graph *graphs[MAX_BLOCKS];
    int countGraphs;

    ConstantBlock *constBlock[MAX_BLOCKS];
    int countConstBlock;

    ConstArrayBlock *constArrayBlock[MAX_BLOCKS];
    int countConstArrayBlock;

    ExpressionBlock *expressionBlock[MAX_BLOCKS];
    int countExpressionBlock;

    DataSplitBlock *dataSplitBlock[MAX_BLOCKS];
    int countDataSplitBlock;

    AdderBlock *adderBlock[MAX_BLOCKS];
    int countAdderBlock;

    DelayBlock *delayBlock[MAX_BLOCKS];
    int countDelayBlock;

    AccumulatorBlock *accumulatorBlock[MAX_BLOCKS];
    int countAccumulatorBlock;

    ReadFileBlock *readFileBlock[MAX_BLOCKS];
    int countReadFileBlock;

    GetMaxBlock *getMaxBlock[MAX_BLOCKS];
    int countGetMaxBlock;

    LineDisplayBlock *lineDisplayBlock[MAX_BLOCKS];
    int countLineDisplayBlock;

    IfBlock *ifBlock[MAX_BLOCKS];
    int countIfBlock;

    HistFromArrBlock *histFromArrBlock[MAX_BLOCKS];
    int countHistFromArrBlock;

    FillHist *fillHistBlock[MAX_BLOCKS];
    int countFillHistBlock;

    ReadMultiFilesBlock *readMultiFilesBlock[MAX_BLOCKS];
    int countReadMultiFilesBlock;

    GenerateGausBlock *generateGausBlock[MAX_BLOCKS];
    int countgenerateGausBlock;

    GenerateXYBlock *generateXYBlock[MAX_BLOCKS];
    int countgenerateXYBlock;

    MainBlock *generateMainBlock[1];
    int countgenerateMainBlock;

    DeMux *deMuxBlock[MAX_BLOCKS];
    int countDeMuxBlock;

    LocalProcedureBlock *localProcedureBlock[MAX_BLOCKS];
    int countlocalProcedureBlock;



    //SumBlock *sumBlock[MAX_BLOCKS];
    int countSumBlock;

    QStringList strListBlockNames, strListBlockExpOut;
    //QStringListModel *model;
    //QStringListModel *model_exp_out;
    //QStringListModel *model_all_outs;
    QStringList strListAllOuts;

    Simulate *simulate;


};

#endif // MANAGEBLOCKS_H