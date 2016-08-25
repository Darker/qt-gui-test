#ifndef FILEDIALOGRESULT_H
#define FILEDIALOGRESULT_H
#include "DialogResult.h"
#include <QFileDialog>

class FileDialogResult : public DialogResult
{
    public:
        FileDialogResult(QFileDialog* dialog, TestingModule* module);

    protected:
        QFileDialog* targetFileDialog_;

    public slots:
        virtual void setValue(const QVariant&) override;
        virtual void submit() override;
};

#endif // FILEDIALOGRESULT_H
