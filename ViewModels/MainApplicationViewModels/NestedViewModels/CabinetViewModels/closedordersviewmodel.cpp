#include "closedordersviewmodel.h"
#include "ui_closedordersviewmodel.h"

ClosedOrdersViewModel::ClosedOrdersViewModel(const LoginResponse& loginResponse, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClosedOrdersViewModel),
    loginResponse(loginResponse)
{
    ui->setupUi(this);
}

ClosedOrdersViewModel::~ClosedOrdersViewModel()
{
    delete ui;
}
