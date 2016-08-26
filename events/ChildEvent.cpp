#include "ChildEvent.h"
#include <QWidget>

ChildEvent::ChildEvent(QObject* parent, QObject* child, Mode m) :
    QEvent(QEvent::User)
  , parent_(parent)
  , child_(child)
  , mode(m)
{

}

QObject* ChildEvent::parent() const
{
    return parent_;
}

QObject* ChildEvent::child() const
{
    return child_;
}

QWidget*ChildEvent::parentWidget() const
{
    if(parent_->isWidgetType())
        return dynamic_cast<QWidget*>(parent_.data());
    return nullptr;
}

QWidget*ChildEvent::childWidget() const
{
    if(child_->isWidgetType())
        return dynamic_cast<QWidget*>(child_.data());
    return nullptr;
}
