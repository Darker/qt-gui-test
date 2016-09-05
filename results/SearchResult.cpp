#include "SearchResult.h"
#include "../TestingModule.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
//#include <QTest>
#include <QReadWriteLock>
#include <QReadLocker>
#include <QWriteLocker>
#include <QApplication>

#define RETURN_IF_INVALID(X) \
  if(target_.isNull()) \
    return X;


SearchResult::SearchResult(QObject *widget, TestingModule* app) :
    QObject(nullptr/*app!=nullptr?(QObject*)app:(QObject*)qApp*/)
  , target_(widget)
  , app_(app!=nullptr?app->getApp():qApp)
{

}

SearchResult::~SearchResult()
{

}

void SearchResult::setValue(const QVariant&)
{

}

void SearchResult::click(const int x, const int y)
{
    RETURN_IF_INVALID();
    //QTest::mouseClick(target_, Qt::LeftButton, Qt::NoModifier, QPoint(x, y), 100);
    //hover(x, y);
    sendMouseEvent(QEvent::MouseButtonPress, x, y, Qt::LeftButton);
    sendMouseEvent(QEvent::MouseButtonRelease, x, y, Qt::LeftButton);
}

void SearchResult::click(const QPoint&p)
{
    click(p.x(), p.y());
}

void SearchResult::click()
{
    RETURN_IF_INVALID()
    click(getMidpoint());
}

void SearchResult::hover(const int x, const int y)
{
    //sendMouseEvent(QEvent::MouseMove, x, y, Qt::NoButton);
    QHoverEvent* eve = new QHoverEvent( QEvent::HoverEnter, QPoint(x,y), QPoint(x,y));
    sendEvent(eve);
}



void SearchResult::contextMenu(const int, const int)
{}

QPoint SearchResult::getMidpoint()
{
    return QPoint(0,0);
}

void SearchResult::submit()
{

}

QString SearchResult::getGUIText()
{
    QVariant text;
    const char* names[] = {"text","title","description", "windowTitle"};
    const short l = sizeof(names) / sizeof( *names );
    for(short i=0; i<l; i++) {
        text = target_->property(names[i]);
        if(text.canConvert<QString>()) {
            return text.toString();
        }
    }
    return QString();
}

void SearchResult::doubleClickItem(const QString&) {}

void SearchResult::selectItems(const QStringList&) {}


void SearchResult::sendEvent(QEvent* e)
{
    RETURN_IF_INVALID()
    app_->postEvent(target_, e);
}

void SearchResult::sendMouseEvent(QEvent::Type t, const int x, const int y, Qt::MouseButton button)
{
    QMouseEvent* eve = new QMouseEvent( t, QPoint(x,y),
        button,
        button,
        Qt::NoModifier);
    sendEvent(eve);
}
std::shared_ptr<SearchResult::Factory> SearchResult::Factory::qobjectFactory = nullptr;
std::shared_ptr<SearchResult> SearchResult::Factory::fromObject(QObject* widget, TestingModule* module, bool ignoreUnimplemented)
{
    std::shared_ptr<SearchResult> returnValue = nullptr;
    std::shared_ptr<SearchResult::Factory> constructor(nullptr);

    // Access the class meta info
    const QMetaObject* meta = widget->metaObject();

    if(widget != nullptr) {
        QString className = meta->className();
        // First try to find constructor in cache, it's faster
        QMap<QString, std::shared_ptr<SearchResult::Factory>>* cache = getCache();
        const auto it = cache->constFind(className);
        if( it != cache->constEnd()) {
            constructor = *it;
        }
        // Resolve ctor if not cached
        if(constructor == nullptr) {
            QReadLocker lock(getLock());
            QMap<QString, std::shared_ptr<SearchResult::Factory>>* map = getMap();

            while( className != "QObject" && returnValue == nullptr )
            {
                QMap<QString, std::shared_ptr<SearchResult::Factory>>::const_iterator factoryLocation = map->constFind(className);
                if(factoryLocation != map->constEnd()) {
                    constructor = *factoryLocation;
                    cache->insert(className, constructor);
                    break;
                }
                meta = meta->superClass();
                className = meta->className();
            }
        }
    }
    if(constructor != nullptr) {
        returnValue = constructor->newInstance( widget, module );
    }
    else {
        if(!ignoreUnimplemented)
            returnValue = std::make_shared<SearchResult>(widget, module);
        QMap<QString, std::shared_ptr<SearchResult::Factory>>* cache = getCache();
        QString className = meta->className();
        if(qobjectFactory == nullptr) {
            qobjectFactory = std::shared_ptr<SearchResult::Factory>(new SearchResult::QObjectFactory);
        }
        cache->insert(className, qobjectFactory);
    }
    return returnValue;
}

void SearchResult::Factory::registerConstructor(const std::shared_ptr<SearchResult::Factory> factory)
{
    QWriteLocker lock(getLock());
    QMap<QString, std::shared_ptr<SearchResult::Factory>>* map = getMap();

    map->insert(factory->objectName(), factory);
}

QMap<QString, std::shared_ptr<SearchResult::Factory>>* SearchResult::Factory::getMap()
{
    static QMap<QString, std::shared_ptr<SearchResult::Factory>> map;
    return &map;
}

QReadWriteLock* SearchResult::Factory::getLock()
{
    static QReadWriteLock lock;
    return &lock;
}

QMap<QString, std::shared_ptr<SearchResult::Factory> >*SearchResult::Factory::getCache()
{
    static QMap<QString, std::shared_ptr<SearchResult::Factory>> map;
    return &map;
}

SearchResult::QObjectFactory* SearchResult::QObjectFactory::instance()
{
    static SearchResult::QObjectFactory factory;
    return &factory;
}
