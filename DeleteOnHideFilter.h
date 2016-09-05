#ifndef DELETEONHIDEFILTER_H
#define DELETEONHIDEFILTER_H

#include <QObject>

class DeleteOnHideFilter : public QObject
{
        Q_OBJECT
    public:
        explicit DeleteOnHideFilter(QObject *parent = 0);

    signals:

    protected slots:
        bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // DELETEONHIDEFILTER_H
