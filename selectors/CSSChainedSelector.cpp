#include "CSSChainedSelector.h"
#include "CssSelector.h"
#include <QChar>
CSSChainedSelector::CSSChainedSelector()
{

}
/**
 * Performs depth first search. If any object satisfies the first selector in chain, tries the second, third etc...
**/
QObjectList CSSChainedSelector::find(QObject* parent, bool returnFirst, QObjectList& targetList)
{
    return find(parent, returnFirst, targetList, 0);
}

QObjectList CSSChainedSelector::find(QObject* parent, bool returnFirst, QObjectList& targetList, const int currentSelector)
{
    if(currentSelector>=chain_.size())
        return targetList;
    SelectorPtr selector = chain_[currentSelector];
    //SelectorPtr firstSelector = chain_[0];

    const QObjectList& children = parent->children();
    Q_FOREACH(QObject* child, children) {
        bool mustInspect = true;
        // If current nth selector works for child
        if(selector->satisfies(child)) {
            // If there are MORE selectors to check on child's children
            if(currentSelector+1<chain_.size()) {
                find(child, returnFirst, targetList, currentSelector+1);
                mustInspect = false;
                if(returnFirst && targetList.size()>0) {
                    return targetList;
                }
            }
            //
            else {
                if(!targetList.contains(child)) {
                    targetList.append(child);
                    if(returnFirst) {
                        return targetList;
                    }
                }
            }
        }
        // Selectors didn't apply recursion but it's still worth to check children
        if(mustInspect && child->children().length()>0) {
            // Double recursion because I suck
            find(child, returnFirst, targetList, currentSelector);
            if(returnFirst && targetList.size()>0) {
                return targetList;
            }
            find(child, returnFirst, targetList, 0);
            if(returnFirst && targetList.size()>0) {
                return targetList;
            }
        }

    }
    return targetList;
}
/** Iterate from bottomost selector. Every time, try to apply current selection
 * on object or it's parent or it's parent etc. If we exhaust all parents it doesn't satisfy.
 * If we still have parents and we exhaust selectors, it satisfies them
 * The given object mus ALWAYS satisfy the last selector.
**/
bool CSSChainedSelector::satisfies(QObject* object, TestingModule* module) const
{
    int index = chain_.length()-1;
    if(!chain_[index]->satisfies(object, module)) {
        return false;
    }
    index--;
    object = object->parent();

    while(index>=0 && object!=nullptr) {
        if(chain_[index]->satisfies(object, module)) {
            if(--index < 0)
                break;
        }
        object = object->parent();
    }
    return index<0;
}

QString CSSChainedSelector::parse(const QString& source)
{
    chain_.clear();
    QString str = source;
    while(str.length()>0) {
        QChar character(str[0]);
        if(character==' '|| character=='\n' || character=='\t') {
            str = str.mid(1);
            continue;
        }
        CssSelectorPtr selector(new CssSelector);
        str = selector->parse(str);
        chain_.append(selector);
    }
    return str;
}

std::shared_ptr<Selector> CSSChainedSelector::optimize(std::shared_ptr<Selector> target) const
{
    if(target.get() != this)
        return target;
    std::shared_ptr<CSSChainedSelector> self = std::dynamic_pointer_cast<CSSChainedSelector>(target);
    if(self) {
        if(chain_.length() == 1) {
            return chain_[0]->optimize(chain_[0]);
        }
    }
    else
        return target;
    return target;
}


