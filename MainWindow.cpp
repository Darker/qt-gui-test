#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
