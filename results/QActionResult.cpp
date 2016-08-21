#include "QActionResult.h"

QActionResult::QActionResult(QAction* target, TestingModule* parent) :
    SearchResult(target, parent)
  , targetAction_(target)
{}

void QActionResult::click()
{
    targetAction_->trigger();
}

void QActionResult::submit()
{
    targetAction_->trigger();
}
