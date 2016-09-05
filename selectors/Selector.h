#ifndef SELECTOR_H
#define SELECTOR_H
#include <QString>
#include <QObjectList>
#include <memory>
class TestingModule;
class Selector
{
    public:
        Selector();
        virtual QObjectList find(QObject* parent, bool returnFirst, QObjectList& targetList);
        virtual QObjectList find(QObject* parent, bool returnFirst);
        virtual QObjectList find(QObject* parent) {return find(parent, false);}
        virtual QObject* findOne(QObject* parent);
        virtual bool satisfies(QObject* object, TestingModule* module) const = 0;
        virtual bool satisfies(QObject* object) const {return satisfies(object, nullptr);}
        virtual std::shared_ptr<Selector> optimize(std::shared_ptr<Selector> target) const {
            return target;
        }
        /** Parses input and returns remaining data for sub-selectors **/
        virtual QString parse(const QString&) = 0;

        static std::shared_ptr<Selector> parseString(const QString& data);

};
typedef std::shared_ptr<Selector> SelectorPtr;
#endif // SELECTOR_H
