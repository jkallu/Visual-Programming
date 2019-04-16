#include "manageblocks.h"

ManageBlocks::ManageBlocks()
{
    countConstBlock = 0;
    countConstArrayBlock = 0;
    countExpressionBlock = 0;
    countGraphs = 0;
    countDataSplitBlock = 0;
    countAdderBlock = 0;
    countSumBlock = 0;
    countDelayBlock = 0;
    countAccumulatorBlock = 0;
    countReadFileBlock = 0;
    countGetMaxBlock = 0;
    countLineDisplayBlock = 0;
    countIfBlock = 0;
    countHistFromArrBlock = 0;
    countFillHistBlock = 0;
    countReadMultiFilesBlock = 0;
    countgenerateGausBlock = 0;
    countgenerateXYBlock = 0;
    countgenerateMainBlock = 0;
    countDeMuxBlock = 0;
    countlocalProcedureBlock = 0;
    countNetworkClientBlock = 0;
    countNetworkServerBlock = 0;

    simulate = new Simulate(this);
}

QGroupBox* ManageBlocks::addConstantBlock(){
    constBlock[countConstBlock] = new ConstantBlock(countConstBlock);
    constBlock[countConstBlock]->groupBox->setTitle(constBlock[countConstBlock]->groupBox->title() + "_" + QString::number(countConstBlock));
    constBlock[countConstBlock]->leName->setText("const_block_" + QString::number(countConstBlock));
    constBlock[countConstBlock]->lblNameGrid->setText("const_block_" + QString::number(countConstBlock));
    strListBlockNames.append(constBlock[countConstBlock]->leName->text());
    //model->setStringList(strListBlockNames);
    countConstBlock++;

    return constBlock[countConstBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addExpressionBlock(){
    expressionBlock[countExpressionBlock] = new ExpressionBlock(countExpressionBlock);
    expressionBlock[countExpressionBlock]->groupBox->setTitle(expressionBlock[countExpressionBlock]->groupBox->title() + "_"+ QString::number(countExpressionBlock));
    expressionBlock[countExpressionBlock]->leName->setText("ExpBlock_" + QString::number(countExpressionBlock));
    for(int i = 0; i < expressionBlock[countExpressionBlock]->numOfOutputs; i++)
    {
        expressionBlock[countExpressionBlock]->lblOutData[i]->setText("ExpBlock_" + QString::number(countExpressionBlock) + "_" + QString::number(i));
    }
    countExpressionBlock++;


    return expressionBlock[countExpressionBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addGraphBlock(){
    graphs[countGraphs] = new Graph(countGraphs);
    graphs[countGraphs]->leName->setText("Graph_" + QString::number(countGraphs));
    //graphs[countGraphs]->cbIn1->setModel(model_exp_out);
    //graphs[countGraphs]->cbIn2->setModel(model_exp_out);
    countGraphs++;

    return graphs[countGraphs - 1]->groupBox;
}

QGroupBox* ManageBlocks::addContArrayBlock(int nIn, int nOut){
    /*constArrayBlock[countConstArrayBlock] = new ConstArrayBlock(countConstArrayBlock, nIn, nOut);
    constArrayBlock[countConstArrayBlock]->groupBox->setTitle(constArrayBlock[countConstArrayBlock]->groupBox->title() + "_" + QString::number(countConstArrayBlock));
    constArrayBlock[countConstArrayBlock]->leName->setText("const_array_block_" + QString::number(countConstArrayBlock));
    for(int i = 0; i < constArrayBlock[countConstArrayBlock]->numOfOutputs; i++)
    {
        constArrayBlock[countConstArrayBlock]->lblOutData[i]->setText("const_array_block_" + QString::number(countConstArrayBlock) + "_" + QString::number(i));
    }
    strListBlockNames.append(constArrayBlock[countConstArrayBlock]->leName->text());

    strListBlockExpOut.append(constArrayBlock[countConstArrayBlock]->leName->text());

    strListAllOuts.append(constArrayBlock[countConstArrayBlock]->leName->text());
    countConstArrayBlock++;

    return constArrayBlock[countConstArrayBlock - 1]->groupBox;
    */

    ConstArrayBlock *ab = new ConstArrayBlock(countConstArrayBlock, nIn, nOut);
    ab->groupBox->setTitle(ab->groupBox->title() + "_" + QString::number(countConstArrayBlock));
    ab->leName->setText("const_array_block_" + QString::number(countConstArrayBlock));
    for(int i = 0; i < ab->numOfOutputs; i++)
    {
        ab->lblOutData[i]->setText("const_array_block_" + QString::number(countConstArrayBlock) + "_" + QString::number(i));
    }
    strListBlockNames.append(ab->leName->text());

    strListBlockExpOut.append(ab->leName->text());

    strListAllOuts.append(ab->leName->text());
    countConstArrayBlock++;

    blockIO.push_back(ab);

    return ab->groupBox;

}

QGroupBox* ManageBlocks::addDataSplitBlock(){
    /*dataSplitBlock[countDataSplitBlock] = new DataSplitBlock(countDataSplitBlock);
    dataSplitBlock[countDataSplitBlock]->groupBox->setTitle(dataSplitBlock[countDataSplitBlock]->groupBox->title() + "_"+ QString::number(countDataSplitBlock));
    dataSplitBlock[countDataSplitBlock]->leName->setText("DataSplitBlock_" + QString::number(countDataSplitBlock));
    dataSplitBlock[countDataSplitBlock]->lblOutData[0]->setText("DataSplitBlock_" + QString::number(countDataSplitBlock) + "_0");
    dataSplitBlock[countDataSplitBlock]->lblOutData[1]->setText("DataSplitBlock_" + QString::number(countDataSplitBlock) + "_1");

    countDataSplitBlock++;

    return dataSplitBlock[countDataSplitBlock - 1]->groupBox;*/
    DataSplitBlock *ab = new DataSplitBlock(countConstArrayBlock);
    ab->groupBox->setTitle(ab->groupBox->title() + "_"+ QString::number(countDataSplitBlock));
    ab->leName->setText("DataSplitBlock_" + QString::number(countDataSplitBlock));
    ab->lblOutData[0]->setText("DataSplitBlock_" + QString::number(countDataSplitBlock) + "_0");
    ab->lblOutData[1]->setText("DataSplitBlock_" + QString::number(countDataSplitBlock) + "_1");

    countDataSplitBlock++;


    blockIO.push_back(ab);

    return ab->groupBox;
}

QGroupBox* ManageBlocks::addAdderBlock(){
    adderBlock[countAdderBlock] = new AdderBlock(countAdderBlock);
    adderBlock[countAdderBlock]->groupBox->setTitle(adderBlock[countAdderBlock]->groupBox->title() + "_"+ QString::number(countAdderBlock));
    adderBlock[countAdderBlock]->leName->setText("AdderBlock_" + QString::number(countAdderBlock));
    adderBlock[countAdderBlock]->lblOutData[0]->setText("AdderBlock_" + QString::number(countAdderBlock) + "_0");

    countAdderBlock++;

    return adderBlock[countAdderBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addDelayBlock(){
    delayBlock[countDelayBlock] = new DelayBlock(countDelayBlock);
    delayBlock[countDelayBlock]->groupBox->setTitle(delayBlock[countDelayBlock]->groupBox->title() + "_"+ QString::number(countDelayBlock));
    delayBlock[countDelayBlock]->leName->setText("DelayBlock_" + QString::number(countDelayBlock));
    delayBlock[countDelayBlock]->lblOutData[0]->setText("DelayBlock_" + QString::number(countDelayBlock) + "_0");

    countDelayBlock++;

    return delayBlock[countDelayBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addAccumulatorBlock(){
    accumulatorBlock[countAccumulatorBlock] = new AccumulatorBlock(countAccumulatorBlock);
    accumulatorBlock[countAccumulatorBlock]->groupBox->setTitle(accumulatorBlock[countAccumulatorBlock]->groupBox->title() + "_"+ QString::number(countAccumulatorBlock));
    accumulatorBlock[countAccumulatorBlock]->leName->setText("AccumulatorBlock_" + QString::number(countAccumulatorBlock));
    accumulatorBlock[countAccumulatorBlock]->lblOutData[0]->setText("AccumulatorBlock_" + QString::number(countAccumulatorBlock) + "_0");

    countAccumulatorBlock++;

    return accumulatorBlock[countAccumulatorBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addReadFileBlock(){
    readFileBlock[countReadFileBlock] = new ReadFileBlock(countReadFileBlock);
    readFileBlock[countReadFileBlock]->groupBox->setTitle(readFileBlock[countReadFileBlock]->groupBox->title() + "_"+ QString::number(countReadFileBlock));
    readFileBlock[countReadFileBlock]->leName->setText("ReadFileBlock_" + QString::number(countReadFileBlock));
    readFileBlock[countReadFileBlock]->lblOutData[0]->setText("ReadFileBlock_" + QString::number(countReadFileBlock) + "_0");

    countReadFileBlock++;

    return readFileBlock[countReadFileBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addGetMaxBlock(){
    getMaxBlock[countGetMaxBlock] = new GetMaxBlock(countReadFileBlock);
    getMaxBlock[countGetMaxBlock]->groupBox->setTitle(getMaxBlock[countGetMaxBlock]->groupBox->title() + "_"+ QString::number(countGetMaxBlock));
    getMaxBlock[countGetMaxBlock]->leName->setText("GetMaxBlock_" + QString::number(countGetMaxBlock));
    getMaxBlock[countGetMaxBlock]->lblOutData[0]->setText("GetMaxBlock_" + QString::number(countGetMaxBlock) + "_0");

    countGetMaxBlock++;

    return getMaxBlock[countGetMaxBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addLineDisplayBlock(){
    lineDisplayBlock[countLineDisplayBlock] = new LineDisplayBlock(countLineDisplayBlock);
    lineDisplayBlock[countLineDisplayBlock]->groupBox->setTitle(lineDisplayBlock[countLineDisplayBlock]->groupBox->title() + "_"+ QString::number(countLineDisplayBlock));
    lineDisplayBlock[countLineDisplayBlock]->leName->setText("LineDisplayBlock_" + QString::number(countLineDisplayBlock));
    //lineDisplayBlock[countLineDisplayBlock]->lblOutData[0]->setText("LineDisplayBlock_" + QString::number(countLineDisplayBlock) + "_0");

    countLineDisplayBlock++;

    return lineDisplayBlock[countLineDisplayBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addIfBlock(){
    ifBlock[countIfBlock] = new IfBlock(countIfBlock);
    ifBlock[countIfBlock]->leExp->setText(ifBlock[countIfBlock]->lblInData[0]->text());
    ifBlock[countIfBlock]->leName->setText("IfBlock_" + QString::number(countIfBlock));
    ifBlock[countIfBlock]->lblOutData[0]->setText("If_" + QString::number(countIfBlock) + "_True");
    ifBlock[countIfBlock]->lblOutData[1]->setText("If_" + QString::number(countIfBlock) + "_False");

    countIfBlock++;


    return ifBlock[countIfBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addHistFromArrBlock(){
    histFromArrBlock[countHistFromArrBlock] = new HistFromArrBlock(countHistFromArrBlock);
    histFromArrBlock[countHistFromArrBlock]->leName->setText("HistFromArrBlock_" + QString::number(countHistFromArrBlock));
    histFromArrBlock[countHistFromArrBlock]->lblOutData[0]->setText("HistFromArr_" + QString::number(countHistFromArrBlock) + "_x");
    histFromArrBlock[countHistFromArrBlock]->lblOutData[1]->setText("HistFromArr_" + QString::number(countHistFromArrBlock) + "_y");

    countHistFromArrBlock++;


    return histFromArrBlock[countHistFromArrBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addFillHistBlock(){
    fillHistBlock[countFillHistBlock] = new FillHist(countFillHistBlock);
    fillHistBlock[countFillHistBlock]->leName->setText("FillHistBlock_" + QString::number(countFillHistBlock));
    fillHistBlock[countFillHistBlock]->lblOutData[0]->setText("FillHist_" + QString::number(countFillHistBlock) + "_x");
    fillHistBlock[countFillHistBlock]->lblOutData[1]->setText("FillHist_" + QString::number(countFillHistBlock) + "_y");
    countFillHistBlock++;


    return fillHistBlock[countFillHistBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addReadMultiFilesBlock(){
    readMultiFilesBlock[countReadMultiFilesBlock] = new ReadMultiFilesBlock(countReadMultiFilesBlock);
    readMultiFilesBlock[countReadMultiFilesBlock]->leName->setText("ReadMultiFilesBlock_" + QString::number(countReadMultiFilesBlock));
    readMultiFilesBlock[countReadMultiFilesBlock]->lblOutData[0]->setText("ReadMultiFiles_" + QString::number(countReadMultiFilesBlock));

    countReadMultiFilesBlock++;


    return readMultiFilesBlock[countReadMultiFilesBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addGenerateGausBlock(){
    generateGausBlock[countgenerateGausBlock] = new GenerateGausBlock(countgenerateGausBlock);
    generateGausBlock[countgenerateGausBlock]->leName->setText("GenerateGausBlock_" + QString::number(countgenerateGausBlock));
    generateGausBlock[countgenerateGausBlock]->lblOutData[0]->setText("GenerateGaus_" + QString::number(countgenerateGausBlock));

    countgenerateGausBlock++;


    return generateGausBlock[countgenerateGausBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addGenerateXYBlock(){
    generateXYBlock[countgenerateXYBlock] = new GenerateXYBlock(countgenerateXYBlock);
    generateXYBlock[countgenerateXYBlock]->leName->setText("GenerateXYBlock_" + QString::number(countgenerateXYBlock));
    generateXYBlock[countgenerateXYBlock]->lblOutData[0]->setText("GenerateXY_" + QString::number(countgenerateXYBlock) + "_x");
    generateXYBlock[countgenerateXYBlock]->lblOutData[1]->setText("GenerateXY_" + QString::number(countgenerateXYBlock) + "_y");

    countgenerateXYBlock++;


    return generateXYBlock[countgenerateXYBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addGenerateMainBlock(){
    generateMainBlock[countgenerateMainBlock] = new MainBlock(countgenerateMainBlock);
    generateMainBlock[countgenerateMainBlock]->leName->setText("MainBlock_" + QString::number(countgenerateMainBlock));
    for(int i = 0; i < generateMainBlock[countgenerateMainBlock]->numOfOutputs; i++)
    {
        generateMainBlock[countgenerateMainBlock]->lblOutData[0]->setText("MainBlock_" + QString::number(countgenerateMainBlock) + "_" + QString::number(i));
    }

    countgenerateMainBlock++;


    return generateMainBlock[countgenerateMainBlock - 1]->groupBox;

}

QGroupBox* ManageBlocks::addDeMuxBlock(int nIn, int nOut){
    deMuxBlock[countDeMuxBlock] = new DeMux(countDeMuxBlock, nIn, nOut);
    deMuxBlock[countDeMuxBlock]->leName->setText("DeMuxBlock_" + QString::number(countDeMuxBlock));
    for(int i = 0; i < deMuxBlock[countDeMuxBlock]->numOfOutputs; i++)
    {
        deMuxBlock[countDeMuxBlock]->lblOutData[i]->setText("DeMuxBlock_" + QString::number(countDeMuxBlock) + "_" + QString::number(i));
    }

    countDeMuxBlock++;


    return deMuxBlock[countDeMuxBlock - 1]->groupBox;
}
QGroupBox* ManageBlocks::addLocalProcedureBlock(int nIn, int nOut){
    localProcedureBlock[countlocalProcedureBlock] = new LocalProcedureBlock(countlocalProcedureBlock, nIn, nOut);
    localProcedureBlock[countlocalProcedureBlock]->leName->setText("LocalProcedureBlock_" + QString::number(countlocalProcedureBlock));
    for(int i = 0; i < localProcedureBlock[countlocalProcedureBlock]->numOfOutputs; i++)
    {
        localProcedureBlock[countlocalProcedureBlock]->lblOutData[i]->setText("LocalProcedureBlock_" + QString::number(countlocalProcedureBlock) + "_" + QString::number(i));
    }

    countlocalProcedureBlock++;


    return localProcedureBlock[countlocalProcedureBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addNetworkClientBlock(int nIn, int nOut){
    networkClientBlock[countNetworkClientBlock] = new NetworkClientBlock(countNetworkClientBlock, nIn, nOut);
    networkClientBlock[countNetworkClientBlock]->leName->setText("NetworkClientBlock_" + QString::number(countNetworkClientBlock));
    for(int i = 0; i < networkClientBlock[countNetworkClientBlock]->numOfOutputs; i++)
    {
        networkClientBlock[countNetworkClientBlock]->lblOutData[i]->setText("NetworkClientBlock_" + QString::number(countNetworkClientBlock) + "_" + QString::number(i));
    }

    countNetworkClientBlock++;


    return networkClientBlock[countNetworkClientBlock - 1]->groupBox;
}

QGroupBox* ManageBlocks::addNetworkServerBlock(int nIn, int nOut){
    networkServerBlock[countNetworkServerBlock] = new NetworkServerBlock(countNetworkServerBlock, nIn, nOut);
    networkServerBlock[countNetworkServerBlock]->leName->setText("NetworkServerBlock_" + QString::number(countNetworkServerBlock));
    for(int i = 0; i < networkServerBlock[countNetworkServerBlock]->numOfOutputs; i++)
    {
        networkServerBlock[countNetworkServerBlock]->lblOutData[i]->setText("NetworkServerBlock_" + QString::number(countNetworkServerBlock) + "_" + QString::number(i));
    }

    countNetworkServerBlock++;


    return networkServerBlock[countNetworkServerBlock - 1]->groupBox;
}


/*QGroupBox* ManageBlocks::addSumBlock(){
    sumBlock[countSumBlock] = new SumBlock(countSumBlock);
    sumBlock[countSumBlock]->groupBox->setTitle(sumBlock[countSumBlock]->groupBox->title() + "_"+ QString::number(countSumBlock));
    sumBlock[countSumBlock]->leName->setText("SumBlock_" + QString::number(countSumBlock));
    sumBlock[countSumBlock]->leOut->setText("SumBlock_" + QString::number(countSumBlock));

    countSumBlock++;

    return sumBlock[countSumBlock - 1]->groupBox;
}*/

void ManageBlocks::generateCode()
{
    QString dir = "../Node/nodegencodes/";
    //QString dir = "/home/jin/Downloads/nodegencodes/";
    // 1. First we generate outputcodes for constant array block
    /*for(int i = 0; i < countConstArrayBlock; i++){
        if(constArrayBlock[i]->isBlockEnabled()){
            constArrayBlock[i]->generateCode(dir);
            generateMainBlock[0]->addHeader(constArrayBlock[i]->leName->text());
            simulate->addSource(constArrayBlock[i]->leName->text());

            Func_t func;
            func.funcName = constArrayBlock[i]->leName->text().toStdString();
            func.type = constArrayBlock[i]->getType();
            func.arrayNum = i;
            simulate->func.push_back(func);
         }
    }*/
    for(size_t i = 0; i < blockIO.size(); i++){
        if(blockIO.at(i)->isBlockEnabled()){
            blockIO.at(i)->generateCode(dir);
            generateMainBlock[0]->addHeader(blockIO.at(i)->leName->text());
            simulate->addSource(blockIO.at(i)->leName->text());

            Func_t func;
            func.funcName = blockIO.at(i)->leName->text().toStdString();
            func.type = blockIO.at(i)->getType();
            func.arrayNum = blockIO.at(i)->getId();
            simulate->func.push_back(func);
        }
    }

    // 2. Expression blocks
    for(int i = 0; i < countExpressionBlock; i++){
        if(expressionBlock[i]->isBlockEnabled()){
            expressionBlock[i]->generateCode(dir);
            generateMainBlock[0]->addHeader(expressionBlock[i]->leName->text());
            simulate->addSource(expressionBlock[i]->leName->text());

            Func_t func;
            func.funcName = expressionBlock[i]->leName->text().toStdString();
            func.type = expressionBlock[i]->getType();
            func.arrayNum = i;
            simulate->func.push_back(func);
        }
    }

    // 10. Linedisplay blocks
    for(int i = 0; i < countLineDisplayBlock; i++){
        if(lineDisplayBlock[i]->isBlockEnabled()){
            lineDisplayBlock[i]->generateCode(dir);
            generateMainBlock[0]->addHeader(lineDisplayBlock[i]->leName->text());
            simulate->addSource(lineDisplayBlock[i]->leName->text());

            Func_t func;
            func.funcName = lineDisplayBlock[i]->leName->text().toStdString();
            func.type = lineDisplayBlock[i]->getType();
            func.arrayNum = i;
            simulate->func.push_back(func);
        }
    }

    // 18. LocalProcedure block
    for(int i = 0; i < countlocalProcedureBlock; i++){
        if(localProcedureBlock[i]->isBlockEnabled()){
            localProcedureBlock[i]->generateCode(dir);
            generateMainBlock[0]->addHeader(localProcedureBlock[i]->leName->text());
            simulate->addSource(localProcedureBlock[i]->leName->text());

            Func_t func;
            func.funcName = localProcedureBlock[i]->leName->text().toStdString();
            func.type = localProcedureBlock[i]->getType();
            func.arrayNum = i;
            simulate->func.push_back(func);
        }
    }

    // 18. NetworkClient block
    for(int i = 0; i < countNetworkClientBlock; i++){
        if(networkClientBlock[i]->isBlockEnabled()){
            networkClientBlock[i]->generateCode(dir);
            generateMainBlock[0]->addHeader(networkClientBlock[i]->leName->text());
            simulate->addSource(networkClientBlock[i]->leName->text());

            Func_t func;
            func.funcName = networkClientBlock[i]->leName->text().toStdString();
            func.type = networkClientBlock[i]->getType();
            func.arrayNum = i;
            simulate->func.push_back(func);
        }
    }

    // 18. NetworkServer block
    for(int i = 0; i < countNetworkServerBlock; i++){
        if(networkServerBlock[i]->isBlockEnabled()){
            networkServerBlock[i]->generateCode(dir);
            generateMainBlock[0]->addHeader(networkServerBlock[i]->leName->text());
            simulate->addSource(networkServerBlock[i]->leName->text());

            Func_t func;
            func.funcName = networkServerBlock[i]->leName->text().toStdString();
            func.type = networkServerBlock[i]->getType();
            func.arrayNum = i;
            simulate->func.push_back(func);
        }
    }

    // 18. DataSplit block
   /* for(int i = 0; i < countDataSplitBlock; i++){
        if(dataSplitBlock[i]->isBlockEnabled()){
            dataSplitBlock[i]->generateCode(dir);
            generateMainBlock[0]->addHeader(dataSplitBlock[i]->leName->text());
            simulate->addSource(dataSplitBlock[i]->leName->text());

            Func_t func;
            func.funcName = dataSplitBlock[i]->leName->text().toStdString();
            func.type = dataSplitBlock[i]->getType();
            func.arrayNum = i;
            simulate->func.push_back(func);
        }
    }*/

    // 18. Demux block
    for(int i = 0; i < countDeMuxBlock; i++){
        if(deMuxBlock[i]->isBlockEnabled()){
            deMuxBlock[i]->generateCode(dir);
            generateMainBlock[0]->addHeader(deMuxBlock[i]->leName->text());
            simulate->addSource(deMuxBlock[i]->leName->text());

            Func_t func;
            func.funcName = deMuxBlock[i]->leName->text().toStdString();
            func.type = deMuxBlock[i]->getType();
            func.arrayNum = i;
            simulate->func.push_back(func);
        }
    }

    // 4. graph block
    for(int i = 0; i < countGraphs; i++){
        if(graphs[i]->isBlockEnabled()){
            //graphs[i]->generateCode(dir);
            //generateMainBlock[0]->addHeader(graphs[i]->leName->text());
            //simulate->addSource(graphs[i]->leName->text());

            Func_t func;
            func.funcName = graphs[i]->leName->text().toStdString();
            func.type = graphs[i]->getType();
            func.arrayNum = i;
            simulate->func.push_back(func);
        }
    }

    //0. MainBlock
    for(int i = 0; i < countgenerateMainBlock; i++){
        if(generateMainBlock[i]->isBlockEnabled()){
            generateMainBlock[i]->generateCode(dir);
            qDebug() << generateMainBlock[i]->lblOutConToBlock[0]->text().toStdString().c_str() ;

            Func_t func;
            func.funcName = generateMainBlock[i]->leName->text().toStdString();
            func.type = generateMainBlock[i]->getType();
            func.arrayNum = i;
            simulate->func.push_back(func);


            simulate->start((char*)generateMainBlock[i]->lblOutConToBlock[0]->text().toStdString().c_str(), dir);
        }
    }


}

void ManageBlocks::runDesign(){

    if(generateMainBlock[0] != nullptr)
        generateCode();

    /* int maxIter = 100;
    int readMultiFileLoop = 0;

    if(countReadMultiFilesBlock > 0){
        readMultiFileLoop = readMultiFilesBlock[0]->numberOfFiles();
    }

    readMultiFileLoop = readMultiFileLoop > 0? readMultiFileLoop: 1;

    qDebug() << "loops " << readMultiFileLoop;

    for(int num = 0; num < readMultiFileLoop; num++){
        for(int i = 0; i < maxIter; i++){
            generateAllOutOnlyBlocks(num);
            generateAllOutsOfIOBlocks();
            generateAllInputBlocks();
            if(isExecutedGood()){
                drawGraphs();
                qDebug() << "Executed in " << i << " iterations ";
                break;
            }
            if(i == 99){
                qDebug() << "Maximum iterations " << maxIter << " Reached ";
            }
        }
        reset();
    }
    resetLoops(); // fill loops*/
}

bool ManageBlocks::isExecutedGood(){
    /*for(int i = 0; i < countConstArrayBlock; i++){
        if(!constArrayBlock[i]->isExecutedFull() && constArrayBlock[i]->isBlockEnabled()){
            return false;
        }
    }*/

    for(size_t i = 0; i < blockIO.size(); i++){
        if(!blockIO.at(i)->isExecutedFull() && blockIO.at(i)->isBlockEnabled()){
            return false;
        }
    }

    /*for(int i = 0; i < countDataSplitBlock; i++){
        if(!dataSplitBlock[i]->isExecutedFull() && dataSplitBlock[i]->isBlockEnabled()){
            return false;
        }
    }*/

    for(int i = 0; i < countExpressionBlock; i++){
        if(!expressionBlock[i]->isExecutedFull() && expressionBlock[i]->isBlockEnabled()){
            return false;
        }
    }

    for(int i = 0; i < countGraphs; i++){
        if(!graphs[i]->isExecutedFull() && graphs[i]->isBlockEnabled()){
            return false;
        }
    }

    for(int i = 0; i < countAdderBlock; i++){
        if(!adderBlock[i]->isExecutedFull() && adderBlock[i]->isBlockEnabled()){
            return false;
        }
    }

    for(int i = 0; i < countDelayBlock; i++){
        if(!delayBlock[i]->isExecutedFull() && delayBlock[i]->isBlockEnabled()){
            return false;
        }
    }
    for(int i = 0; i < countAccumulatorBlock; i++){
        if(!accumulatorBlock[i]->isExecutedFull() && accumulatorBlock[i]->isBlockEnabled()){
            return false;
        }
    }
    for(int i = 0; i < countReadFileBlock; i++){
        if(!readFileBlock[i]->isExecutedFull() && readFileBlock[i]->isBlockEnabled()){
            return false;
        }
    }

    for(int i = 0; i < countGetMaxBlock; i++){
        if(!getMaxBlock[i]->isExecutedFull() && getMaxBlock[i]->isBlockEnabled()){
            return false;
        }
    }
    for(int i = 0; i < countLineDisplayBlock; i++){
        if(!lineDisplayBlock[i]->isExecutedFull() && lineDisplayBlock[i]->isBlockEnabled()){
            return false;
        }
    }

    for(int i = 0; i < countIfBlock; i++){
        if(!ifBlock[i]->isExecutedFull() && ifBlock[i]->isBlockEnabled()){
            return false;
        }
    }

    for(int i = 0; i < countHistFromArrBlock; i++){
        if(!histFromArrBlock[i]->isExecutedFull() && histFromArrBlock[i]->isBlockEnabled()){
            return false;
        }
    }

    for(int i = 0; i < countFillHistBlock; i++){
        if(!fillHistBlock[i]->isExecutedFull() && fillHistBlock[i]->isBlockEnabled()){
            return false;
        }
    }

    for(int i = 0; i < countReadMultiFilesBlock; i++){
        if(!readMultiFilesBlock[i]->isExecutedFull() && readMultiFilesBlock[i]->isBlockEnabled()){
            return false;
        }
    }

    for(int i = 0; i < countgenerateGausBlock; i++){
        if(!generateGausBlock[i]->isExecutedFull() && generateGausBlock[i]->isBlockEnabled()){
            return false;
        }
    }

    for(int i = 0; i < countgenerateXYBlock; i++){
        if(!generateXYBlock[i]->isExecutedFull() && generateXYBlock[i]->isBlockEnabled()){
            return false;
        }
    }


    return true;
}

void ManageBlocks::reset(){
    /*for(int i = 0; i < countConstArrayBlock; i++){
        constArrayBlock[i]->reset();
    }*/
    for(size_t i = 0; i < blockIO.size(); i++){
        blockIO.at(i)->reset();
    }

    /*for(int i = 0; i < countDataSplitBlock; i++){
        dataSplitBlock[i]->reset();
    }*/

    for(int i = 0; i < countExpressionBlock; i++){
        expressionBlock[i]->reset();
    }

    for(int i = 0; i < countGraphs; i++){
        graphs[i]->reset();
    }
    for(int i = 0; i < countAdderBlock; i++){
        adderBlock[i]->reset();
    }
    for(int i = 0; i < countDelayBlock; i++){
        delayBlock[i]->reset();
    }
    for(int i = 0; i < countAccumulatorBlock; i++){
        accumulatorBlock[i]->reset();
    }
    for(int i = 0; i < countReadFileBlock; i++){
        readFileBlock[i]->reset();
    }

    for(int i = 0; i < countGetMaxBlock; i++){
        getMaxBlock[i]->reset();
    }

    for(int i = 0; i < countLineDisplayBlock; i++){
        lineDisplayBlock[i]->reset();
    }

    for(int i = 0; i < countIfBlock; i++){
        ifBlock[i]->reset();
    }

    for(int i = 0; i < countHistFromArrBlock; i++){
        histFromArrBlock[i]->reset();
    }

    for(int i = 0; i < countFillHistBlock; i++){
        fillHistBlock[i]->reset();
    }

    for(int i = 0; i < countReadMultiFilesBlock; i++){
        readMultiFilesBlock[i]->reset();
    }

    for(int i = 0; i < countgenerateGausBlock; i++){
        generateGausBlock[i]->reset();
    }

    for(int i = 0; i < countgenerateXYBlock; i++){
        generateXYBlock[i]->reset();
    }

    for(int i = 0; i < countgenerateMainBlock; i++){
        generateMainBlock[i]->reset();
        generateMainBlock[i]->resetHeader();
    }

    for(int i = 0; i < countDeMuxBlock; i++){
        deMuxBlock[i]->reset();
        //        /deMuxBlock[i]->resetHeader();
    }

    for(int i = 0; i < countlocalProcedureBlock; i++){
        localProcedureBlock[i]->reset();
        //        /deMuxBlock[i]->resetHeader();
    }
    for(int i = 0; i < countNetworkClientBlock; i++){
        networkClientBlock[i]->reset();
        //        /deMuxBlock[i]->resetHeader();
    }
    for(int i = 0; i < countNetworkServerBlock; i++){
        networkServerBlock[i]->reset();
        //        /deMuxBlock[i]->resetHeader();
    }

}

void ManageBlocks::resetLoops(){
    for(int i = 0; i < countFillHistBlock; i++){
        fillHistBlock[i]->flagInit = false;
    }
}


// generate outputs for all the out only blocks which are not depending on other blocks
void ManageBlocks::generateAllOutOnlyBlocks(int num){
    // 1. First we generate outputs for constant array block
    for(int i = 0; i < countConstArrayBlock; i++){
        for(int j = 0; j < constArrayBlock[i]->numOfOutputs; j++){
            if(!constArrayBlock[i]->flagOut[j] && constArrayBlock[i]->isBlockEnabled()){
                constArrayBlock[i]->generateArrayOutputs();
            }
        }
    }

    // 8. ReadFile block
    for(int i = 0; i < countReadFileBlock; i++){
        for(int j = 0; j < readFileBlock[i]->numOfOutputs; j++){
            if(!readFileBlock[i]->flagOut[j] && readFileBlock[i]->isBlockEnabled()){
                readFileBlock[i]->generateArrayOutputs();
            }
        }
    }

    // 8. ReadMultiFiles block
    for(int i = 0; i < countReadMultiFilesBlock; i++){
        for(int j = 0; j < readMultiFilesBlock[i]->numOfOutputs; j++){
            if(!readMultiFilesBlock[i]->flagOut[j] && readMultiFilesBlock[i]->isBlockEnabled()){
                readMultiFilesBlock[i]->generateArrayOutputs(num);
            }
        }
    }

    // 8. GenerateGaus block
    for(int i = 0; i < countgenerateGausBlock; i++){
        for(int j = 0; j < generateGausBlock[i]->numOfOutputs; j++){
            if(!generateGausBlock[i]->flagOut[j] && generateGausBlock[i]->isBlockEnabled()){
                generateGausBlock[i]->generateArrayOutputs();
            }
        }
    }

}

// generate inputs for all the IO blocks and as well as for Input only blocks
void ManageBlocks::generateAllInputBlocks(){
    // 2. Expression blocks
    for(int i = 0; i < countExpressionBlock; i++){
        for(int j = 0; j < expressionBlock[i]->numOfInputs; j++){
            if(!expressionBlock[i]->flagIn[j] && expressionBlock[i]->isBlockEnabled()){
                BlockInfo blockInfo =  getBlockIOInfo(expressionBlock[i]->lblInData[j]->text());
                if(blockInfo.status == 0){ // found the good connection
                    expressionBlock[i]->createIOArray(0, j, blockInfo.size); // input
                    getConnectedData(blockInfo, expressionBlock[i]->in[j]);
                    expressionBlock[i]->flagIn[j] = true;
                }
            }
        }
    }

    // 3. graph blocks
    for(int i = 0; i < countGraphs; i++){
        for(int j = 0; j < graphs[i]->numOfInputs; j++){
            if(!graphs[i]->flagIn[j] && graphs[i]->isBlockEnabled()){
                BlockInfo blockInfo =  getBlockIOInfo(graphs[i]->lblInData[j]->text());
                if(blockInfo.status == 0){ // found the good connection
                    graphs[i]->createIOArray(0, j, blockInfo.size); // input
                    getConnectedData(blockInfo, graphs[i]->in[j]);
                    graphs[i]->flagIn[j] = true;
                }
            }
        }
    }



    // 4. DataSplit blocks
    for(int i = 0; i < countDataSplitBlock; i++){
        for(int j = 0; j < dataSplitBlock[i]->numOfInputs; j++){
            if(!dataSplitBlock[i]->flagIn[j] && dataSplitBlock[i]->isBlockEnabled()){
                BlockInfo blockInfo =  getBlockIOInfo(dataSplitBlock[i]->lblInData[j]->text());
                if(blockInfo.status == 0){ // found the good connection
                    dataSplitBlock[i]->createIOArray(0, j, blockInfo.size); // input
                    getConnectedData(blockInfo, dataSplitBlock[i]->in[j]);
                    dataSplitBlock[i]->flagIn[j] = true;
                }
            }
        }
    }

    // 5. Adder blocks
    for(int i = 0; i < countAdderBlock; i++){
        for(int j = 0; j < adderBlock[i]->numOfInputs; j++){
            if(!adderBlock[i]->flagIn[j] && adderBlock[i]->isBlockEnabled()){
                BlockInfo blockInfo =  getBlockIOInfo(adderBlock[i]->lblInData[j]->text());
                if(blockInfo.status == 0){ // found the good connection
                    adderBlock[i]->createIOArray(0, j, blockInfo.size); // input
                    getConnectedData(blockInfo, adderBlock[i]->in[j]);
                    adderBlock[i]->flagIn[j] = true;
                }
            }
        }
    }

    // 6. Delay blocks
    for(int i = 0; i < countDelayBlock; i++){
        for(int j = 0; j < delayBlock[i]->numOfInputs; j++){
            if(!delayBlock[i]->flagIn[j] && delayBlock[i]->isBlockEnabled()){
                BlockInfo blockInfo =  getBlockIOInfo(delayBlock[i]->lblInData[j]->text());
                if(blockInfo.status == 0){ // found the good connection
                    delayBlock[i]->createIOArray(0, j, blockInfo.size); // input
                    getConnectedData(blockInfo, delayBlock[i]->in[j]);
                    delayBlock[i]->flagIn[j] = true;
                }
            }
        }
    }

    // 7. Accumulator blocks
    for(int i = 0; i < countAccumulatorBlock; i++){
        for(int j = 0; j < accumulatorBlock[i]->numOfInputs; j++){
            if(!accumulatorBlock[i]->flagIn[j] && accumulatorBlock[i]->isBlockEnabled()){
                BlockInfo blockInfo =  getBlockIOInfo(accumulatorBlock[i]->lblInData[j]->text());
                if(blockInfo.status == 0){ // found the good connection
                    accumulatorBlock[i]->createIOArray(0, j, blockInfo.size); // input
                    getConnectedData(blockInfo, accumulatorBlock[i]->in[j]);
                    accumulatorBlock[i]->flagIn[j] = true;
                }
            }
        }
    }

    // 9. GetMax blocks
    for(int i = 0; i < countGetMaxBlock; i++){
        for(int j = 0; j < getMaxBlock[i]->numOfInputs; j++){
            if(!getMaxBlock[i]->flagIn[j] && getMaxBlock[i]->isBlockEnabled()){
                BlockInfo blockInfo =  getBlockIOInfo(getMaxBlock[i]->lblInData[j]->text());
                if(blockInfo.status == 0){ // found the good connection
                    getMaxBlock[i]->createIOArray(0, j, blockInfo.size); // input
                    getConnectedData(blockInfo, getMaxBlock[i]->in[j]);
                    getMaxBlock[i]->flagIn[j] = true;
                }
            }
        }
    }

    // 10. LineDisplay blocks
    for(int i = 0; i < countLineDisplayBlock; i++){
        for(int j = 0; j < lineDisplayBlock[i]->numOfInputs; j++){
            if(!lineDisplayBlock[i]->flagIn[j] && lineDisplayBlock[i]->isBlockEnabled()){
                BlockInfo blockInfo =  getBlockIOInfo(lineDisplayBlock[i]->lblInData[j]->text());
                if(blockInfo.status == 0){ // found the good connection
                    lineDisplayBlock[i]->createIOArray(0, j, blockInfo.size); // input
                    getConnectedData(blockInfo, lineDisplayBlock[i]->in[j]);
                    lineDisplayBlock[i]->flagIn[j] = true;
                    lineDisplayBlock[i]->generateOutputs();
                }
            }
        }
    }

    // 11. If blocks
    for(int i = 0; i < countIfBlock; i++){
        for(int j = 0; j < ifBlock[i]->numOfInputs; j++){
            if(!ifBlock[i]->flagIn[j] && ifBlock[i]->isBlockEnabled()){
                BlockInfo blockInfo =  getBlockIOInfo(ifBlock[i]->lblInData[j]->text());
                if(blockInfo.status == 0){ // found the good connection
                    ifBlock[i]->createIOArray(0, j, blockInfo.size); // input
                    getConnectedData(blockInfo, ifBlock[i]->in[j]);
                    ifBlock[i]->flagIn[j] = true;
                }
            }
        }
    }

    // 12. HistFromArr blocks
    for(int i = 0; i < countHistFromArrBlock; i++){
        for(int j = 0; j < histFromArrBlock[i]->numOfInputs; j++){
            if(!histFromArrBlock[i]->flagIn[j] && histFromArrBlock[i]->isBlockEnabled()){
                BlockInfo blockInfo =  getBlockIOInfo(histFromArrBlock[i]->lblInData[j]->text());
                if(blockInfo.status == 0){ // found the good connection
                    histFromArrBlock[i]->createIOArray(0, j, blockInfo.size); // input
                    getConnectedData(blockInfo, histFromArrBlock[i]->in[j]);
                    histFromArrBlock[i]->flagIn[j] = true;
                }
            }
        }
    }

    // 13. FillHist blocks
    for(int i = 0; i < countFillHistBlock; i++){
        for(int j = 0; j < fillHistBlock[i]->numOfInputs; j++){
            if(!fillHistBlock[i]->flagIn[j] && fillHistBlock[i]->isBlockEnabled()){
                BlockInfo blockInfo =  getBlockIOInfo(fillHistBlock[i]->lblInData[j]->text());
                if(blockInfo.status == 0){ // found the good connection
                    fillHistBlock[i]->createIOArray(0, j, blockInfo.size); // input
                    getConnectedData(blockInfo, fillHistBlock[i]->in[j]);
                    fillHistBlock[i]->flagIn[j] = true;
                }
            }
        }
    }

    // 16. GenerateXY blocks
    for(int i = 0; i < countgenerateXYBlock; i++){
        for(int j = 0; j < generateXYBlock[i]->numOfInputs; j++){
            if(!generateXYBlock[i]->flagIn[j] && generateXYBlock[i]->isBlockEnabled()){
                BlockInfo blockInfo =  getBlockIOInfo(generateXYBlock[i]->lblInData[j]->text());
                if(blockInfo.status == 0){ // found the good connection
                    generateXYBlock[i]->createIOArray(0, j, blockInfo.size); // input
                    getConnectedData(blockInfo, generateXYBlock[i]->in[j]);
                    generateXYBlock[i]->flagIn[j] = true;
                }
            }
        }
    }
}

void ManageBlocks::getConnectedData(BlockInfo blockInfo, double *data){
    //1.get data from constant array block
    if(blockInfo.type == 1){
        if(blockInfo.io == 1){
            for(int i = 0; i < constArrayBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = constArrayBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //2.get data from expression block
    if(blockInfo.type == 2){
        if(blockInfo.io == 1){
            for(int i = 0; i < expressionBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = expressionBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //4.get data from datasplit block
    else if(blockInfo.type == 4){
        if(blockInfo.io == 1){
            for(int i = 0; i < dataSplitBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = dataSplitBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //5.get data from Adder block
    else if(blockInfo.type == 5){
        if(blockInfo.io == 1){
            for(int i = 0; i < adderBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = adderBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //6.get data from Delay block
    else if(blockInfo.type == 6){
        if(blockInfo.io == 1){
            for(int i = 0; i < delayBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = delayBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //7.get data from Accumulator block
    else if(blockInfo.type == 7){
        if(blockInfo.io == 1){
            for(int i = 0; i < accumulatorBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = accumulatorBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //8.get data from ReadFile block
    else if(blockInfo.type == 8){
        if(blockInfo.io == 1){
            for(int i = 0; i < readFileBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = readFileBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //9.get data from GetMax block
    else if(blockInfo.type == 9){
        if(blockInfo.io == 1){
            for(int i = 0; i < getMaxBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = getMaxBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //11.get data from if block
    else if(blockInfo.type == 11){
        if(blockInfo.io == 1){
            for(int i = 0; i < ifBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = ifBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //12.get data from histFromArr block
    else if(blockInfo.type == 12){
        if(blockInfo.io == 1){
            for(int i = 0; i < histFromArrBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = histFromArrBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //13.get data from fillhist block
    else if(blockInfo.type == 13){
        if(blockInfo.io == 1){
            for(int i = 0; i < fillHistBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = fillHistBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //14.get data from ReadMultiFiles block
    else if(blockInfo.type == 14){
        if(blockInfo.io == 1){
            for(int i = 0; i < readMultiFilesBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = readMultiFilesBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //15.get data from GenerateGaus block
    else if(blockInfo.type == 15){
        if(blockInfo.io == 1){
            for(int i = 0; i < generateGausBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = generateGausBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }

    //16.get data from GenerateXY block
    else if(blockInfo.type == 16){
        if(blockInfo.io == 1){
            for(int i = 0; i < generateXYBlock[blockInfo.id]->getSize(blockInfo.io, blockInfo.num); i++){
                data[i] = generateXYBlock[blockInfo.id]->out[blockInfo.num][i];
            }
        }
    }
}

// Get the information about the io connection
BlockInfo ManageBlocks::getBlockIOInfo(QString name){
    BlockInfo blockInfo;
    blockInfo.status = -1;

    // 1. ConstArrayBlock
    for(int i = 0; i < countConstArrayBlock; i++){
        for(int j = 0; j < constArrayBlock[i]->numOfOutputs; j++){
            if(name == constArrayBlock[i]->lblOutData[j]->text()){
                if(constArrayBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of expressionBlock
                    blockInfo.io = 1; // 1 for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 1; // type
                    blockInfo.status = 0; // good
                    blockInfo.size = constArrayBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

    // 2. ExpressionBlock
    for(int i = 0; i < countExpressionBlock; i++){
        for(int j = 0; j < expressionBlock[i]->numOfOutputs; j++){
            if(name == expressionBlock[i]->lblOutData[j]->text()){
                if(expressionBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of expressionBlock
                    blockInfo.io = 1; // 01for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 2;
                    blockInfo.status = 0;
                    blockInfo.size = expressionBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }
    // 4. DataSplitBlock
    for(int i = 0; i < countDataSplitBlock; i++){
        for(int j = 0; j < dataSplitBlock[i]->numOfOutputs; j++){
            if(name == dataSplitBlock[i]->lblOutData[j]->text()){
                if(dataSplitBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of expressionBlock
                    blockInfo.io = 1; // 01for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 4;
                    blockInfo.status = 0;
                    blockInfo.size = dataSplitBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

    // 5. AdderBlock
    for(int i = 0; i < countAdderBlock; i++){
        for(int j = 0; j < adderBlock[i]->numOfOutputs; j++){
            if(name == adderBlock[i]->lblOutData[j]->text()){
                if(adderBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of expressionBlock
                    blockInfo.io = 1; // 01for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 5;
                    blockInfo.status = 0;
                    blockInfo.size = adderBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

    // 6. DelayrBlock
    for(int i = 0; i < countDelayBlock; i++){
        for(int j = 0; j < delayBlock[i]->numOfOutputs; j++){
            if(name == delayBlock[i]->lblOutData[j]->text()){
                if(delayBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of expressionBlock
                    blockInfo.io = 1; // 01for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 6;
                    blockInfo.status = 0;
                    blockInfo.size = delayBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

    // 7. AccumulatorBlock
    for(int i = 0; i < countAccumulatorBlock; i++){
        for(int j = 0; j < accumulatorBlock[i]->numOfOutputs; j++){
            if(name == accumulatorBlock[i]->lblOutData[j]->text()){
                if(accumulatorBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of expressionBlock
                    blockInfo.io = 1; // 01for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 7;
                    blockInfo.status = 0;
                    blockInfo.size = accumulatorBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

    // 8. ReadFileBlock
    for(int i = 0; i < countReadFileBlock; i++){
        for(int j = 0; j < readFileBlock[i]->numOfOutputs; j++){
            if(name == readFileBlock[i]->lblOutData[j]->text()){
                if(readFileBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of readfile block
                    blockInfo.io = 1; // 1 for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 8; // type
                    blockInfo.status = 0; // good
                    blockInfo.size = readFileBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

    // 9. GetMaxBlock
    for(int i = 0; i < countGetMaxBlock; i++){
        for(int j = 0; j < getMaxBlock[i]->numOfOutputs; j++){
            if(name == getMaxBlock[i]->lblOutData[j]->text()){
                if(getMaxBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of readfile block
                    blockInfo.io = 1; // 1 for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 9; // type
                    blockInfo.status = 0; // good
                    blockInfo.size = getMaxBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

    // 11. IfBlock
    for(int i = 0; i < countIfBlock; i++){
        for(int j = 0; j < ifBlock[i]->numOfOutputs; j++){
            if(name == ifBlock[i]->lblOutData[j]->text()){
                if(ifBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of expressionBlock
                    blockInfo.io = 1; // 01for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 11;
                    blockInfo.status = 0;
                    blockInfo.size = ifBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

    // 12. HistFromArrBlock
    for(int i = 0; i < countHistFromArrBlock; i++){
        for(int j = 0; j < histFromArrBlock[i]->numOfOutputs; j++){
            if(name == histFromArrBlock[i]->lblOutData[j]->text()){
                if(histFromArrBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of expressionBlock
                    blockInfo.io = 1; // 01for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 12;
                    blockInfo.status = 0;
                    blockInfo.size = histFromArrBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

    // 13. FillHistBlock
    for(int i = 0; i < countFillHistBlock; i++){
        for(int j = 0; j < fillHistBlock[i]->numOfOutputs; j++){
            if(name == fillHistBlock[i]->lblOutData[j]->text()){
                if(fillHistBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of expressionBlock
                    blockInfo.io = 1; // 01for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 13;
                    blockInfo.status = 0;
                    blockInfo.size = fillHistBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

    // 14. ReadMultiFileBlock
    for(int i = 0; i < countReadMultiFilesBlock; i++){
        for(int j = 0; j < readMultiFilesBlock[i]->numOfOutputs; j++){
            if(name == readMultiFilesBlock[i]->lblOutData[j]->text()){
                if(readMultiFilesBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of readMultifiles block
                    blockInfo.io = 1; // 1 for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 14; // type
                    blockInfo.status = 0; // good
                    blockInfo.size = readMultiFilesBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

    // 15. GenerateGausBlock
    for(int i = 0; i < countgenerateGausBlock; i++){
        for(int j = 0; j < generateGausBlock[i]->numOfOutputs; j++){
            if(name == generateGausBlock[i]->lblOutData[j]->text()){
                if(generateGausBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of generateGaus block
                    blockInfo.io = 1; // 1 for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 15; // type
                    blockInfo.status = 0; // good
                    blockInfo.size = generateGausBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

    // 16. GenerateXYBlock
    for(int i = 0; i < countgenerateXYBlock; i++){
        for(int j = 0; j < generateXYBlock[i]->numOfOutputs; j++){
            if(name == generateXYBlock[i]->lblOutData[j]->text()){
                if(generateXYBlock[i]->flagOut[j]){
                    blockInfo.id = i; // id of generateXY block
                    blockInfo.io = 1; // 1 for output
                    blockInfo.num = j; // num of input
                    blockInfo.type = 16; // type
                    blockInfo.status = 0; // good
                    blockInfo.size = generateXYBlock[i]->getSize(1, j);
                    return blockInfo;
                }
            }
        }
    }

}

void ManageBlocks::generateAllOutsOfIOBlocks(){
    // 2. Expression blocks
    for(int i = 0; i < countExpressionBlock; i++){
        if(expressionBlock[i]->flagIn[0] && !expressionBlock[i]->flagOut[0] && expressionBlock[i]->isBlockEnabled()){
            expressionBlock[i]->generateOutputs();
        }
    }

    // 4. DataSplit blocks
    for(int i = 0; i < countDataSplitBlock; i++){
        if(dataSplitBlock[i]->flagIn[0]  && !dataSplitBlock[i]->flagOut[0] && dataSplitBlock[i]->isBlockEnabled()){
            dataSplitBlock[i]->generateOutputs();
        }
    }

    // 6. Adder blocks
    for(int i = 0; i < countAdderBlock; i++){
        //for(int j = 0; j < adderBlock[i]->numOfOutputs; j++){}
        if(adderBlock[i]->flagIn[0] && adderBlock[i]->flagIn[1]  && !adderBlock[i]->flagOut[0] && adderBlock[i]->isBlockEnabled()){
            adderBlock[i]->generateOutputs();
        }
        //}
    }

    // 6. Delay blocks
    for(int i = 0; i < countDelayBlock; i++){
        //for(int j = 0; j < adderBlock[i]->numOfOutputs; j++){}
        if(delayBlock[i]->flagIn[0] && !delayBlock[i]->flagOut[0] && delayBlock[i]->isBlockEnabled()){
            delayBlock[i]->generateOutputs();
        }
        //}
    }

    // 7. Accumulator blocks
    for(int i = 0; i < countAccumulatorBlock; i++){
        //for(int j = 0; j < adderBlock[i]->numOfOutputs; j++){}
        if(accumulatorBlock[i]->flagIn[0] && !accumulatorBlock[i]->flagOut[0] && accumulatorBlock[i]->isBlockEnabled()){
            accumulatorBlock[i]->generateOutputs();
        }
        //}
    }

    // 9. GetMax blocks
    for(int i = 0; i < countGetMaxBlock; i++){
        //for(int j = 0; j < adderBlock[i]->numOfOutputs; j++){}
        if(getMaxBlock[i]->flagIn[0] && !getMaxBlock[i]->flagOut[0] && getMaxBlock[i]->isBlockEnabled()){
            getMaxBlock[i]->generateOutputs();
        }
        //}
    }

    // 11. IF blocks
    for(int i = 0; i < countIfBlock; i++){
        if(ifBlock[i]->flagIn[0] && !ifBlock[i]->flagOut[0] && ifBlock[i]->isBlockEnabled()){
            ifBlock[i]->generateOutputs();
        }
    }

    // 12. HistFromArr blocks
    for(int i = 0; i < countHistFromArrBlock; i++){
        if(histFromArrBlock[i]->flagIn[0] && !histFromArrBlock[i]->flagOut[0] && histFromArrBlock[i]->isBlockEnabled()){
            histFromArrBlock[i]->generateOutputs();
        }
    }

    // 13. FillHist blocks
    for(int i = 0; i < countFillHistBlock; i++){
        if(fillHistBlock[i]->flagIn[0] && !fillHistBlock[i]->flagOut[0] && fillHistBlock[i]->isBlockEnabled()){
            fillHistBlock[i]->generateOutputs();
        }
    }

    // 16. GenerateXY blocks
    for(int i = 0; i < countgenerateXYBlock; i++){
        if(generateXYBlock[i]->flagIn[0] && !generateXYBlock[i]->flagOut[0] && generateXYBlock[i]->isBlockEnabled()){
            generateXYBlock[i]->generateOutputs();
        }
    }
}


void ManageBlocks::drawGraphs(){
    for(int i = 0; i < countGraphs; i++){
        if(graphs[i]->flagIn[0] && graphs[i]->flagIn[1] && graphs[i]->isBlockEnabled())
            graphs[i]->draw();
    }
}

void ManageBlocks::resetOutputs(){
    for(int i = 0; i < countGraphs; i++){
        //if((!graphs[i]->flagIn[0] || !graphs[i]->flagIn[1]) && graphs[i]->isBlockEnabled())
        graphs[i]->resetGL();
    }
}


QGroupBox* ManageBlocks::getBlock(int type, int id){
    for(size_t i = 0; i < blockIO.size(); i++)
    {
        if(blockIO.at(i)->getType() == type && blockIO.at(i)->getId() == id)
        {
            return blockIO.at(i)->groupBox;
        }
    }
    if(type == 1){
        //return constArrayBlock[id]->groupBox;
        //return  blockIO.at(id)->groupBox;
    }
    else if(type == 2){
        return expressionBlock[id]->groupBox;
    }
    else if(type == 3){
        return graphs[id]->groupBox;
    }
    else if(type == 4){
       // return dataSplitBlock[id]->groupBox;
    }
    else if(type == 5){
        return adderBlock[id]->groupBox;
    }
    else if(type == 6){
        return delayBlock[id]->groupBox;
    }
    else if(type == 7){
        return accumulatorBlock[id]->groupBox;
    }
    else if(type == 8){
        return readFileBlock[id]->groupBox;
    }
    else if(type == 9){
        return getMaxBlock[id]->groupBox;
    }
    else if(type == 10){
        return lineDisplayBlock[id]->groupBox;
    }
    else if(type == 11){
        return ifBlock[id]->groupBox;
    }
    else if(type == 12){
        return histFromArrBlock[id]->groupBox;
    }
    else if(type == 13){
        return fillHistBlock[id]->groupBox;
    }
    else if(type == 14){
        return readMultiFilesBlock[id]->groupBox;
    }
    else if(type == 15){
        return generateGausBlock[id]->groupBox;
    }
    else if(type == 16){
        return generateXYBlock[id]->groupBox;
    }
    else if(type == 17){
        return generateMainBlock[id]->groupBox;
    }
    else if(type == 18){
        return deMuxBlock[id]->groupBox;
    }
    else if(type == 19){
        return localProcedureBlock[id]->groupBox;
    }
    else if(type == BlockItem::NetworkClient){
        return networkClientBlock[id]->groupBox;
    }
    else if(type == BlockItem::NetworkServer){
        return networkServerBlock[id]->groupBox;
    }
}

void ManageBlocks::setBlockEnable(int type, int id, bool flagEn){
    for(size_t i = 0; i < blockIO.size(); i++)
    {
        if(blockIO.at(i)->getType() == type && blockIO.at(i)->getId() == id)
        {
            blockIO.at(i)->setEnabled(flagEn);
            break;
        }
    }
    if(type == 1){
        //constArrayBlock[id]->setBlockEnabled(flagEn);
        //blockIO.at(id)->setEnabled(flagEn);
    }
    else if(type == 2){
        expressionBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 3){
        graphs[id]->setBlockEnabled(flagEn);
    }
    else if(type == 4){
        //dataSplitBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 5){
        adderBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 6){
        delayBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 7){
        accumulatorBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 8){
        readFileBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 9){
        getMaxBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 10){
        lineDisplayBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 11){
        ifBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 12){
        histFromArrBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 13){
        fillHistBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 14){
        readMultiFilesBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 15){
        generateGausBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 16){
        generateXYBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 17){
        generateMainBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 18){
        deMuxBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == 19){
        localProcedureBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == BlockItem::NetworkClient){
        networkClientBlock[id]->setBlockEnabled(flagEn);
    }
    else if(type == BlockItem::NetworkServer){
        networkServerBlock[id]->setBlockEnabled(flagEn);
    }
}

void ManageBlocks::stop()
{
    simulate->stop();
}
