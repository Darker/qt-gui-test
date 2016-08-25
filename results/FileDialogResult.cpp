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
        const QString strpath = var.toString();
        QFileInfo info(strpath);
        QFileInfo parent(info.absoluteDir().canonicalPath());
        const QString fileName = info.fileName();
        qDebug()<<"FileDialogResult::setValue("<<strpath<<')';
        qDebug()<<"  File:"<<fileName;
        qDebug()<<"  Parent path: "<<parent.canonicalFilePath();
        if( parent.exists() ) {
            targetFileDialog_->setDirectory(parent.canonicalFilePath());
            targetFileDialog_->selectFile(fileName);
            targetFileDialog_->fileSelected(fileName);

            const QStringList files = targetFileDialog_->selectedFiles();
            qDebug()<<"  "<<files;
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



void FileDialogResult::submit()
{
    qDebug()<<"FileDialogResult::submit()";
    const QStringList files = targetFileDialog_->selectedFiles();
    qDebug()<<"  "<<files;
    targetDialog_->accept();
    //targetFileDialog_->accept();
    //targetFileDialog_->done(QDialog::Accepted);
}
