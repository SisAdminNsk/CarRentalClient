#include "activeordersviewmodel.h"
#include "ui_activeordersviewmodel.h"

#include "ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/OpenCarOrderCard/opencarordercardviewmodel.h"

ActiveOrdersViewModel::ActiveOrdersViewModel(const LoginResponse& loginResponse, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActiveOrdersViewModel),
    loginResponse(loginResponse)
{
    ui->setupUi(this);

    ui->progressBar->reset();
    ui->progressBar->hide();
}

void ActiveOrdersViewModel::InitializeCatalog(const QList<OpenedCarReservationResonse>& openedCarReservations){

    for(auto& openedReservation : openedCarReservations){
        ui->verticalLayout->addWidget(new OpenCarOrderCardViewModel(openedReservation,this));
        ui->verticalLayout->addWidget(new OpenCarOrderCardViewModel(openedReservation,this));
    }
}

ActiveOrdersViewModel::~ActiveOrdersViewModel()
{
    delete ui;
}
