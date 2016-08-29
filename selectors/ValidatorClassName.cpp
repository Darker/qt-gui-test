#include "ValidatorClassName.h"
#include <QObject>

//ValidatorClassName::ValidatorClassName(const QString& name) :
//    Validator()
//  , className_(name)
//{

//}

bool ValidatorClassName::validate(QObject* object) const
{
    return object->metaObject()->className() == className_;
}

QString ValidatorClassName::parse(const QString& source)
{
    className_ = "";
    for (int i = 0, l = source.length(); i < l; ++i) {
        QChar cur = source[i];
        if(cur.isLetterOrNumber() || cur=='_') {
            className_+=cur;
        }
        else {
            return source.right(l-i);
        }
    }
    return "";
}
