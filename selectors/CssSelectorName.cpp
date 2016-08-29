#include "CssSelectorName.h"

CssSelectorName::CssSelectorName()
{

}

QString CssSelectorName::parse(const QString& input) const
{
    QString result;
    for(int i=0,l=input.length(); i<l; i++) {
        QChar character = input[i];
        if((character.isDigit() && i>0) || character.isLetter()) {
            result+=character;
        }
        else
            break;
    }
    q_object_name = result;
}

QObjectList CssSelectorName::filterElements(const QObjectList& list) const
{
    QObjectList results;
    Q_FOREACH(QObject* o, list) {
        if(o->objectName() == q_object_name) {
            results.push_back(o);
        }
    }
    return results;
}
