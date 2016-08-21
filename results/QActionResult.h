#ifndef QACTIONRESULT_H
#define QACTIONRESULT_H

#include <QObject>
#include <QAction>
#include "SearchResult.h"

class QActionResult : public SearchResult
{
        Q_OBJECT
    public:
        QActionResult(QAction* target, TestingModule* parent);


        // SearchResult interface
    public slots:
        virtual void click() override;
        virtual void submit() override;
    protected:
        QPointer<QAction> targetAction_;
};

#endif // QACTIONRESULT_H
