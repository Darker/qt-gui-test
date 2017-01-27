#include "ValidatorClassName.h"
#include <QObject>

bool ValidatorClassName::validate(QObject* object, TestingModule*) const
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
        if(cur.isLetterOrNumber() || cur=='_' || cur=='.') {
            className_+=cur;
        }
        else {
            className_ = className_.replace(".", "::");
            return source.right(l-i);
        }
    }
    className_ = className_.replace(".", "::");
    return "";
}
