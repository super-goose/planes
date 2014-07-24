#include "glwidget.h"
#include "objloader.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);

// scale and offset is set here
    s = 2;   // scale for object   (1/s is size)
    zo = -1; // offset for z coord (- is away from user)
    yo = 0;
    xo = 0;

}

void GLWidget::initializeGL(){
// background color (sky-ish blue is (.5, .5, .9, 1)
    glClearColor(.5, .5, .9, 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

}

// the rendering happens here
void GLWidget::paintGL(){


    objloader a ("plane.obj");
    objloader::triangle * tcurrent = a.list;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotatef(0.4, .5, .5, .5);

    glColor3f(1,0,0);

//normals need to be calculated


    while(tcurrent->next != NULL)
    {
        glColor3f(.4, .4, .4);
        glBegin(GL_TRIANGLES);
            glVertex3f(tcurrent->A.x/s + xo, tcurrent->A.y/s + yo, tcurrent->A.z/s + zo);
            glVertex3f(tcurrent->B.x/s + xo, tcurrent->B.y/s + yo, tcurrent->B.z/s + zo);
            glVertex3f(tcurrent->C.x/s + xo, tcurrent->C.y/s + yo, tcurrent->C.z/s + zo);
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
