#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    QTimer timer;

private:
    float s;  // scale for object   (1/s is size)
public:
    float zo; // offset for z coord (- is away from user)
    float yo;
    float xo;

};

#endif // GLWIDGET_H
