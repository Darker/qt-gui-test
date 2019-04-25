#include "AddChildEventFilter.h"
#include <QEvent>
AddChildEventFilter::AddChildEventFilter(QObject *parent)
    : QObject(parent)
{

}

AddChildEventFilter::~AddChildEventFilter()
{

}
bool AddChildEventFilter::eventFilter(QObject* parent, QEvent* event) {
    if(event->type() == QEvent::ChildAdded) {
        if(QChildEvent* chevent = dynamic_cast<QChildEvent*>(event)) {
            if(chevent->added()) {
                QObject* child = chevent->child();
                if(child->isWidgetType()) {
                    reportChildAdded(child, parent);
                }
            }
        }
    }
    return false;
}

void AddChildEventFilter::reportChildAdded(QObject* child, QObject* parent)
{
    emit childAdded(child, parent);
}
