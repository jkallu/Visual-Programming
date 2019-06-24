#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMatrix4x4>
#include <QtGlobal>
#include <QLineEdit>
#include <QBoxLayout>
#include <QGroupBox>
#include <QComboBox>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();
    QSize sizeHint() const;

    void paint_axis(float xmin, float xmax, float ymin, float ymax);
    void paint_graph();
    void create_array(int cnt);
    void set_array_val(int index, double x_val, double y_val);
    void normalize_x_y();
    void clearGL();

    //QComboBox *cbIn;
    //QComboBox *cbIn_2;
    //QBoxLayout *boxLayout;
    //QGroupBox *groupBox;

    //void setValues(int *st, float * val);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    QMatrix4x4 pMatrix;
    int num_steps;
    float *step_vals;
    double *x, *y;
    int count;
    bool flag_x_y_created;
    double x_max, y_max, x_min, y_min;
    double x_div, y_div;

};

#endif // GLWIDGET_H
