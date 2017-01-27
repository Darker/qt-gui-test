#include "QActionResult.h"
#include <QAction>

QActionResult::QActionResult(QAction* target, TestingModule* parent) :
    SearchResult(target, parent)
  , targetAction_(target)
{}

void QActionResult::click()
{
    asyncTrigger();
}

void QActionResult::submit()
{
    asyncTrigger();
}

void QActionResult::asyncTrigger()
{
    if(!targetAction_.isNull()) {
        QObject::connect(this, &QActionResult::triggerWorkaround, targetAction_.data(), &QAction::trigger, Qt::QueuedConnection);
        emit triggerWorkaround();
        QObject::disconnect(this, nullptr, targetAction_.data(), nullptr);
    }
}
