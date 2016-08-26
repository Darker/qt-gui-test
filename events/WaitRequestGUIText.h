#ifndef WAITREQUESTGUITEXT_H
#define WAITREQUESTGUITEXT_H
#include "../results/WaitRequest.h"
#include <QString>

class WaitRequestGUIText : public WaitRequest
{
    public:
        WaitRequestGUIText(const QString& text, const int id);
        bool validate(QObject*, TestingModule*) const override;
    protected:
        const QString text_;
};

#endif // WAITREQUESTGUITEXT_H
