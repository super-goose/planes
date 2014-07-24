#include "glwidget.h"
#include "objloader.h"
#include <cmath>



GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);

// scale and offset is set here
    s = 4; // scale for object (1/s is size)
    zo = 0; // offset for z coord (- is away from user)
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

    GLWidget::vector norm;
    objloader a ("untitled.obj");
    objloader::triangle * tcurrent = a.list;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotatef(0.4, .5, .5, .5);

//    glColor3f(1,0,0);

//normals need to be calculated



    while(tcurrent->next != NULL)
    {
        norm = set_vector(tcurrent->A, tcurrent->B, tcurrent->C);

        glColor3f(.4, .4, .4);
        glBegin(GL_TRIANGLES);
        glNormal3d(norm.x, norm.y, norm.z);
            glVertex3f(tcurrent->A.x/s + xo, tcurrent->A.y/s + yo, tcurrent->A.z/s + zo);
            glVertex3f(tcurrent->B.x/s + xo, tcurrent->B.y/s + yo, tcurrent->B.z/s + zo);
            glVertex3f(tcurrent->C.x/s + xo, tcurrent->C.y/s + yo, tcurrent->C.z/s + zo);
        glEnd();

        tcurrent = tcurrent->next;
    }


   /*   SUPER HEROS   */
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
}

// this returns the normal vector for the triangle defined by the three points passed to it
GLWidget::vector GLWidget::set_vector(objloader::point main, objloader::point pt1, objloader::point pt2){
    GLWidget::vector A;
    GLWidget::vector B;
    GLWidget::vector C;
    float mag;

    A.x = pt1.x - main.x;
    A.y = pt1.y - main.y;
    A.z = pt1.z - main.z;

    B.x = pt2.x - main.x;
    B.y = pt2.y - main.y;
    B.z = pt2.z - main.z;

    C = cross(A, B);

    // not needed... really?
    mag = sqrt((C.x*C.x) + (C.y*C.y) + (C.z*C.z));
    C.x /= mag;
    C.y /= mag;
    C.z /= mag;

    return C;
}

GLWidget::vector GLWidget::cross(GLWidget::vector A, GLWidget::vector B){
    GLWidget::vector C;

    C.x = (A.z*B.y) - (A.y*B.z);
    C.y = (A.x*B.z) - (A.z*B.x);
    C.z = (A.y*B.x) - (A.x*B.y);

/*
    C.x = (A.y*B.z) - (A.z*B.y);
    C.y = (A.z*B.x) - (A.x*B.z);
    C.z = (A.x*B.y) - (A.y*B.x);
*/
    return C;
}

/*
Begin Function CalculateSurfaceNormal (Input Triangle) Returns Vector

        Set Vector U to (Triangle.p2 minus Triangle.p1)
        Set Vector V to (Triangle.p3 minus Triangle.p1)

        Set Normal.x to (multiply U.y by V.z) minus (multiply U.z by V.y)
        Set Normal.y to (multiply U.z by V.x) minus (multiply U.x by V.z)
        Set Normal.z to (multiply U.x by V.y) minus (multiply U.y by V.x)

        Returning Normal

End Function
*/

