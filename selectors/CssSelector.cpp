#include "CssSelector.h"
#include "ValidatorName.h"
#include "ValidatorClassName.h"
#include "ValidatorGUIText.h"
#include <stdexcept>



CssSelector::CssSelector(const QString& str) :
    Selector()
  , source_(str)
{
    parse(source_);
}

CssSelector::CssSelector() :
    Selector()
  , source_("")
{

}

QString CssSelector::parse(const QString& input)
{
    QString str = input;
    sub_.clear();
    source_ = input;
    bool can_be_class_name = true;
    bool can_be_object_name = true;
    while(str.length()>0) {
    //for (int i = 0; i < str.length(); ++i) {
        QChar character = str[0];
        Validator* validator = nullptr;
        if(can_be_object_name && character == '#') {
            validator = new ValidatorName;
        }
        // Class name
        else if(can_be_class_name && character.isLetter()) {
            validator = new ValidatorClassName;
        }
        else if(character == '"') {
            validator = new ValidatorGUIText;
        }
        // End of selector
        else if(character == ' ') {
            return str.mid(1);
        }
        else {
            throw std::runtime_error((QString("Unparsable CSS: ")+input).toStdString());
        }
        if(validator != nullptr) {
            str = validator->parse(str);
            sub_.push_back(ValidatorPtr(validator));
        }
        else {
            throw std::runtime_error((QString("CSS never ends: ")+input).toStdString());
        }

        if(!can_be_class_name)
            can_be_object_name = false;
        can_be_class_name = false;
    }
}

bool CssSelector::satisfies(QObject* object) const
{
    Q_FOREACH(ValidatorPtr validator, sub_) {
        if(!validator->validate(object, TestingModule* m))
            return false;
    }
    return true;
}
