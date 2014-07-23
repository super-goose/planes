#-------------------------------------------------
#
# Project created by QtCreator 2014-07-22T23:00:29
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = planes
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    objloader.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    objloader.h \
    glwidget.h

FORMS    += mainwindow.ui
