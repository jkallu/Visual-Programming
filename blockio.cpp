#include "blockio.h"

BlockIO::BlockIO(int id_l, int numOfIn, int numOfOut, BlockItem::BlockType typ):
    Block(id_l)
{
    initBlock();
    setId(id_l);

    type = typ;

    numOfInputs = numOfIn;
    numOfOutputs = numOfOut;

    in = new double*[numOfInputs]; // create number of ins
    out = new double*[numOfOutputs]; // create number of outs

    for(int i = 0; i < numOfInputs; i++)
    {
        in[i] = nullptr;
    }
    for(int i = 0; i < numOfOutputs; i++)
    {
        out[i] = nullptr;
    }

    conToIONum = new int[numOfOutputs];
    conToTotIns = new int[numOfOutputs];

    flagIn = new bool[numOfInputs];
    flagOut = new bool[numOfOutputs];

    sizeIn = new int[numOfInputs];
    sizeOut = new int[numOfOutputs];

    lblIn = new QLabel*[numOfInputs];
    lblInData = new QLabel*[numOfInputs];

    lblOut = new QLabel*[numOfOutputs];
    lblOutData = new QLabel*[numOfOutputs];

    lblOutConTo = new QLabel*[numOfOutputs];
    lblOutConToBlock = new QLabel*[numOfOutputs];

    for(int i = 0; i < numOfInputs; i++){
        lblIn[i] = new QLabel("Input_" + QString::number(i));
        lblInData[i] = new QLabel("InputData_" + QString::number(i));
        boxLayout->addWidget(lblIn[i]);
        boxLayout->addWidget(lblInData[i]);
    }

    for(int i = 0; i < numOfOutputs; i++){
        lblOut[i] = new QLabel("Output_" + QString::number(i));
        lblOutData[i] = new QLabel("OutputData_" + QString::number(i));
        boxLayout->addWidget(lblOut[i]);
        boxLayout->addWidget(lblOutData[i]);

        lblOutConTo[i] = new QLabel("Out_" + QString::number(i) + "_ConTo");
        lblOutConToBlock[i] = new QLabel("OutConToBlock_" + QString::number(i));
        boxLayout->addWidget(lblOutConTo[i]);
        boxLayout->addWidget(lblOutConToBlock[i]);
    }

    lblData = new QLabel("Data");
    teData = new QTextEdit;
    teData->setReadOnly(true);
    teData->setText("Recieved data\n");

    boxLayout->addWidget(lblData);
    boxLayout->addWidget(teData);

    for(int i = 0; i < numOfInputs; i++){
        flagIn[i] = false;
    }

    for(int i = 0; i < numOfOutputs; i++){
        flagOut[i] = false;
    }

    //connect(this, SIGNAL(dataChanged(char *)), this, SLOT(setData(char *)));
}

void BlockIO::init()
{

}

void BlockIO::generateCode(QString dir)
{

}

void BlockIO::setData(char *data)
{
    /*
     * char *strTypes[Types::PACK_COUNT_MAX];
    strTypes[Types::Pack_Int] = "int";
    strTypes[Types::Pack_Float] = "float";
    strTypes[Types::Pack_Double] = "double";
    strTypes[Types::Pack_Char] = "char";
    */

    Types type = Types::Pack_func;
    size_t size = 0;
    char **data_out;


    data_out = new char*[numOfInputs];


    for(int i = 0; i < numOfInputs; i++)
    {
        getData(i, data, &type, &size, &data_out[i]);

        //teData->append("Type " + QString::fromStdString(strTypes[type]) + "\n");
        teData->append("Size " + QString::number(size) + "\n");
        //teData->append("Size " + QString::number(size) + "\n");
    }


}


BlockIO::~BlockIO(){

}

int BlockIO::getFinalNoIns()
{
    return numOfInputs;
}
int BlockIO::getFinalNoOuts()
{
    return numOfOutputs;
}

void BlockIO::setIOConts(int n_in, int n_out)
{
    numOfInputs = n_in;
    numOfOutputs = n_out;
}

std::vector <int> BlockIO::getIOCounts()
{
    std::vector <int> vec;
    vec.push_back(numOfInputs);
    vec.push_back(numOfOutputs);

    return vec;
}

void BlockIO::createIOArray(int io, int num, size_t size){
    // delete any previusly dynamica allocate memory
    //if(sizeof(in) / sizeof(double) > 0){
    //delete[] in;
    //}
    //if(sizeof(out) / sizeof(double) > 0){
    //delete[] out;
    //}
    //count = io;
    if(io == 0){
        in[num] = new double[size];
        flagIn[num] = true;
        sizeIn[num] = size;
    }
    else if(io == 1){
        out[num] = new double[size];
        flagOut[num] = true;
        sizeOut[num] = size;
    }
}

void BlockIO::reset(){
    for(int i = 0; i < numOfInputs; i++){
        flagIn[i] = false;
        if(in[i] != nullptr)
        {
            delete[] in[i];
            sizeIn[i] = 0;
        }
    }

    for(int i = 0; i < numOfOutputs; i++){
        flagOut[i] = false;
        if(out[i] != nullptr)
        {
            delete[] out[i];
            sizeOut[i] = 0;
        }
    }


}

int BlockIO::getSize(int io, int num){
    if(io == 0){
        if(num < numOfInputs){
            return sizeIn[num];
        }
    }
    else if(io == 1){
        if(num < numOfOutputs){
            return sizeOut[num];
        }
    }

    return 0;
}

bool BlockIO::isExecutedFull(){
    bool flagExecuted = true;
    for(int j = 0; j < numOfOutputs; j++){
        if(!flagOut[j])
            flagExecuted = false;
    }
    for(int j = 0; j < numOfInputs; j++){
        if(!flagIn[j])
            flagExecuted = false;
    }

    return flagExecuted;
}


BlockItem::BlockType BlockIO::getType()
{
    return  type;
}
