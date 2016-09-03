#-------------------------------------------------
#
# Project created by QtCreator 2016-08-02T20:17:23
#
#-------------------------------------------------

QT       += core gui testlib network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGuiTest
TEMPLATE = app
CONFIG += c++11

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
    TestingEvent.cpp \
    results/QAbstractItemViewResult.cpp \
    AddChildEventFilter.cpp \
    events/ChildEvent.cpp \
    events/WaitRequest.cpp \
    events/WaitRequestGUIText.cpp \
    selectors/Selector.cpp \
    Message.cpp \
    selectors/CssSelector.cpp \
    selectors/Validator.cpp \
    selectors/ValidatorName.cpp \
    selectors/ValidatorClassName.cpp \
    test_css.cpp \
    selectors/ValidatorGUIText.cpp \
    results/SearchResultGroup.cpp \
    results/QLineEditResult.cpp \
    events/WaitRequestCSS.cpp \
    selectors/CSSChainedSelector.cpp

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
    TestingEvent.h \
    results/QAbstractItemViewResult.h \
    AddChildEventFilter.h \
    events/ChildEvent.h \
    events/WaitRequest.h \
    events/WaitRequestGUIText.h \
    selectors/Selector.h \
    Message.h \
    selectors/CssSelector.h \
    selectors/Validator.h \
    selectors/ValidatorName.h \
    selectors/ValidatorClassName.h \
    test_css.h \
    selectors/ValidatorGUIText.h \
    results/SearchResultGroup.h \
    results/QLineEditResult.h \
    events/WaitRequestCSS.h \
    selectors/CSSChainedSelector.h

FORMS    += MainWindow.ui
