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
    register_shit.cpp \
    server/TestServer.cpp \
    server/SmartSocket.cpp \
    results/DialogResult.cpp \
    results/FileDialogResult.cpp \
    results/SearchResult.cpp \
    results/WidgetResult.cpp \
    server/ANSI.cpp \
    results/QMenuResult.cpp \
    results/QActionResult.cpp \
    results/QTreeWidgetResult.cpp

HEADERS  += MainWindow.h \
    TestingModule.h \
    register_shit.h \
    server/TestServer.h \
    server/SmartSocket.h \
    results/DialogResult.h \
    results/FileDialogResult.h \
    results/SearchResult.h \
    results/WidgetResult.h \
    server/ANSI.h \
    results/QMenuResult.h \
    results/QActionResult.h \
    results/QTreeWidgetResult.h

FORMS    += MainWindow.ui
