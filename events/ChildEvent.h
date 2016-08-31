#ifndef CHILDEVENT_H
#define CHILDEVENT_H
#include <QEvent>
#include <QObject>
#include <QPointer>
class QWidget;

class ChildEvent : public QEvent
{
    public:
        enum Mode: unsigned char {
            ADD,
            REMOVE
        };
        ChildEvent(QObject* parent, QObject* child, Mode m);
        QObject* parent() const;
        QObject* child() const;
        // Returns true if both child and parent are not null
        bool valid() const;
        QWidget* parentWidget() const;
        QWidget* childWidget() const;
        const Mode mode;
    protected:
        QPointer<QObject> child_;
        QPointer<QObject> parent_;
        const QObject* const originalChildPtr_;
        const QObject* const originalParentPtr_;

};

#endif // CHILDEVENT_H
