#include "ValidatorName.h"
#include <QObject>
ValidatorName::ValidatorName() :
    Validator()
{

}

bool ValidatorName::validate(QObject* object) const
{
    return object->objectName() == name_;
}


QString ValidatorName::parse(const QString& source)
{
    name_ = "";
    for (int i = 1, l = source.length(); i < l; ++i) {
        QChar cur = source[i];
        if(cur.isLetterOrNumber() || cur=='_') {
            name_+=cur;
        }
        else {
            return source.right(l-i);
        }
    }
    return "";
}
