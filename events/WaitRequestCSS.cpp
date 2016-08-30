#include "WaitRequestCSS.h"
#include "../selectors/CssSelector.h"
WaitRequestCSS::WaitRequestCSS(CssSelectorPtr selector, const int id)
 : WaitRequest(id)
 , selector_(selector)
{

}

bool WaitRequestCSS::validate(QObject*o, TestingModule* m) const
{
  return selector_->satisfies(o, m);
}
