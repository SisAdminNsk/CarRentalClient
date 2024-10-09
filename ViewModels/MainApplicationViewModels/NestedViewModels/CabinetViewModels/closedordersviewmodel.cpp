#include "closedordersviewmodel.h"
#include "ui_closedordersviewmodel.h"

ClosedOrdersViewModel::ClosedOrdersViewModel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClosedOrdersViewModel)
{
    ui->setupUi(this);
}

ClosedOrdersViewModel::~ClosedOrdersViewModel()
{
    delete ui;
}
