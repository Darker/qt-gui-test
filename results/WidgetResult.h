#ifndef WIDGETRESULT_H
#define WIDGETRESULT_H
#include "SearchResult.h"
#include <QWidget>
class WidgetResult : public SearchResult
{
        Q_OBJECT
    public:
        WidgetResult(QWidget*, TestingModule*);

        class Factory: public SearchResult::Factory {
            public:
                virtual SearchResultPtr newInstance( QObject*, TestingModule* ) const override;
                virtual QString objectName() const override;
        };
    public slots:
        void click(const int x, const int y) override;
    private:
        QPointer<QWidget> targetWidget_;

        // SearchResult interface
    public slots:
        virtual QPoint getMidpoint() override;

        // SearchResult interface
    public slots:
        virtual void contextMenu(const int x, const int y) override;
};
typedef std::shared_ptr<WidgetResult> WidgetResultPtr;
#endif // WIDGETRESULT_H
