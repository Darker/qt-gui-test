#ifndef TESTINGMODULE_H
#define TESTINGMODULE_H
#include <QObject>
#include <QApplication>
#include <QPointer>
#include <QWidget>
#include <QString>
#include <QThread>
#include <memory>
#include "events/WaitRequest.h"
#include "TestingEvent.h"
class SearchResult;
typedef std::shared_ptr<SearchResult> SearchResultPtr;

class QEvent;


class TestingModule: public QObject
{
        Q_OBJECT
    public:
        TestingModule(QApplication* app);
        TestingModule();
        virtual QWidget* byName(const QString& name);
        virtual SearchResultPtr byText(const QString& text);
        virtual ~TestingModule();
        virtual QApplication* getApp() const {
            return app_.isNull()?nullptr:app_;
        }
        virtual bool event(QEvent*) override;
    public slots:
        void start();
        void command(const QString& name, const QString& paramstr, const QString& transactionId="");
        // Starts listening on ALL changes in QApplication
        void startListening();
    // Signals that can be delegated over to the listener
    signals:
        void t_event(const TestingEvent&);
        void message(const QString msg);
        void message(const QString msg, const QString transactionId);
    protected:
        QPointer<QApplication> app_;
        SearchResultPtr byText(QObject* obj, const QString&);
        void installEventFilters();
        // List of items we're waiting for
        // Currently, just GUI strings
        QList<WaitRequestPtr> requests;

};

#endif // TESTINGMODULE_H
