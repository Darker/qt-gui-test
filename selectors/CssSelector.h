#ifndef CSSSELECTOR_H
#define CSSSELECTOR_H
#include "Selector.h"
#include "Validator.h"

class CssSelector : public Selector
{
    public:
        CssSelector(const QString&);
        CssSelector();
        virtual bool satisfies(QObject* object) const override;
        QString parse(const QString&);
    protected:
        QList<std::shared_ptr<Validator>> sub_;
        QString source_;
};
typedef std::shared_ptr<CssSelector> CssSelectorPtr;
#endif // CSSSELECTOR_H
