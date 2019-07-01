#include "gnuplotblock.h"

GnuplotBlock::GnuplotBlock(int i):
    BlockIO(i, 2, 0, BlockItem::BlockType::Gnuplot)
{
    init();
}

void GnuplotBlock::init()
{
    widget = new QtGnuplotWidget;
    instance = new QtGnuplotInstance;


    boxLayout->addWidget(widget, 4, 0, 1, 2);
    lblData->setVisible(false);
    teData->setVisible(false);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Gnuplot Block");
}

void GnuplotBlock::generateCode(QString dir)
{

}

void GnuplotBlock::setData(char *data)
{
    if(data == nullptr)
    {
        return;
    }
    qDebug() << "CREQATING GNUPLOT INS";

    //resetGL();
    //reset();
    Types type = Types::PACK_COUNT_MAX;
    size_t size_0 = 0, size_1 = 0;
    char *data_0 = nullptr, *data_1 = nullptr;

    getData(0, data, &type, &size_0, &data_0);
    getData(1, data, &type, &size_1, &data_1);
    qDebug() << "SIZE FROM GNUPLOT " << size_0 << " " << size_1 << endl;
    qDebug() << "type FROM GNUPLOT " << type << endl;
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
            float d = 0;
            memcpy(&d, data_0 + i * sizeof (d), sizeof (d));
            in[0][i] = d;
            //qDebug() << i << " " << d << endl;
            flagIn[0] = true;
            add += sizeof (d);
        }
        add = 0;
        for(size_t i = 0; i < size_1; i++)
        {
            float d = 0;
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

    QVector<QPointF> points;
    for(size_t i = 0; i < size_0; i++)
    {
        points.push_back(QPointF(in[0][i], in[1][i]));
    }

    draw(&points);
}

void GnuplotBlock::draw(QVector<QPointF> *points)
{
    instance->setWidget(widget);
    //*instance << "plot x w l lt 3\n";
    *instance << *points;
    widget->show();
}
