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
        QObjectList results;
        selector_->find(o, true, results);
        if(results.size()>0) {
            return true;
        }
    }
    return false;
}
