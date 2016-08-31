#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);//tableContextMenu(const QPoint&)
    connect(ui->tableWidget, &QWidget::customContextMenuRequested, this, &MainWindow::tableContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickWidget(const QString& name)
{
    clickWidgetRequest(name);
}

void MainWindow::clickWidget()
{
    const QString text = ui->lineEdit->text();
    ui->lineEdit->setText("");
    clickWidget(text);
    //ui->lineEdit->setText(text);
}

void MainWindow::actionClicked()
{
    qDebug()<<"Clicked!";
}

void MainWindow::menuClicked(QAction* a)
{
    qDebug()<< "Clicked: "<<a->text();
}

void MainWindow::treeItemDbl(QModelIndex i)
{
    qDebug()<<"Abstract item clicked: "<<i.data().toString();
}
#include <QTreeWidgetItem>
void MainWindow::treeItemDbl(QTreeWidgetItem*i, int index)
{
    qDebug()<<"Tree widget item clicked: "<<i->text(index);
}
#include <QMessageBox>
void MainWindow::showDialog()
{
    QMessageBox::warning(this, "!!!", "U gon die.");
}
#include <QFileDialog>
void MainWindow::fileDialog()
{
    QString ddd = QFileDialog::getExistingDirectory(this, "Select file or die!");
    qDebug()<<"Selected file: "<<ddd;
}
 #include <QInputDialog>
void MainWindow::askStuff()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok)
        qDebug()<<"User says:"<<text;
    else
        qDebug()<<"User rejected given dialog.";
}

void MainWindow::cellDblClick(int x, int y)
{
    qDebug()<<"Cell double clicked at ["<<x<<", "<<y<<"]";
}

void MainWindow::tableContextMenu(const QPoint& point)
{
    makeContextMenu(point, ui->tableWidget);
}
#include <QMenu>
void MainWindow::makeContextMenu(const QPoint& pos, QWidget* target)
{
    QMenu *menu = new QMenu(this);
    menu->addAction(new QAction("Action 1", menu));
    menu->addAction(new QAction("Action 2", menu));
    menu->addAction(new QAction("Action 3", menu));
    // Notify window about clicking
    QObject::connect(menu, &QMenu::triggered, this, &MainWindow::menuClicked);
    // If this is a scroll area, map coordinates to real app coordinates
    if(QAbstractScrollArea* area = dynamic_cast<QAbstractScrollArea*>(target))
        menu->popup(area->viewport()->mapToGlobal(pos));
    else
        menu->popup(pos);
}


