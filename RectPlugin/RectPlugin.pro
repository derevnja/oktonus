QT       += core gui widgets

TARGET = RectPlugin
TEMPLATE = lib
CONFIG += plugin
INCLUDEPATH    += ../

DESTDIR = ../../out/plugins

SOURCES += \
    rectplugin.cpp

HEADERS += \
    rectplugin.h
DISTFILES +=

unix {
    target.path = /usr/lib
    INSTALLS += target
}
