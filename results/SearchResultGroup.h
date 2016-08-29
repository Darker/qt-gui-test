#ifndef SEARCHRESULTGROUP_H
#define SEARCHRESULTGROUP_H
#include "SearchResult.h"
#include <QList>
#include <QObjectList>
class SearchResultGroup : public SearchResult
{
        Q_OBJECT
    public:
        SearchResultGroup(TestingModule*);
        SearchResultGroup(const QObjectList&, TestingModule*);
        void loadList(const QObjectList& list, TestingModule* m = nullptr );
        // SearchResult interface
    public slots:
        virtual void setValue(const QVariant&) override;
        virtual void click(const int x, const int y) override;
        virtual void click() override;
        virtual void hover(const int x, const int y) override;
        virtual void submit() override;
        virtual QString getGUIText() override;
        virtual void doubleClickItem(const QString&) override;
        virtual void selectItems(const QStringList&) override;
    protected:
        QList<SearchResultPtr> results_;
};

#endif // SEARCHRESULTGROUP_H
