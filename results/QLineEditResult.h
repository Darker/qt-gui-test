#ifndef QLINEEDITRESULT_H
#define QLINEEDITRESULT_H
#include "WidgetResult.h"
#include <QPointer>
class QLineEdit;
class QLineEditResult : public WidgetResult
{
        Q_OBJECT
    public:
        QLineEditResult(QLineEdit* target, TestingModule* parent);
    protected:
        QPointer<QLineEdit> targetLineEdit_;

        // SearchResult interface
    public slots:
        virtual void setValue(const QVariant&) override;
        virtual QString getGUIText() override;
        virtual void submit() override;
};

#endif // QLINEEDITRESULT_H
