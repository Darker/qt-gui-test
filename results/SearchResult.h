#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QObject>
#include <QEvent>
//#include <QApplication>
#include <QPointer>
#include <memory>
#include <QPoint>
class QApplication;
class QReadWriteLock;
class TestingModule;

class SearchResult : public QObject
{
        Q_OBJECT
    public:
        SearchResult(QObject*, TestingModule*);
        virtual ~SearchResult();
        typedef std::shared_ptr<SearchResult> SearchResultPtr;
        class Factory {
            public:
                static SearchResultPtr fromObject( QObject*, TestingModule*, bool ignoreUnimplemented = false );
                static void registerConstructor( const std::shared_ptr<SearchResult::Factory> factory );
                template <class T_ResType, class T_QObjectType>
                static void registerConstructor() {
                    registerConstructor(std::make_shared<SearchResult::FactorySimple<T_ResType, T_QObjectType>>());
                }

                virtual SearchResultPtr newInstance( QObject*, TestingModule* ) const = 0;
                virtual QString objectName() const = 0;
            protected:
            private:
                static QMap<QString, std::shared_ptr<SearchResult::Factory>>* getMap();
                static QReadWriteLock* getLock();
                // There is a cache that remembers which objects did resolve to which factories
                static QMap<QString, std::shared_ptr<SearchResult::Factory>>* getCache();
                // Returns basic factory for qobjects, which is instance of this class
                static std::shared_ptr<SearchResult::Factory> qobjectFactory;
        };
        template <class T_SearchResultSubclass, class T_QObjectSubclass>
        class FactorySimple: public Factory {
            public:
            virtual SearchResultPtr newInstance( QObject*o, TestingModule*m ) const override {
                return std::make_shared<T_SearchResultSubclass>(
                            qobject_cast<T_QObjectSubclass*>(o), m);
            }
            virtual QString objectName() const override {
                return T_QObjectSubclass::staticMetaObject.className();
            }
        };

        class QObjectFactory: public Factory {
        public:
            virtual SearchResultPtr newInstance(QObject* o, TestingModule* m) const override {
                return std::make_shared<SearchResult>(o, m);
            }
            virtual QString objectName() const override {return "QObject";}
            static QObjectFactory* instance();
        };

    signals:
        void clicked(const int x, const int y);
    public slots:
        virtual void setValue(const QVariant&);
        // Always override (x,y) based methods
        virtual void click(const int x, const int y);
        virtual void click(const QPoint&);
        virtual void click();

        virtual void hover(const int x, const int y);

        virtual void contextMenu(const int x, const int y);
        virtual void contextMenu()             {contextMenu(getMidpoint());}
        virtual void contextMenu(const QPoint&p){contextMenu(p.x(), p.y());}

        // For graphical objects, shall return mouse coordinates of this object
        virtual QPoint getMidpoint();
        // Submits the data
        // This is almost unique to dialogs
        virtual void submit();
        // Returns text that the user uses to navigate to this item
        // Should NOT return text of sub items. If no text is applicable
        // shhould NOT return qobject name
        virtual QString getGUIText();
        // Double clicks an item in the target
        // This can be menu item, item in qlistwidget or combobox
        virtual void doubleClickItem(const QString&);
        // Selects one or more items by their visible string values
        // If multi select isn't supported, only first item of list will be selected
        virtual void selectItems(const QStringList&);
    protected:
        void sendEvent(QEvent* e);
        void sendMouseEvent(QEvent::Type t, const int x, const int y, Qt::MouseButton button);
        QPointer<QObject> target_;
        QPointer<QApplication> app_;
};
typedef SearchResult::SearchResultPtr SearchResultPtr;
#endif // SEARCHRESULT_H
