#ifndef WAITREQUESTCSSdsadsa_H
#define WAITREQUESTCSSdsadsa_H
#include "WaitRequest.h"
#include <QString>
class Selector;
typedef std::shared_ptr<Selector> SelectorPtr;
class WaitRequestCSS : public WaitRequest
{
    public:
        WaitRequestCSS(SelectorPtr selector, const QString& id);
        bool validate(QObject*, TestingModule*) const override;
    protected:
        const QString text_;
        SelectorPtr selector_;
};

#endif // WAITREQUESTGUITEXT_H
