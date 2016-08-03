#ifndef WIDGETRESULT_H
#define WIDGETRESULT_H

#include <QWidget>
#include <QEvent>
#include <QApplication>
#include <QPointer>
#include "TestingModule.h"

class WidgetResult : public QObject
{
        Q_OBJECT
    public:
        WidgetResult(QWidget*, TestingModule*);


    signals:
        clicked(const int x, const int y);
    public slots:
        virtual void setValue(const QVariant&);
        virtual void click(const int x, const int y);
        virtual void click();
        virtual void submit();
    protected:
        void sendEvent(QEvent* e);
        void sendMouseEvent(QEvent::Type t, const int x, const int y, Qt::MouseButton button);
        QPointer<QWidget> target_;
        QPointer<QApplication> app_;
};

#endif // WIDGETRESULT_H
