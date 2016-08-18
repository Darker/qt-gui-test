#include "WidgetResult.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QTest>
#define RETURN_IF_INVALID(X) \
  if(target_.isNull()) \
    return X;


WidgetResult::WidgetResult(QWidget *widget, TestingModule* app) :
    SearchResult(widget, app)
  , targetWidget_(widget)
{

}
void WidgetResult::click()
{
    RETURN_IF_INVALID()
    const int x = targetWidget_->width()/2;
    const int y = targetWidget_->height()/2;
    SearchResult::click(x, y);
}

void WidgetResult::click(const int x, const int y)
{
    RETURN_IF_INVALID();
    QTest::mouseClick(targetWidget_, Qt::LeftButton, Qt::NoModifier, QPoint(x, y), 100);
}

SearchResultPtr WidgetResult::Factory::newInstance(QObject* o, TestingModule*t) const
{
    return std::make_shared<WidgetResult>(qobject_cast<QWidget*>(o), t);
}

QString WidgetResult::Factory::objectName() const
{
    return "QWidget";
}
