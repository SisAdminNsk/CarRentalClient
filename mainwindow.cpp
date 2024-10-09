#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::OnRegistratePushButtonClicked(){

}

void MainWindow::OnLoginPushButtonClicked(){

}

void MainWindow::Setup(){

    setFixedSize(500,320);
    setMinimumSize(500,320);
    setMaximumSize(500,320);
}
