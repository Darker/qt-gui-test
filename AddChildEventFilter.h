#ifndef ADDCHILDEVENTFILTER_H
#define ADDCHILDEVENTFILTER_H

#include <QObject>
#include <QPointer>
class QEvent;
class TestingModule;

class AddChildEventFilter : public QObject
{
        Q_OBJECT
    public:
        explicit AddChildEventFilter(TestingModule* m, QObject *parent = 0);
        virtual ~AddChildEventFilter();
    protected:
        bool eventFilter(QObject *obj, QEvent *event) override;
        QPointer<TestingModule> mod_;
};

#endif // ADDCHILDEVENTFILTER_H
