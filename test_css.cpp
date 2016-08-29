#include <QDebug>
#include "selectors/CssSelector.h"
#include <QObjectList>
bool should_run_test() {
    return !true;
}

void run_test()
{
    CssSelector pokus("QWidget#ble");
    pokus.parse("\"pokus\"");
    qDebug()<<"Done.";
}
QObjectList the_recursive_fn(QObjectList& list, int iteration = 2) {
    if(iteration>0) {
        //list.push_back(new QObject);
        iteration--;
        the_recursive_fn(list, iteration);
        return list;
    }
    else {
        return list;
    }
}

#include <QObject>
QObjectList findObjectRecursively(QObject* parent, bool returnFirst, QObjectList& targetList) {
    const QObjectList& children = parent->children();
    Q_FOREACH(QObject* child, children) {
//        if(satisfies(child)) {
//            targetList.push_back(child);
//            if(returnFirst)
//                return targetList;
//        }
        findObjectRecursively(child, returnFirst, targetList);
        if(returnFirst && targetList.size()>0) {
            return targetList;
        }
    }
    if(targetList.isEmpty())
        return QObjectList();
    else
        return targetList;
}
#include "selectors/Selector.h"
void QLIST_craziness() {
    QObject* o_top = new QObject;
    QObject* child = new QObject(o_top);
    child = new QObject(child);

    QObjectList empty;
    SelectorPtr test = Selector::parseString("\"Show\"");
    findObjectRecursively(o_top, false, empty);
    qDebug()<<"Pause";

    delete o_top;
    /*the_recursive_fn(empty, 3);
    Q_FOREACH(QObject* o, empty) {
        delete o;
    }*/
}


