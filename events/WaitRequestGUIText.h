#ifndef WAITREQUESTGUITEXT_H
#define WAITREQUESTGUITEXT_H
#include "WaitRequest.h"
#include <QString>

class WaitRequestGUIText : public WaitRequest
{
    public:
        WaitRequestGUIText(const QString& text, const QString& id);
        bool validate(QObject*, TestingModule*) const override;
    protected:
        const QString text_;
};

#endif // WAITREQUESTGUITEXT_H
