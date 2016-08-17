#ifndef DIALOGRESULT_H
#define DIALOGRESULT_H
#include "../WidgetResult.h"
#include <QDialog>
class DialogResult : public WidgetResult
{
    public:
        DialogResult(QDialog* dialog, TestingModule* module);

        // SearchResult interface
    public slots:
        virtual void submit() override;
    protected:
        QPointer<QDialog> targetDialog_;



};

#endif // DIALOGRESULT_H
