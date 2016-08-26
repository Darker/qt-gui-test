#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
class QAction;
class QTreeWidgetItem;
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
        void treeItemDbl(QModelIndex);
        void treeItemDbl(QTreeWidgetItem*,int);
        void showDialog();
        void fileDialog();
    signals:
        void clickWidgetRequest(const QString&);
    private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
