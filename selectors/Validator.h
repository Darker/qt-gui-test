#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <memory>
#include <QString>
/**
 * @brief The Validator class serves to validate QObject during selection
 */
class QObject;
class Validator
{
    public:
        Validator();
        virtual ~Validator();
        virtual bool validate(QObject* object) const = 0;
        virtual QString parse(const QString& source) = 0;
};
typedef std::shared_ptr<Validator> ValidatorPtr;
#endif // VALIDATOR_H
