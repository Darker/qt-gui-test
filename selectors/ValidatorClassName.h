#ifndef VALIDATORCLASSNAME_H
#define VALIDATORCLASSNAME_H
#include "Validator.h"
#include <QString>

class ValidatorClassName : public Validator
{
    public:
        //ValidatorClassName(const QString& name);

        virtual bool validate(QObject* object, TestingModule* m) const override;
        virtual QString parse(const QString& source) override;
    protected:
        QString className_;
};

#endif // VALIDATORCLASSNAME_H
