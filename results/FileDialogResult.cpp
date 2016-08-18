#include "FileDialogResult.h"
#include <QVariant>

FileDialogResult::FileDialogResult(QFileDialog* dialog, TestingModule* module) :
    DialogResult(dialog, module)
  , targetFileDialog_(dialog)
{

}
#include <QDebug>
#include <QUrl>
void FileDialogResult::setValue(const QVariant& var)
{
    if( var.canConvert<QString>() ) {
        targetFileDialog_->setDirectory(var.toString());
        // These two were added later, when it didn't work
        // but they didn't help in any way
        targetFileDialog_->selectFile(var.toString());
        QUrl asUrl(var.toString());
        targetFileDialog_->selectUrl(asUrl);

        QString directory = targetFileDialog_->directory().absolutePath();
        qDebug()<<"New dir: "<<directory;
        // Copied from QFileDialog::getExistingDirectory to check the real output
        qDebug()<<"Selected: "<<targetFileDialog_->selectedUrls().value(0).toString();
    }
}
