#ifndef QACTIONRESULT_H
#define QACTIONRESULT_H

#include <QObject>
#include "SearchResult.h"
class QAction;

class QActionResult : public SearchResult
{
        Q_OBJECT
    public:
        QActionResult(QAction* target, TestingModule* parent);

    signals:
        void triggerWorkaround();
    public slots:
        virtual void click() override;
        virtual void submit() override;
        virtual void asyncTrigger();
    protected:
        QPointer<QAction> targetAction_;
};

#endif // QACTIONRESULT_H
