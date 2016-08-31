#include "TestingModule.h"
#include "results/SearchResult.h"
#include "AddChildEventFilter.h"
#include "events/ChildEvent.h"
#include "events/WaitRequestCSS.h"
#include <QDebug>


TestingModule::TestingModule(QApplication* app) :
    QObject(app),
    app_(app)
{

}

TestingModule::TestingModule() :
    QObject(qApp),
    app_(qApp)
{

}

QWidget* TestingModule::byName(const QString& name)
{
    QWidget* ret = nullptr;
    Q_FOREACH(auto top, app_->topLevelWidgets()) {
       ret = top->findChild<QWidget*>(name);
       if( ret!=nullptr )
           break;
    }
    
    return ret;
}

SearchResultPtr TestingModule::byText(const QString& text)
{
    SearchResultPtr ret = nullptr;
    Q_FOREACH(QWidget* top, app_->topLevelWidgets()) {
       ret = byText(top, text);
       if(ret != nullptr)
           return ret;
    }
    /*for(QWidget* widget: QApplication::allWidgets()) {
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
    }*/
    return ret;
}

TestingModule::~TestingModule()
{

}

bool TestingModule::event(QEvent*e)
{
    if(e->type() == QEvent::User) {
        if(ChildEvent* chev = dynamic_cast<ChildEvent*>(e)) {
            if(chev->mode == ChildEvent::ADD) {
                if(!chev->valid())
                    return true;
                const QString childClassName =  chev->child()->metaObject()->className();
                const QString parentClassName = chev->parent()->metaObject()->className();
                qDebug()<<"Add"
                        <<childClassName
                        <<"to"
                        <<parentClassName;
                // Check out events
                for(int i=0,l=requests.length(); i<l; i++) {
                //for(WaitRequestPtr req: requests) {
                    WaitRequestPtr req(requests[i]);
                    if(req->validate(chev->child(), this)) {
                        emit message(QString(QString::number(req->ID)));
                        requests.removeAt(i);
                        i--;l--;
                    }
                }
            }
            return true;
        }
    }
    return false;
}

void TestingModule::start()
{
    moveToThread(app_->thread());
    //connect(&workerThread, &QThread::finished(), worker, &QThread::deleteLater());
    //connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
    //QThread::start(priority);
}
#include "selectors/Selector.h"
#include "results/SearchResultGroup.h"
void TestingModule::command(const QString& name, const QString& paramstr)
{
    QStringList params = paramstr.split("::");
    if(params.length()==0)
        return;
    SearchResultPtr res = nullptr;
    QObjectList results = QObjectList();
    const QString selectorStr = params[0];
    SelectorPtr selector(nullptr);
    try {
        selector = Selector::parseString(selectorStr);
    }
    catch(const std::runtime_error& e) {
        emit message(QString("ERROR when parsing selector: %1").arg(e.what()));
        return;
    }

    Q_FOREACH(QWidget* top, app_->topLevelWidgets()) {
        //QObject* parent = top->parent();
        selector->find(top, false, results);
    }
    if(results.length()>1)
        res = SearchResultPtr(new SearchResultGroup(results, this));
    else if (results.length()>0)
        res = SearchResult::Factory::fromObject(results[0], this);
    //sleep(1);
    if(res !=nullptr) {
        if( name == "click" )
            res->click();
        else if (name=="submit")
            res->submit();
        else if (name=="value" && params.length()>=2) {
            res->setValue(params[1]);
        }
        else if (name=="dblclickitem" && params.length()>=2) {
            res->doubleClickItem(params[1]);
        }
        else if (name=="select" && params.length()>=2) {
            res->selectItems(params.mid(2));
        }
    }
    if (name=="wait" && params.length()>=2) {
        if(res == nullptr) {
            WaitRequestPtr req(new WaitRequestCSS(selector, params[1].toInt()));
            requests.push_back(req);
        }
        else {
            emit message(params[1]);
        }
    }
}

void TestingModule::startListening()
{
    installEventFilters();
}

SearchResultPtr TestingModule::byText(QObject* parentObj, const QString& text)
{
    Q_FOREACH(QObject* object, parentObj->children()) {
        SearchResultPtr tmp = SearchResult::Factory::fromObject(object, this, true);
        if(tmp == nullptr)
            continue;
        //const QString otext = tmp->getGUIText();
        //const QString oname = object->objectName();

        if(tmp->getGUIText().indexOf(text) != -1)
            return tmp;
        tmp = byText(object, text);
        if(tmp!=nullptr)
            return tmp;
    }
    return nullptr;
}


void TestingModule::installEventFilters()
{
    app_->installEventFilter(new AddChildEventFilter(this, app_));
    /*for(QWidget* widget: QApplication::allWidgets()) {
        widget->installEventFilter(new AddChildEventFilter(this, widget));
    }*/
}

