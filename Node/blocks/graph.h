#ifndef GRAPH_H
#define GRAPH_H
#include "blockio.h"
#include "glwidget.h"

class GLWidget;

class BlockIO;

class Graph : virtual public BlockIO
{
public:
    Graph(int i);

    void generateCode(QString dir) override;
    void init() override;
    void setData(char *data) override;

    GLWidget *glWidget;

    void draw();
    void resetGL();
    static int getNumInputs(){return  2;}
    static int getNumOutputs(){return 0;}

    QLabel *lblAxis0;
    QComboBox *cbAxis0;

    QLabel *lblAxis1;
    QComboBox *cbAxis1;
};

#endif // GRAPH_H
