#ifndef QTREEWIDGETRESULT_H
#define QTREEWIDGETRESULT_H
#include "WidgetResult.h"
#include <QAbstractItemView>
class QAbstractItemViewResult : public WidgetResult
{
    public:
        QAbstractItemViewResult(QAbstractItemView*, TestingModule*);


    public slots:
        virtual void doubleClickItem(const QString&) override;
    protected:
        QAbstractItemView* targetView_;
};

#endif // QTREEWIDGETRESULT_H
