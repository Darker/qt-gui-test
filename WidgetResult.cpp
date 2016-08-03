#include "WidgetResult.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QTest>

#define RETURN_IF_INVALID(X) \
  if(target_.isNull()) \
    return X;


WidgetResult::WidgetResult(QWidget *widget, TestingModule* app) :
    QObject(app)
  , target_(widget)
  , app_(app->getApp())
{

}

void WidgetResult::setValue(const QVariant&)
{

}

void WidgetResult::click(const int x, const int y)
{
    RETURN_IF_INVALID()
    //QTest::mouseClick(target_, Qt::LeftButton, Qt::NoModifier, QPoint(x, y), 100);
    sendMouseEvent(QEvent::MouseButtonPress, x, y, Qt::LeftButton);
    sendMouseEvent(QEvent::MouseButtonRelease, x, y, Qt::LeftButton);
}

void WidgetResult::click()
{
    RETURN_IF_INVALID()
    const int x = target_->width()/2;
    const int y = target_->height()/2;
    click(x, y);
}

void WidgetResult::submit()
{

}

void WidgetResult::sendEvent(QEvent* e)
{
    RETURN_IF_INVALID()
    app_->postEvent(target_, e);
}

void WidgetResult::sendMouseEvent(QEvent::Type t, const int x, const int y, Qt::MouseButton button)
{
    QMouseEvent* eve = new QMouseEvent( t, QPoint(x,y),
        button,
        button,
        Qt::NoModifier);
    sendEvent(eve);
}
