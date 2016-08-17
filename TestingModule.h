#ifndef TESTINGMODULE_H
#define TESTINGMODULE_H
#include <QObject>
#include <QApplication>
#include <QPointer>
#include <QWidget>
#include <QString>
#include <QThread>
#include "SearchResult.h"
class TestingModule: public QObject
{
        Q_OBJECT
    public:
        TestingModule(QApplication* app);
        virtual QWidget* byName(const QString& name);
        virtual SearchResultPtr byText(const QString& text);
        virtual ~TestingModule();
        virtual QApplication* getApp() const {
            return app_.isNull()?nullptr:app_;
        }
    public slots:
        void start();
        void command(const QString& name, const QString& paramstr);
    // Signals that can be delegated over to the listener
    protected:
        QPointer<QApplication> app_;
};

#endif // TESTINGMODULE_H
