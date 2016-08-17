#include "DialogResult.h"

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
