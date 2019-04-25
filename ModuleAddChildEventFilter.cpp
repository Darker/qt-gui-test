#include "ModuleAddChildEventFilter.h"
#include "TestingModule.h"
#include <QEvent>
#include <QDebug>
#include <QWidget>
#include <QChildEvent>
#include <QCoreApplication>
#include "events/ChildEvent.h"
ModuleAddChildEventFilter::ModuleAddChildEventFilter(TestingModule* m, QObject *parent)
    : AddChildEventFilter(parent)
    , mod_(m)
{
    QObject::connect(this, &AddChildEventFilter::childAdded, this, &ModuleAddChildEventFilter::slotChildAdded);
}

ModuleAddChildEventFilter::~ModuleAddChildEventFilter()
{

}


void ModuleAddChildEventFilter::slotChildAdded(QObject* child, QObject* parent)
{
    QCoreApplication::postEvent(
                mod_,
                new ChildEvent(
                    parent,
                    child,
                    ChildEvent::ADD)
    );
}
