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
                //const QString childClassName =  chev->child()->metaObject()->className();
                //const QString parentClassName = chev->parent()->metaObject()->className();
                //qDebug()<<"Add"
                //        <<childClassName
                //        <<"to"
                //        <<parentClassName;
                // Check out events
                for(int i=0,l=requests.length(); i<l; i++) {
                //for(WaitRequestPtr req: requests) {
                    WaitRequestPtr req(requests[i]);
                    if(req->validate(chev->child(), this)) {
                        emit message(req->ID);
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
#include "selectors/CSSChainedSelector.h"
#include "results/SearchResultGroup.h"
void TestingModule::command(const QString& command, const QString& paramstr, const QString& transactionId)
{
    QStringList params = paramstr.split("::");
    if(params.length()==0)
        return;
    SearchResultPtr res = nullptr;
    QObjectList results = QObjectList();
    const QString selectorStr = params[0];
    bool findOneOnly = false;
    // Some commands are known to operate over single item
    // for those, selector only searches for first item to save CPU
    if(command == "wait" || command=="coords" || command=="gettext")
        findOneOnly = true;
    SelectorPtr selector(new CSSChainedSelector);
    try {
        selector->parse(selectorStr);
        selector = selector->optimize(selector);
    }
    catch(const std::runtime_error& e) {
        emit message(QString("ERROR when parsing selector: %1").arg(e.what()));
        return;
    }

    Q_FOREACH(QWidget* top, app_->topLevelWidgets()) {
        //QObject* parent = top->parent();
        selector->find(top, findOneOnly, results);
        if(findOneOnly && results.size()>0)
            break;
    }
    if(results.length()>1)
        res = SearchResultPtr(new SearchResultGroup(results, this));
    else if (results.length()>0)
        res = SearchResult::Factory::fromObject(results[0], this);
    //sleep(1);
    if(res !=nullptr) {
        if( command == "click" )
            res->click();
        if( command == "ctx" ) {
            if( params.size()>2 ) {
                res->contextMenu(params[1].toInt(),params[2].toInt());
            }
            else {
                res->contextMenu();
            }
        }
        else if (command=="submit")
            res->submit();
        else if (command=="value" && params.length()>=2) {
            res->setValue(params[1]);
        }
        else if (command=="dblclickitem" && params.length()>=2) {
            res->doubleClickItem(params[1]);
        }
        else if (command=="selectitems" && params.length()>=2) {
            QString delimiter = ",";
            const QString targets(params[1]);
            // If two params given, then delimiter is second
            if(params.length()>=3) {
                delimiter = params[2];
            }
            res->selectItems(targets.split(delimiter));
        }
        else if (command=="select" && params.length()>=2) {
            res->selectItems(params.mid(2));
        }
        else if(command=="coords") {
            const QPoint loc(res->getMidpoint());
            emit message(QString("[%1,%2]").arg(loc.x()).arg(loc.y()), transactionId);
        }
        else if(command=="gettext") {
            emit message(res->getGUIText(), transactionId);
        }
    }
    if (command=="wait") {
        if(res == nullptr) {
            WaitRequestPtr req(new WaitRequestCSS(selector, transactionId));
            requests.push_back(req);
        }
        else {
            emit message("", transactionId);
        }
    }
    else if(command=="count") {
        //emit message(QString("Element %1 occurs %2 times.").arg(selectorStr).arg(results.size()), transactionId);
        emit message(QString("%1").arg(results.size()), transactionId);
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

