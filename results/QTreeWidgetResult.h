#ifndef QTREEWIDGETRESULT_H
#define QTREEWIDGETRESULT_H
#include "WidgetResult.h"
#include <QAbstractItemView>
class QTreeWidgetResult : public WidgetResult
{
    public:
        QTreeWidgetResult(QAbstractItemView*, TestingModule*);

        // SearchResult interface
    public slots:
        virtual void doubleClickItem(const QString&) override;
};

#endif // QTREEWIDGETRESULT_H
