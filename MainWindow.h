#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QAction;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    public slots:
        void clickWidget(const QString& name);
        void clickWidget();
        void actionClicked();
        void menuClicked(QAction*);
        void showDialog();
        void fileDialog();
    signals:
        clickWidgetRequest(const QString&);
    private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
