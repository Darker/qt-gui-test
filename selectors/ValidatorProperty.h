#ifndef VALIDATORPROPERTY_H
#define VALIDATORPROPERTY_H
#include "Validator.h"
#include <QVariant>
#include <string>
class ValidatorProperty : public Validator
{
    public:
        ValidatorProperty();
        virtual bool validate(QObject* object, TestingModule* m) const override;
        virtual QString parse(const QString& source) override;
        virtual ~ValidatorProperty();
    protected:
        std::string propertyName_;
        bool acceptsAllValues;
        QVariant value_;
};

#endif // VALIDATORPROPERTY_H
