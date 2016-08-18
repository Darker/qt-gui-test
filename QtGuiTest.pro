#-------------------------------------------------
#
# Project created by QtCreator 2016-08-02T20:17:23
#
#-------------------------------------------------

QT       += core gui testlib network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGuiTest
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TestingModule.cpp \
    WidgetResult.cpp \
    SearchResult.cpp \
    register_shit.cpp \
    server/TestServer.cpp \
    server/SmartSocket.cpp \
    results/DialogResult.cpp \
    results/FileDialogResult.cpp \
    results/SearchResult.cpp \
    results/WidgetResult.cpp

HEADERS  += MainWindow.h \
    TestingModule.h \
    WidgetResult.h \
    SearchResult.h \
    register_shit.h \
    server/TestServer.h \
    server/SmartSocket.h \
    results/DialogResult.h \
    results/FileDialogResult.h \
    results/SearchResult.h \
    results/WidgetResult.h

FORMS    += MainWindow.ui
