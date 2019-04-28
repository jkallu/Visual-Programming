#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(), parent)
{
    num_steps = 0;
    flag_x_y_created = false;
    count = 0;
    //cbIn = new QComboBox;
    //cbIn_2 = new QComboBox;


}

GLWidget::~GLWidget(){
    if(flag_x_y_created){
        delete[] x;
        delete[] y;
    }
}

QSize GLWidget::sizeHint() const{
    return QSize(200, 200);
}

void GLWidget::initializeGL(){
    qglClearColor((QColor(Qt::black)));
    this->paintGL();
}

void GLWidget::clearGL(){
    count = 0;
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //qglClearColor((QColor(Qt::white)));
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glFlush();
    //update();
    qDebug() << "cleared!";
    //qglClearColor((QColor(Qt::black)));

    paintGL();
}

void GLWidget::resizeGL(int width, int height){
    if (height == 0) { height = 1;
    }
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000); glViewport(0, 0, width, height);


}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    //if(count > 0)
    //{
        paint_graph();
    //}
    glFlush();
}

void GLWidget::paint_axis(float xmin, float xmax, float ymin, float ymax){
    qglClearColor((QColor(Qt::white)));
    // The following code displays the steps as points.
    glPointSize(5.0);
    glLineWidth(5);
    glColor3f(0.0, 0.0, 0.0);

    //if(num_steps > 0){
    // x axis
    glBegin(GL_LINES);
    glVertex3f(xmin, ymin, 0.);
    glVertex3f(xmax, ymin, 0.);

    // y axis
    glVertex3f(xmin, ymin, 0.);
    glVertex3f(xmin, ymax, 0.);
    glEnd();
    //}
}

void GLWidget::create_array(int cnt){
    count = cnt;
    x = new double[count];
    y = new double[count];

    flag_x_y_created = true;
}

void GLWidget::set_array_val(int index, double x_val, double y_val){
    x[index] = x_val;
    y[index] = y_val;
}

void GLWidget::paint_graph(){
    //glViewport(x_min, y_min, x_max - x_min, y_max - y_min);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(x_min - 0.1 * x_max , x_max +  0.1 * x_max, y_min -  0.1 * y_max, y_max +  0.1 * y_max, -1, 1) ;

    if(count > 0){
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_LINE_STRIP);


        for(int i = 0; i < count; i++){
            double x_p = x[i];// + (-1. - x_min / x_div);
            double y_p = y[i];// + (-1. - y_min / y_div);
            glVertex3f(x_p, y_p, 0.);
            //qDebug() << x_p << y_p;
        }

        glEnd();
    }

    paint_axis(x_min - 0.1 * x_max , x_max +  0.1 * x_max, y_min -  0.1 * y_max, y_max +  0.1 * y_max);
    glMatrixMode(GL_MODELVIEW);

}

void GLWidget::normalize_x_y(){
    x_max = -1.e300;
    y_max = -1.e300;
    x_min = 1.e300;
    y_min = 1.e300;
    for(int i = 0; i < count; i++){
        if(x[i] > x_max)
            x_max = x[i];
        if(y[i] > y_max)
            y_max = y[i];

        if(x[i] < x_min)
            x_min = x[i];
        if(y[i] < y_min)
            y_min = y[i];
    }

    x_div = qMax(qAbs(x_max), qAbs(x_min));
    y_div = qMax(qAbs(y_max), qAbs(y_min));

    if(x_div == 0){
        x_div = 1.;
    }
    if(y_div == 0){
        y_div = 1.;
    }

    //x_div *= 1.1;



    //for(int i = 0; i < count; i++){
    //x[i] /= x_div;
    //y[i] /= y_div;
    // }
}

