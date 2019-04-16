#include "graph.h"

Graph::Graph(int i):
    BlockIO(i, 2, 0, BlockItem::BlockType::Graph)
{
    init();
}

void Graph::init()
{
    glWidget = new GLWidget();

    boxLayout->addWidget(glWidget, 3, 0, 1, 2);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Graph Block");
}

void Graph::generateCode(QString dir)
{

}


void Graph::draw(){
    int size = getSize(0, 0);
    glWidget->create_array(size);
    for(int i = 0; i < size; i++){
        glWidget->set_array_val(i, in[0][i], in[1][i]);
    }
    glWidget->normalize_x_y();
    //glWidget->repaint();
    glWidget->update();
}

void Graph::resetGL(){
    glWidget->clearGL();

}

void Graph::createInpuData(char *data)
{
    if(data == nullptr)
    {
        return;
    }
    qDebug() << "CREQATING GRAPH INS";
    //resetGL();
    //reset();
    Types type = Types::Pack_func;
    size_t size_0 = 0, size_1 = 0;
    char *data_0 = nullptr, *data_1 = nullptr;

    getData(0, data, &type, &size_0, &data_0);
    getData(1, data, &type, &size_1, &data_1);
    qDebug() << "SIZE FROM GRAPH " << size_0 << " " << size_1 << endl;
    qDebug() << "type FROM GRAPH " << type << endl;
    createIOArray(0, 0, size_0);
    createIOArray(0, 1, size_1);
    size_t add = 0;
    if(type == Types::Pack_Int)
    {
        for(size_t i = 0; i < size_0; i++)
        {
            int d;
            memcpy(&d, data_0 + add, sizeof (int));
            in[0][i] = d;
            flagIn[0] = true;
            add += sizeof (int);
        }
        add = 0;
        for(size_t i = 0; i < size_1; i++)
        {
            int d;
            memcpy(&d, data_1 + add, sizeof (int));
            in[1][i] = d;
            flagIn[1] = true;
            add += sizeof (int);
        }
    }
    else if(type == Types::Pack_Float)
    {
        for(size_t i = 0; i < size_0; i++)
        {
            float d;
            memcpy(&d, data_0 + add, sizeof (float));
            in[0][i] = d;
            flagIn[0] = true;
            add += sizeof (float);
        }
        add = 0;
        for(size_t i = 0; i < size_1; i++)
        {
            float d;
            memcpy(&d, data_1 + add, sizeof (float));
            in[1][i] = d;
            flagIn[1] = true;
            add += sizeof (float);
        }
    }
    else if(type == Types::Pack_Double)
    {
        for(size_t i = 0; i < size_0; i++)
        {
            double d;
            memcpy(&d, data_0 + add, sizeof (double));
            in[0][i] = d;
            flagIn[0] = true;
            add += sizeof (double);
        }
        add = 0;
        for(size_t i = 0; i < size_1; i++)
        {
            double d;
            memcpy(&d, data_1 + add, sizeof (double));
            in[1][i] = d;
            flagIn[1] = true;
            add += sizeof (double);
        }
    }
    draw();
}

