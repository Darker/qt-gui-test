#include "WaitRequest.h"
#include <QObjectList>


WaitRequest::WaitRequest(const QString& id)
 : ID(id)
{

}

bool WaitRequest::validateChildren(QObject*parent, TestingModule*m, bool returnOn) const
{
    const QObjectList& children = parent->children();
    Q_FOREACH(QObject* child, children) {
        if(returnOn == validate(child, m))
            return returnOn;
    }
    return !returnOn;
}

WaitRequest::~WaitRequest()
{

}

