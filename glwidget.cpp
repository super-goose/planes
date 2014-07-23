#include "glwidget.h"
#include "objloader.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL(){
// background color
    glClearColor(1, 1, 1, 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

}

// the rendering happens here
void GLWidget::paintGL(){

    objloader a ("torus.obj");
    objloader::triangle * tcurrent = a.list;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotatef(0.4, .5, .5, .5);

    glColor3f(1,0,0);

    while(tcurrent->next != NULL)
    {
        glColor3f(.4, .4, 0);
        glBegin(GL_TRIANGLES);
            glVertex3f(tcurrent->A.x, tcurrent->A.y, tcurrent->A.z);
            glVertex3f(tcurrent->B.x, tcurrent->B.y, tcurrent->B.z);
            glVertex3f(tcurrent->C.x, tcurrent->C.y, tcurrent->C.z);
        glEnd();

        tcurrent = tcurrent->next;
    }

}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
}
