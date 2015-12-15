#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T17:35:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OktTest
TEMPLATE = app

FORMS += about.ui

DESTDIR = ../out

SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp \
    oktgraphicview.cpp #\
    #oktrectangle.cpp \
    #okttriangle.cpp \
    #oktcircle.cpp

HEADERS  += mainwindow.h \
    #circle.h \
    about.h \
    oktgraphicview.h #\
    #oktrectangle.h \
    #okttriangle.h \
    ibasefigure.h

RC_FILE = okt.rc

RESOURCES += \
    okt.qrc


