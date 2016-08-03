#-------------------------------------------------
#
# Project created by QtCreator 2016-08-02T20:17:23
#fdsf
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGuiTest
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TestingModule.cpp \
    WidgetResult.cpp

HEADERS  += MainWindow.h \
    TestingModule.h \
    WidgetResult.h

FORMS    += MainWindow.ui
