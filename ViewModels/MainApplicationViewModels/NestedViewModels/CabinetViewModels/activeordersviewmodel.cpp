#include "activeordersviewmodel.h"
#include "ui_activeordersviewmodel.h"

ActiveOrdersViewModel::ActiveOrdersViewModel(const LoginResponse& loginResponse, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActiveOrdersViewModel),
    loginResponse(loginResponse)
{
    ui->setupUi(this);
}

ActiveOrdersViewModel::~ActiveOrdersViewModel()
{
    delete ui;
}
