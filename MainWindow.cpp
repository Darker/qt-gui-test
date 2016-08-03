#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

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
    clickWidget(ui->lineEdit->text());
}

void MainWindow::actionClicked()
{
    qDebug()<<"Clicked!";
}
