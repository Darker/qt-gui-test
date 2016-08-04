#include "TestingModule.h"
#include "WidgetResult.h"
#include <QLabel>
#include <QAbstractButton>
#include <QMenu>


TestingModule::TestingModule(QApplication* app) :
    QObject(app),
    app_(app)
{

}

QWidget* TestingModule::byName(const QString& name)
{
    QWidget* ret = nullptr;
    for (auto top : app_->topLevelWidgets()) {
       ret = top->findChild<QWidget*>(name);
       if( ret!=nullptr )
           break;
    }
    return ret;
}

QWidget* TestingModule::byText(const QString& text)
{
    QWidget* ret = nullptr;
    for(QWidget* widget: QApplication::allWidgets()) {
       if(widget->accessibleName().indexOf(text)!=-1 ||
          widget->accessibleDescription().indexOf(text)!=-1) {
           ret = widget;
       }
       if(QLabel* label = qobject_cast<QLabel *>(widget)) {
           if(label->text().indexOf(text) != -1)
               ret = widget;
       }
       else if(QAbstractButton* button = qobject_cast<QAbstractButton *>(widget))
       {
           if(button->text().indexOf(text) != -1)
               ret = widget;
       }
       else if(QMenu* menu = qobject_cast<QMenu*>(widget))
       {
           if(menu->title().indexOf(text) != -1)
               ret = widget;
       }
       if(ret!=nullptr)
           break;
    }
    return ret;
}

TestingModule::~TestingModule()
{

}

void TestingModule::start()
{
    moveToThread(app_->thread());
    //connect(&workerThread, &QThread::finished(), worker, &QThread::deleteLater());
    //connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
    //QThread::start(priority);
}

void TestingModule::clickWidgetByName(const QString& name)
{
    QWidget* w = byName(name);
    if(w == nullptr)
        w = byText(name);
    WidgetResult* res = new WidgetResult(w, this);
    //sleep(1);
    res->click();
}
