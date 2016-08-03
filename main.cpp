#include "MainWindow.h"
#include <QApplication>
#include "TestingModule.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    TestingModule mod(&a);
    mod.start();
    QObject::connect(&w, &MainWindow::clickWidgetRequest, &mod, &TestingModule::clickWidgetByName, Qt::QueuedConnection);
    return a.exec();
}
