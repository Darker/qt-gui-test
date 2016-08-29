#ifndef FILEDIALOGRESULT_H
#define FILEDIALOGRESULT_H
#include "DialogResult.h"
class QFileDialog;

class FileDialogResult : public DialogResult
{
        Q_OBJECT
    public:
        FileDialogResult(QFileDialog* dialog, TestingModule* module);

    protected:
        QFileDialog* targetFileDialog_;

    public slots:
        virtual void setValue(const QVariant&) override;
        virtual void submit() override;
};

#endif // FILEDIALOGRESULT_H
