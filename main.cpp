#include "MainWindow.h"
#include <QApplication>
#include "TestingModule.h"
#include "server/TestServer.h"
#include "register_shit.h"
#include "test_css.h"
int main(int argc, char *argv[])
{
    //run_test();
    if(should_run_test()) {
        QLIST_craziness();
        return 0;
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    TestingModule mod(&a);
    register_shit();
    mod.start();
    // Start threaded server
    TestServer pokus;
    QObject::connect(&pokus, &TestServer::command, &mod, &TestingModule::command);
    //QObject::connect(&pokus, SIGNAL(command(const QString&,const QString&)),
    //                 &mod, SLOT(command(const QString&,const QString&)), Qt::QueuedConnection);

    QObject::connect(&mod, SIGNAL(message(const QString)),
                     &pokus, SLOT(message(const QString)));
    //QObject::connect(&mod, &TestingModule::message, &pokus, &TestServer::message, Qt::QueuedConnection);


    //QObject::connect(&w, &MainWindow::clickWidgetRequest, &mod, &TestingModule::clickWidgetByName, Qt::QueuedConnection);
    return a.exec();
}
