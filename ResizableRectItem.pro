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
    resizablerectitemsettings.cpp

HEADERS  += mainwindow.h \
    resizablerectitem.h \
    resizablerectitemsettings.h \
    resizedirections.h

FORMS    += mainwindow.ui
