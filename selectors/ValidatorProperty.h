#ifndef VALIDATORPROPERTY_H
#define VALIDATORPROPERTY_H
#include "Validator.h"
#include <QVariant>
class ValidatorProperty : public Validator
{
    public:
        ValidatorProperty();
        virtual bool validate(QObject* object, TestingModule* m) const override;
        virtual QString parse(const QString& source) override;
    protected:
        QString propertyName_;
        bool acceptsAllValues;
        QVariant value_;
};

#endif // VALIDATORPROPERTY_H
