#ifndef WAITREQUESTCSSdsadsa_H
#define WAITREQUESTCSSdsadsa_H
#include "WaitRequest.h"
#include <QString>
class CssSelector;
typedef std::shared_ptr<CssSelector> CssSelectorPtr;
class WaitRequestCSS : public WaitRequest
{
    public:
        WaitRequestCSS(CssSelectorPtr selector, const int id);
        bool validate(QObject*, TestingModule*) const override;
    protected:
        const QString text_;
        CssSelectorPtr selector_;
};

#endif // WAITREQUESTGUITEXT_H
