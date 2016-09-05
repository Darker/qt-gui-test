#include "DeleteOnHideFilter.h"
#include <QHideEvent>
DeleteOnHideFilter::DeleteOnHideFilter(QObject *parent) : QObject(parent)
{

}

bool DeleteOnHideFilter::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() == QEvent::Hide) {
        obj->deleteLater();
//        if(QHideEvent* hide = dynamic_cast<QHideEvent*>(event)) {

//        }
    }
    return false;
}
