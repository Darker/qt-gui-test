#ifndef QTREEWIDGETRESULT_H
#define QTREEWIDGETRESULT_H
#include "WidgetResult.h"
#include <QAbstractItemView>
class QAbstractItemViewResult : public WidgetResult
{
        Q_OBJECT
    public:
        QAbstractItemViewResult(QAbstractItemView*, TestingModule*);
    public slots:
        virtual void doubleClickItem(const QString&) override;
        virtual void selectItems(const QStringList&) override;
    protected:
        QAbstractItemView* targetView_;

};

#endif // QTREEWIDGETRESULT_H
