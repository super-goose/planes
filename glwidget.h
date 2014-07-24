#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include "objloader.h"

class GLWidget : public QGLWidget
{
public:
    struct vector{
        float x;
        float y;
        float z;
    };

    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    QTimer timer;

    float s; // scale for object (1/s is size)
    vector set_vector(objloader::point main, objloader::point pt1, objloader::point pt2);
    vector cross(vector v1, vector v2);

public:
    float zo; // offset for z coord (- is away from user)
    float yo;
    float xo;


};

#endif // GLWIDGET_H
