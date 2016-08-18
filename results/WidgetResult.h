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
        void click() override;
        void click(const int x, const int y) override;
    private:
        QPointer<QWidget> targetWidget_;
};
typedef std::shared_ptr<WidgetResult> WidgetResultPtr;
#endif // WIDGETRESULT_H
