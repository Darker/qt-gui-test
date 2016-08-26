#include "AddChildEventFilter.h"
#include "TestingModule.h"
#include <QEvent>
#include <QDebug>
#include <QWidget>
#include <QChildEvent>
#include <QCoreApplication>
#include "events/ChildEvent.h"
AddChildEventFilter::AddChildEventFilter(TestingModule* m, QObject *parent)
    : QObject(parent)
    , mod_(m)
{

}

AddChildEventFilter::~AddChildEventFilter()
{

}
bool AddChildEventFilter::eventFilter(QObject* parent, QEvent* event) {
    if(event->type() == QEvent::ChildAdded) {
        if(mod_.isNull())
            return false;
        if(QChildEvent* chevent = dynamic_cast<QChildEvent*>(event)) {
            if(chevent->added()) {
                QObject* child = chevent->child();
                if(child->isWidgetType()) {
                    child->installEventFilter(new AddChildEventFilter(mod_, child));
                    QCoreApplication::postEvent(
                                mod_,
                                new ChildEvent(
                                    parent,
                                    child,
                                    ChildEvent::ADD)
                    );
                }
            }

        }
    }
    return false;
}
