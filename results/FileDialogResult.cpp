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
        targetFileDialog_->selectFile(var.toString());
        QUrl asUrl(var.toString());
        targetFileDialog_->selectUrl(asUrl);

        QString directory = targetFileDialog_->directory().absolutePath();
        qDebug()<<"New dir: "<<directory;
        qDebug()<<"Selected: "<<targetFileDialog_->selectedUrls().value(0).toString();
    }
}
