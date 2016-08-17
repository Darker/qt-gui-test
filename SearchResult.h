#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QObject>
#include <QEvent>
//#include <QApplication>
#include <QPointer>
#include <memory>

class QApplication;
class QReadWriteLock;
class TestingModule;

class SearchResult : public QObject
{
        Q_OBJECT
    public:
        SearchResult(QObject*, TestingModule*);

        typedef std::shared_ptr<SearchResult> SearchResultPtr;
        class Factory {
            public:
                static SearchResultPtr fromObject( QObject*, TestingModule* );
                static void registerConstructor( const std::shared_ptr<SearchResult::Factory> factory );
                virtual SearchResultPtr newInstance( QObject*, TestingModule* ) const = 0;
                virtual QString objectName() const = 0;
            protected:
            private:
                static QMap<QString, std::shared_ptr<SearchResult::Factory>>* getMap();
                static QReadWriteLock* getLock();
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

    signals:
        clicked(const int x, const int y);
    public slots:
        virtual void setValue(const QVariant&);
        virtual void click(const int x, const int y);
        virtual void click();
        virtual void hover(const int x, const int y);
        virtual void submit();
        virtual QString getGUIText();
    protected:
        void sendEvent(QEvent* e);
        void sendMouseEvent(QEvent::Type t, const int x, const int y, Qt::MouseButton button);
        QPointer<QObject> target_;
        QPointer<QApplication> app_;
};
typedef SearchResult::SearchResultPtr SearchResultPtr;
#endif // SEARCHRESULT_H
