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

SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    circle.h \
    about.h

RC_FILE = okt.rc

RESOURCES += \
    okt.qrc


