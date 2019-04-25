#ifndef ADDCHILDEVENTFILTERCSS_H
#define ADDCHILDEVENTFILTERCSS_H

#include <QObject>
#include <memory>
#include "AddChildEventFilter.h"
class Selector;
class AddChildEventFilterCSS : public AddChildEventFilter
{
    Q_OBJECT
public:
    explicit AddChildEventFilterCSS(const QString& selector, QObject *parent = nullptr);

signals:

public slots:
protected:
    virtual void reportChildAdded(QObject* child, QObject* parent) override;
    std::shared_ptr<Selector> selector;
};

#endif // ADDCHILDEVENTFILTERCSS_H
