#ifndef VALIDATORNAME_H
#define VALIDATORNAME_H
#include "Validator.h"
#include <QString>
/**
 * Validates objects by given QObject name
*/
class ValidatorName : public Validator
{
    public:
        ValidatorName();
        virtual bool validate(QObject* object) const override;
        virtual QString parse(const QString& source) override;
    protected:
        QString name_;

};

#endif // VALIDATORNAME_H
