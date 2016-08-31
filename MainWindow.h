#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QPoint>
class QAction;
class QTreeWidgetItem;
namespace Ui {
    class MainWindow;
}
class QMenu;
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
        void askStuff();
        void cellDblClick(int,int);
        void tableContextMenu(const QPoint&);
    signals:
        void clickWidgetRequest(const QString&);
    protected:
        void makeContextMenu(const QPoint& pos, QWidget* target);
    private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
