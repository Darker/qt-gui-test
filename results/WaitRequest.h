#ifndef WAITREQUEST_H
#define WAITREQUEST_H
class QObject;
#include <memory>
/**
 * @brief The WaitRequest class describes an ongoing instance
 * of waiting for qwidget to appear.
 */
class WaitRequest
{
    public:
        WaitRequest(const int id);
        const int ID;
        virtual bool validate(QObject*) const = 0;
        virtual ~WaitRequest();
};
typedef std::shared_ptr<WaitRequest> WaitRequestPtr;
#endif // WAITREQUEST_H
