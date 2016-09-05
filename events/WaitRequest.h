#ifndef WAITREQUEST_H
#define WAITREQUEST_H
class QObject;
class TestingModule;
#include <memory>
#include <QString>
/**
 * @brief The WaitRequest class describes an ongoing instance
 * of waiting for qwidget to appear.
 */
class WaitRequest
{
    public:
        WaitRequest(const QString& id);
        const QString ID;
        virtual bool validate(QObject*, TestingModule*) const = 0;
        // Calls validate for all children of given object
        // but not for the object itself
        // returns imediatelly if validate returns `returnOn` value
        // if no child returns required valie, requrns opposite of returnOn value
        virtual bool validateChildren(QObject*, TestingModule*, bool returnOn=true) const;
        virtual ~WaitRequest();
};
typedef std::shared_ptr<WaitRequest> WaitRequestPtr;
#endif // WAITREQUEST_H
