#include "DialogResult.h"
#include <QDialog>

DialogResult::DialogResult(QDialog* dialog, TestingModule* module) :
    WidgetResult(dialog, module)
  , targetDialog_(dialog)
{

}

void DialogResult::submit()
{
    //targetDialog_->accept();
    targetDialog_->done(QDialog::Accepted);
}


QString DialogResult::getGUIText()
{
    if(!targetDialog_->windowTitle().isEmpty())
        return targetDialog_->windowTitle();
    else
        return WidgetResult::getGUIText();
}
