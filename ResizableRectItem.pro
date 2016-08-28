#-------------------------------------------------
#
# Project created by QtCreator 2016-07-28T08:46:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ResizableRectItem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    resizablerectitem.cpp \
    pyscripting.cpp

HEADERS  += mainwindow.h \
    resizablerectitem.h \
    pyscripting.h

FORMS    += mainwindow.ui

INCLUDEPATH += "/usr/include/python2.7"
LIBS += -lpython2.7
