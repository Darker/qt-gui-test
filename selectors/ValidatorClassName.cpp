#include "ValidatorClassName.h"
#include <QObject>

//ValidatorClassName::ValidatorClassName(const QString& name) :
//    Validator()
//  , className_(name)
//{

//}

bool ValidatorClassName::validate(QObject* object, TestingModule* m) const
{
    const QMetaObject* meta = object->metaObject();
    while(meta != nullptr) {
        if(meta->className() == className_)
            return true;
        meta = meta->superClass();
    }
    return false;
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
