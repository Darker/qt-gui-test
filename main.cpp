#include "MainWindow.h"
#include <QApplication>
#include "TestingModule.h"
#include "server/TestServer.h"
#include "register_shit.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    TestingModule mod(&a);
    register_shit();
    mod.start();
    // Start threaded server
    TestServer pokus;
    QObject::connect(&pokus, &TestServer::command, &mod, &TestingModule::command, Qt::QueuedConnection);


    //QObject::connect(&w, &MainWindow::clickWidgetRequest, &mod, &TestingModule::clickWidgetByName, Qt::QueuedConnection);
    return a.exec();
}
