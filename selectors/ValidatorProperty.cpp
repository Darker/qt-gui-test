#include "ValidatorProperty.h"

ValidatorProperty::ValidatorProperty() : Validator(), acceptsAllValues(false)
{

}


bool ValidatorProperty::validate(QObject* object, TestingModule* m) const
{
}

QString ValidatorProperty::parse(const QString& source)
{
    QString val("");
    // this is false until the opening brace [
    bool started = false;
    // this is false until equals symbol (=)
    // if this remains false all the time
    // this validator will return true just if any value is present
    bool parsingValue = false;
    acceptsAllValues = true;

    for (int i = 1, l = source.length(); i < l; ++i) {
        QChar cur = source[i];
        if(cur=='[') {
            started = true;
        }
        else if(cur==']') {
            return source.right(l-i);
        }
        else
    }
    return "";
}
