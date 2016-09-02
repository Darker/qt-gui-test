#include "QActionResult.h"
#include <QAction>

QActionResult::QActionResult(QAction* target, TestingModule* parent) :
    SearchResult(target, parent)
  , targetAction_(target)
{}

void QActionResult::click()
{
    if(!targetAction_.isNull())
        targetAction_->trigger();
}

void QActionResult::submit()
{
    if(!targetAction_.isNull())
        targetAction_->trigger();
}
