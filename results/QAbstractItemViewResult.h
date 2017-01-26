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
        // Will select all items that contain any of the strings
        // given by 1st argument
        virtual void selectItems(const QStringList&) override;
    protected:
        QAbstractItemView* targetView_;

};

#endif // QTREEWIDGETRESULT_H
