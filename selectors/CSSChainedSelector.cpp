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
    QList<int> base;
    base<<0;
    return find(parent, returnFirst, targetList, base);
}

QObjectList CSSChainedSelector::find(QObject* parent, bool returnFirst, QObjectList& targetList, const QList<int>& activeSelectors)
{
    const QObjectList& children = parent->children();
    Q_FOREACH(QObject* child, children) {
        QList<int> childSelectors(activeSelectors);

        Q_FOREACH(const int selectorIndex, activeSelectors) {
            if(selectorIndex>=chain_.length())
                throw std::runtime_error("Wtf man, selector index ain't in range.");
            SelectorPtr selector = chain_[selectorIndex];
            if(selector == nullptr)
                throw std::runtime_error("Ain't nobody got time for null selector.");
            // If current nth selector works for child
            if(selector->satisfies(child)) {
                // If there are MORE selectors to check on child's children
                if(selectorIndex+1<chain_.size()) {
                    const int nextIndex = selectorIndex+1;
                    if(childSelectors.indexOf(nextIndex)<0)
                        childSelectors.append(nextIndex);
                }
                // This is the final step of the chain, the selector was applied
                else {
                    if(!targetList.contains(child)) {
                        targetList.append(child);
                        if(returnFirst) {
                            return targetList;
                        }
                    }
                }
            }
        }
        find(child, returnFirst, targetList, childSelectors);
        if(returnFirst && targetList.size()>0) {
            return targetList;
        }
    }
    return targetList;
}
/** Iterate from bottomost selector. Every time, try to apply current selection
 * on object or it's parent or it's parent etc. If we exhaust all parents, it doesn't satisfy.
 * If we still have parents and we exhaust selectors, it satisfies them
 * The given object must ALWAYS satisfy the last selector.
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


