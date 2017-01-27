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
    //targetDialog_->done(QDialog::Accepted);
    if(!targetDialog_.isNull()) {
        QMetaObject::invokeMethod( targetDialog_.data(),
                                   "done",//&QDialog::done,//
                                   Qt::QueuedConnection,
                                   Q_ARG( int, QDialog::Accepted )
        );
    }
}


QString DialogResult::getGUIText()
{
    if(!targetDialog_->windowTitle().isEmpty())
        return targetDialog_->windowTitle();
    else
        return WidgetResult::getGUIText();
}
