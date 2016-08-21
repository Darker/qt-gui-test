#include "QMenuResult.h"



QMenuResult::QMenuResult(QMenu*m, TestingModule*t) :
    WidgetResult(m, t)
  , targetMenu_(m)
{

}

void QMenuResult::click()
{
    QAction* a = targetMenu_->menuAction();
    a->trigger();
}
