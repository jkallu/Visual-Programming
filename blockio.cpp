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

    for(int i = 0; i < PACK_COUNT_MAX; i++)
    {
        listType.append(QString::fromStdString(getTypeString((enum Types)i)));
    }

    //connect(this, SIGNAL(dataChanged(char *)), this, SLOT(setData(char *)));
}

void BlockIO::init()
{

}

void BlockIO::generateCode(QString dir)
{

}

void BlockIO::addHeader(QString header)
{

}

QString BlockIO::getDir()
{
    return "";
}

void BlockIO::setData(char *data)
{
    if(data == nullptr)
    {
        return;
    }

    Types type = Types::PACK_COUNT_MAX;
    size_t size = 0;
    char *data_out = nullptr;

    QString strData = "";

    for(int j = -1; j < numOfInputs; j++)
    {
        getData(j, data, &type, &size, &data_out);

        if(size > 0)
        {
            strData.append("Type " + listType.at((int)type) + "\n");
            strData.append("Size " + QString::number(size) + "\n");

            switch(type)
            {
            case Types::Pack_func:
            {
                strData.append("FUNCTION NAME " + QString::fromStdString(data_out) + "\n\n");
                break;
            }
            case Types::Pack_Int:
            {
                int d = 0;
                for(size_t i = 0; i < size; i++)
                {
                    memcpy(&d, data_out + i * sizeof (d), sizeof (d));
                    strData.append("DATA_ " + QString::number(i) + " " + QString::number(d) + "\n");
                }
                strData.append("\n");
                break;
            }
            case Types::Pack_Float:
            {
                float d = 0;
                for(size_t i = 0; i < size; i++)
                {
                    memcpy(&d, data_out + i * sizeof (d), sizeof (d));
                    strData.append("DATA_ " + QString::number(i) + " " + QString::number(d) + "\n");
                }
                strData.append("\n");
                break;
            }
            case Types::Pack_Double:
            {
                double d = 0;
                for(size_t i = 0; i < size; i++)
                {
                    memcpy(&d, data_out + i * sizeof (d), sizeof (d));
                    strData.append("DATA_ " + QString::number(i) + " " + QString::number(d) + "\n");
                }
                strData.append("\n");
                break;
            }
            }
            /*QString strData;
        //teData->append("SIZE " + QString::number(size));
        //switch(type)
        //{
        if(type == Types::Pack_func)
        {
            teData->append("FUNCTION NAME " + QString::fromStdString(data_out));
            //break;
        }
        else if(type == Types::Pack_Float)
        {
            float d_f = 0;
            for(size_t k = 0; k < size; k++)
            {
                memcpy(&d_f, data + k * sizeof (d_f), sizeof (d_f));
                qDebug() << k << " " << d_f << endl;
                strData.append("DATA_ " + QString::number(k) + " " + QString::number(d_f) + "\n");
            }
            teData->append(strData);
            //break;
        }
        else if(type == Types::Pack_Int)
        {
            int d_i = 0;
            for(size_t k = 0; k < size; k++)
            {
                memcpy(&d_i, data + k * sizeof (d_i), sizeof (d_i));
                strData.append("DATA_ " + QString::number(k) + " " + QString::number(d_i) + "\n");
            }
            teData->append(strData);
            //break;
        }*/
            //default:
            //{

            //}
            //}
        }
        if(data_out != nullptr)
        {
            delete data_out;
            data_out = nullptr;
        }
    }
    teData->append(strData);

    /*if(data_out != nullptr)
        {
            delete data_out;
            data_out = nullptr;
        }*/
    //}

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
