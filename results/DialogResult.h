#ifndef DIALOGRESULT_H
#define DIALOGRESULT_H
#include "WidgetResult.h"
class QDialog;
class DialogResult : public WidgetResult
{
        Q_OBJECT
    public:
        DialogResult(QDialog* dialog, TestingModule* module);

        // SearchResult interface
    public slots:
        virtual void submit() override;
    protected:
        QPointer<QDialog> targetDialog_;




        // SearchResult interface
    public slots:
        virtual QString getGUIText() override;
};

#endif // DIALOGRESULT_H
