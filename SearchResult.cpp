#include "SearchResult.h"
#include "TestingModule.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QTest>
#include <QReadWriteLock>
#include <QReadLocker>
#include <QWriteLocker>

#define RETURN_IF_INVALID(X) \
  if(target_.isNull()) \
    return X;


SearchResult::SearchResult(QObject *widget, TestingModule* app) :
    QObject(app)
  , target_(widget)
  , app_(app->getApp())
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

void SearchResult::click()
{
    RETURN_IF_INVALID()
    click(0, 0);
}

void SearchResult::hover(const int x, const int y)
{
    //sendMouseEvent(QEvent::MouseMove, x, y, Qt::NoButton);
    QHoverEvent* eve = new QHoverEvent( QEvent::HoverEnter, QPoint(x,y), QPoint(x,y));
    sendEvent(eve);
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

std::shared_ptr<SearchResult> SearchResult::Factory::fromObject(QObject* widget, TestingModule* module)
{
    std::shared_ptr<SearchResult> returnValue = nullptr;
    if(widget != nullptr) {
        QReadLocker lock(getLock());
        QMap<QString, std::shared_ptr<SearchResult::Factory>>* map = getMap();
        // Try to find factory
        const QMetaObject* meta = widget->metaObject();
        QString className = meta->className();
        while( className != "QObject" && returnValue == nullptr )
        {
            QMap<QString, std::shared_ptr<SearchResult::Factory>>::const_iterator factoryLocation = map->constFind(className);
            if(factoryLocation != map->constEnd()) {
                returnValue = (*factoryLocation)->newInstance( widget, module );
                break;
            }
            meta = meta->superClass();
            className = meta->className();
        }
    }
    if(returnValue == nullptr) {
        returnValue = std::make_shared<SearchResult>(widget, module);
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