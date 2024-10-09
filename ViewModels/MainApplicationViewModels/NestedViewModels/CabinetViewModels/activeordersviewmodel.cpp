#include "activeordersviewmodel.h"
#include "ui_activeordersviewmodel.h"

ActiveOrdersViewModel::ActiveOrdersViewModel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActiveOrdersViewModel)
{
    ui->setupUi(this);
}

ActiveOrdersViewModel::~ActiveOrdersViewModel()
{
    delete ui;
}
