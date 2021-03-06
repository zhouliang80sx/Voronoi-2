#-------------------------------------------------
#
# Project created by QtCreator 2016-12-04T14:18:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Voronoi
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    voronoi.cpp \
    vparabola.cpp \
    vmath.cpp \
    model.cpp

HEADERS  += mainwindow.h \
    voronoi.h \
    vedge.h \
    vevent.h \
    vpoint.h \
    vparabola.h \
    vmath.h \
    model.h \
    eventdata.h

FORMS    += mainwindow.ui
