#include "WaitRequestCSS.h"
#include "../selectors/Selector.h"
WaitRequestCSS::WaitRequestCSS(SelectorPtr selector, const int id)
 : WaitRequest(id)
 , selector_(selector)
{

}

bool WaitRequestCSS::validate(QObject*o, TestingModule* m) const
{
  return selector_->satisfies(o, m);
}
