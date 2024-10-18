#include "opencarordercardviewmodel.h"
#include "ui_opencarordercardviewmodel.h"

OpenCarOrderCardViewModel::OpenCarOrderCardViewModel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OpenCarOrderCardViewModel)
{
    ui->setupUi(this);
}

OpenCarOrderCardViewModel::~OpenCarOrderCardViewModel()
{
    delete ui;
}
