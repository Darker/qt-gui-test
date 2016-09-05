#include "WaitRequestCSS.h"
#include "../selectors/Selector.h"
WaitRequestCSS::WaitRequestCSS(SelectorPtr selector, const QString& id)
 : WaitRequest(id)
 , selector_(selector)
{

}

bool WaitRequestCSS::validate(QObject*o, TestingModule* m) const
{
    if(selector_->satisfies(o, m)) {
        return true;
    }
    else {
        if(validateChildren(o, m, true))
            return true;
    }
    return false;
}
