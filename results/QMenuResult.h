#ifndef QMENURESULT_H
#define QMENURESULT_H

#include <QObject>
#include <QMenu>
#include "WidgetResult.h"
class QMenuResult: public WidgetResult
{
        Q_OBJECT
    public:
        QMenuResult(QMenu*, TestingModule*);
    public slots:
        void click() override;
    protected:
        QPointer<QMenu> targetMenu_;
};

#endif // QMENURESULT_H
