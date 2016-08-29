#ifndef SELECTOR_H
#define SELECTOR_H
#include <QString>
#include <QObjectList>
#include <memory>

class Selector
{
    public:
        Selector();
        virtual QObjectList find(QObject* parent, bool returnFirst, QObjectList& targetList);
        virtual QObjectList find(QObject* parent, bool returnFirst);
        virtual QObjectList find(QObject* parent) {return find(parent, false);}
        virtual QObject* findOne(QObject* parent);
        virtual bool satisfies(QObject* object) const = 0;
        /** Parses input and returns remaining data for sub-selectors **/
        virtual QString parse(const QString&) = 0;

        static std::shared_ptr<Selector> parseString(const QString& data);

};
typedef std::shared_ptr<Selector> SelectorPtr;
#endif // SELECTOR_H
