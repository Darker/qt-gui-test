#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <memory>
#include <QString>
/**
 * @brief The Validator class serves to validate QObject during selection
 */
class QObject;
class TestingModule;
class Validator
{
    public:
        Validator();
        virtual ~Validator();
        virtual bool validate(QObject* object) const {
          return validate(object, nullptr);
        }
        virtual bool validate(QObject* object, TestingModule* m) const = 0;
        virtual QString parse(const QString& source) = 0;
};
typedef std::shared_ptr<Validator> ValidatorPtr;
#endif // VALIDATOR_H
