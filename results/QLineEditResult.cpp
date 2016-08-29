#include "QLineEditResult.h"
#include <QLineEdit>

QLineEditResult::QLineEditResult(QLineEdit* target, TestingModule* parent) :
    WidgetResult(target, parent)
  , targetLineEdit_(target)
{

}


void QLineEditResult::setValue(const QVariant& v)
{
    targetLineEdit_->setText(v.toString());
    emit targetLineEdit_->textEdited(v.toString());
}


QString QLineEditResult::getGUIText()
{
    return "";
}


void QLineEditResult::submit()
{
    targetLineEdit_->returnPressed();
}
