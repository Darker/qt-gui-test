#include "WidgetResult.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
//#include <QTest>
#define RETURN_IF_INVALID(X) \
  if(target_.isNull()) \
    return X;


WidgetResult::WidgetResult(QWidget *widget, TestingModule* app) :
    SearchResult(widget, app)
  , targetWidget_(widget)
{

}
void WidgetResult::click(const int x, const int y)
{
    SearchResult::click(x, y);
}

SearchResultPtr WidgetResult::Factory::newInstance(QObject* o, TestingModule*t) const
{
    return std::make_shared<WidgetResult>(qobject_cast<QWidget*>(o), t);
}

QString WidgetResult::Factory::objectName() const
{
    return "QWidget";
}


QPoint WidgetResult::getMidpoint()
{
    return QPoint(targetWidget_->width()/2.0, targetWidget_->height()/2.0);
}


void WidgetResult::contextMenu(const int x, const int y)
{
    RETURN_IF_INVALID();
    targetWidget_->customContextMenuRequested(QPoint(x, y));
}
