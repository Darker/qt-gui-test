#include "WaitRequestGUIText.h"
#include <QObject>
#include "../results/WidgetResult.h"
#include "../TestingModule.h"
WaitRequestGUIText::WaitRequestGUIText(const QString& text, const QString& id)
 : WaitRequest(id)
 , text_(text)
{

}
bool WaitRequestGUIText::validate(QObject* w, TestingModule*m) const
{
    if(w!=nullptr) {
        SearchResultPtr tmp = SearchResult::Factory::fromObject(w, m, false);
        const QString text = tmp->getGUIText();
        return text==text_ || text.indexOf(text_)!=-1;
    }
    return false;
}
