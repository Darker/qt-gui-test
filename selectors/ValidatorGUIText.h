#ifndef VALIDATORGUITEXT_H
#define VALIDATORGUITEXT_H
#include "Validator.h"

class ValidatorGUIText : public Validator
{
    public:
        ValidatorGUIText();
        virtual bool validate(QObject* object, TestingModule* m) const override;
        virtual QString parse(const QString& source) override;
    protected:
        QString text_;
};

#endif // VALIDATORGUITEXT_H
