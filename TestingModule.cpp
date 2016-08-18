#include "TestingModule.h"
#include "results/SearchResult.h"


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

SearchResultPtr TestingModule::byText(const QString& text)
{
    SearchResultPtr ret = nullptr;
    for(QWidget* widget: QApplication::allWidgets()) {
       SearchResultPtr tmp = SearchResult::Factory::fromObject(widget, this);
       if(tmp->getGUIText().indexOf(text) != -1) {
           ret = tmp;
           break;
       }
       // search widget's children who are not QWidgets themselves
       const QObjectList& childlist = widget->children();
       for( int i=0,l=childlist.size(); i<l; i++ ) {
           const QObject* entry = childlist[i];
           if(!entry->isWidgetType()) {
               SearchResultPtr tmp = SearchResult::Factory::fromObject(widget, this);
               if(tmp->getGUIText().indexOf(text) != -1) {
                   ret = tmp;
                   break;
               }
           }
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

void TestingModule::command(const QString& name, const QString& paramstr)
{
    QStringList params = paramstr.split("::");
    if(params.length()==0)
        return;
    const QString selector = params[0];
    SearchResultPtr res = nullptr;
    {
        QWidget* w = byName(selector);
        if(w != nullptr) {
            res = SearchResult::Factory::fromObject(w, this);
        }
    }
    if(res == nullptr)
        res = byText(selector);
    //sleep(1);
    if(res !=nullptr) {
        if( name == "click" )
            res->click();
        else if (name=="submit")
            res->submit();
        else if (name=="value" && params.length()>=2) {
            res->setValue(params[1]);
        }
    }
}
