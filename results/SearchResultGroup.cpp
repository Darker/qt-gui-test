#include "SearchResultGroup.h"
#define DELEGATE_METHOD_LOOP(NAME, ARG, ARG_NAME) \
    void SearchResultGroup::NAME(ARG ARG_NAME) {\
        Q_FOREACH(SearchResultPtr result, results_) {\
            result->NAME(ARG_NAME);\
        }\
    }\

SearchResultGroup::SearchResultGroup(TestingModule*m) :
    SearchResult(nullptr, m)
{

}

SearchResultGroup::SearchResultGroup(const QObjectList&list, TestingModule*m) :
    SearchResult(nullptr, m)
{
    loadList(list, m);
}

void SearchResultGroup::loadList(const QObjectList&list, TestingModule* m )
{
    Q_FOREACH(QObject* obj, list) {
        SearchResultPtr result = SearchResult::Factory::fromObject(obj, m);
        if(result != nullptr)
            results_.append(result);
    }
}
DELEGATE_METHOD_LOOP(setValue, const QVariant&, v)
DELEGATE_METHOD_LOOP(click,,)
DELEGATE_METHOD_LOOP(submit,,)
DELEGATE_METHOD_LOOP(doubleClickItem, const QString&, v)
DELEGATE_METHOD_LOOP(selectItems, const QStringList&, v)

void SearchResultGroup::click(const int x, const int y)
{
    Q_FOREACH(SearchResultPtr result, results_) {
        result->click(x, y);
    }
}

void SearchResultGroup::hover(const int x, const int y)
{
    Q_FOREACH(SearchResultPtr result, results_) {
        result->hover(x, y);
    }
}


QString SearchResultGroup::getGUIText()
{
    if(results_.size()>0) {
        return results_[0]->getGUIText();
    }
    else
        return QString();
}
