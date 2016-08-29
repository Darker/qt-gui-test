#include "Selector.h"

Selector::Selector()
{

}

QObjectList Selector::find(QObject* parent, bool returnFirst, QObjectList& targetList)
{
    const QObjectList& children = parent->children();
    Q_FOREACH(QObject* child, children) {
        if(satisfies(child)) {
            targetList.push_back(child);
            if(returnFirst)
                return targetList;
        }
        find(child, returnFirst, targetList);
        if(returnFirst && targetList.size()>0) {
            return targetList;
        }
    }
    return targetList;
}

QObjectList Selector::find(QObject* parent, bool returnFirst)
{
    QObjectList result;
    find(parent, returnFirst, result);
    return result;
}

QObject*Selector::findOne(QObject* parent)
{
    QObjectList result;
    find(parent, true, result);
    if(result.size()>0)
        return result[0];
    else
        return nullptr;
}

#include "CssSelector.h"
std::shared_ptr<Selector> Selector::parseString(const QString& data)
{
    std::shared_ptr<CssSelector> css = std::shared_ptr<CssSelector>(new CssSelector);
    css->parse(data);
    return css;
}
