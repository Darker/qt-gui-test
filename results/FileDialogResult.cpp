#include "FileDialogResult.h"
#include <QVariant>
#include <QFileInfo>

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
        QFileInfo info(var.toString());
        QFileInfo parent(info.absoluteDir().canonicalPath());
        if( parent.exists() ) {
            targetFileDialog_->setDirectory(parent.canonicalFilePath());
            targetFileDialog_->selectFile(info.fileName());
            //QUrl asUrl(info.absoluteFilePath());
            //targetFileDialog_->selectUrl(asUrl);
        }
        // These two were added later, when it didn't work
        // but they didn't help in any way



        //QString directory = targetFileDialog_->directory().absolutePath();
        //qDebug()<<"New dir: "<<directory;
        // Copied from QFileDialog::getExistingDirectory to check the real output
        //qDebug()<<"Selected: "<<targetFileDialog_->selectedUrls().value(0).toString();
    }
}
