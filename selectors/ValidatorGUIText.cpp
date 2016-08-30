#include "ValidatorGUIText.h"
#include "../results/SearchResult.h"
#include <stdexcept>
ValidatorGUIText::ValidatorGUIText()
{

}


bool ValidatorGUIText::validate(QObject* object, TestingModule* m) const
{
    SearchResultPtr result = SearchResult::Factory::fromObject(object, m);
    return result->getGUIText().indexOf(text_)!=-1;
}

QString ValidatorGUIText::parse(const QString& source)
{
    text_ = "";
    bool escaped = false;
    for (int i = 1, l = source.length(); i < l; ++i) {
        QChar cur = source[i];
        if(cur == '\\') {
            escaped = true;
            continue;
        }
        else if(!escaped && cur == '\"') {
            return source.right(l-i-1);
        }
        text_+=cur;
        escaped = false;
    }
    throw std::runtime_error("Expected \" at the end of GUI text definition!");
}
