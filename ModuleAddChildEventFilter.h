#ifndef mmmADDCHILDEVENTFILTER_H
#define mmmADDCHILDEVENTFILTER_H

#include <QObject>
#include <QPointer>
#include "AddChildEventFilter.h"
class QEvent;
class TestingModule;

class ModuleAddChildEventFilter : public AddChildEventFilter
{
        Q_OBJECT
    public:
        explicit ModuleAddChildEventFilter(TestingModule* m, QObject *parent = 0);
        virtual ~ModuleAddChildEventFilter();
    protected:
        QPointer<TestingModule> mod_;
    protected slots:
        void slotChildAdded(QObject* child, QObject* parent);
};

#endif // ADDCHILDEVENTFILTER_H
