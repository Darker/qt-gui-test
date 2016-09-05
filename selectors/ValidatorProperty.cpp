#include "ValidatorProperty.h"
#include <cstring>

ValidatorProperty::ValidatorProperty() : Validator(), acceptsAllValues(false)
{

}


bool ValidatorProperty::validate(QObject*o, TestingModule*) const
{
    const QVariant prop = o->property(propertyName_.c_str());
    if(prop.isValid()) {
        if(acceptsAllValues)
            return true;
        else
            return prop == value_;

    }
    return false;
}

QString ValidatorProperty::parse(const QString& source)
{
    QString name("");
    QString val("");
    // this is false until the opening brace [
    bool started = false;
    // this is false until equals symbol (=)
    // if this remains false all the time
    // this validator will return true just if any value is present
    bool parsingValue = false;
    acceptsAllValues = true;
    // Start with 1 because [ is automatically skipped
    int i = 1;
    const int l = source.length();
    for (; i < l; ++i) {
        QChar cur = source[i];
//        if(cur=='[') {
//            started = true;
//        }
//        else

        if(cur==']') {
            ++i;
            break;
        }
        else if(!parsingValue && cur=='=') {
            parsingValue = true;
            acceptsAllValues = false;
        }
        else if(!parsingValue) {
            name += cur;
        }
        else if(parsingValue) {
            val += cur;
        }
    }
    value_ = QVariant::fromValue(val);
    propertyName_ = name.toStdString();

    return source.right(l-i);
}

ValidatorProperty::~ValidatorProperty()
{

}
