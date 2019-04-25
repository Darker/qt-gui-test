#ifndef ADDCHILDEVENTFILTER_H
#define ADDCHILDEVENTFILTER_H

#include <QObject>

class AddChildEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit AddChildEventFilter(QObject *parent = 0);
    virtual ~AddChildEventFilter();
signals:
    void childAdded(QObject* child, QObject* parent);
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    virtual void reportChildAdded(QObject* child, QObject* parent);
};

#endif // ADDCHILDEVENTFILTER_H
