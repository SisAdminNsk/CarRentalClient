#include "cabinetviewmodel.h"
#include "ui_cabinetviewmodel.h"

#include <QMessageBox>

#include "Api/Endpoints/CarOrders/Requests/getopenedcarordersrequest.h"
#include "clientcache.h"

CabinetViewModel::CabinetViewModel(const LoginResponse& loginResponse, QWidget *parent) :
    QWidget(parent),
    parent(parent),
    loginResponse(loginResponse),
    ui(new Ui::CabinetViewModel)
{
    ui->setupUi(this);

    this->personalViewModel = new PersonalDataViewModel(loginResponse, this);
    this->ui->stackedWidget->setCurrentWidget(personalViewModel);
    this->activeOrdersViewModel = new ActiveOrdersViewModel(loginResponse, this);
    this->closedOrdersViewModel = new ClosedOrdersViewModel(loginResponse,this);

    ui->stackedWidget->addWidget(personalViewModel);
    ui->stackedWidget->addWidget(activeOrdersViewModel);
    ui->stackedWidget->addWidget(closedOrdersViewModel);

    QObject::connect(ui->profileDataButton, &QPushButton::clicked, this, &CabinetViewModel::OnPersonalDataButtonClicked);
    QObject::connect(ui->activeOrdersButton, &QPushButton::clicked, this, &CabinetViewModel::OnActiveOrdersButtonClicked);
    QObject::connect(ui->closedOrdersButton, &QPushButton::clicked, this, &CabinetViewModel::OnClosedOrdersButtonClicked);
}

void CabinetViewModel::CloseMainWindow(){
    parent->close();
}

void CabinetViewModel::FillProfileData(const CarsharingUserDto& carsharingUser){
    this->personalViewModel->FillProfileData(carsharingUser);
}

void CabinetViewModel::SetPersonalDataScene(){
    OnPersonalDataButtonClicked();
}

void CabinetViewModel::OnPersonalDataButtonClicked(){
    ui->stackedWidget->setCurrentWidget(personalViewModel);
    personalViewModel->WhenSwappedToView();
}

void CabinetViewModel::OnActiveOrdersButtonClicked(){
    ui->stackedWidget->setCurrentWidget(activeOrdersViewModel);
    activeOrdersViewModel->Update();
}

void CabinetViewModel::OnClosedOrdersButtonClicked(){
    ui->stackedWidget->setCurrentWidget(closedOrdersViewModel);
    closedOrdersViewModel->Update();
}

void CabinetViewModel::LoadOpenedCarOrders(){

    auto carsharingUserId = ClientCache::instance().GetCarsharingUserProfile().Id;

    auto getOpenedCarOrdersRequest = new GetOpenedCarOrdersRequest(loginResponse.Token, carsharingUserId);

    connect(getOpenedCarOrdersRequest, &GetOpenedCarOrdersRequest::OnSuccessSingal, this,
            &CabinetViewModel::OnGettingOpenedCarOrdersSuccess);

    connect(getOpenedCarOrdersRequest, &GetOpenedCarOrdersRequest::OnFailureSignal, this,
            &CabinetViewModel::OnGettingOpenedCarOrdersFailure);

    getOpenedCarOrdersRequest->SendApiRequest();
}

void CabinetViewModel::OnGettingOpenedCarOrdersSuccess(const QList<OpenedCarReservationResonse>& openedCarReservations){

    activeOrdersViewModel->InitializeCatalog(openedCarReservations);
}

void CabinetViewModel::OnGettingOpenedCarOrdersFailure(const QString& errorMessage){
    QMessageBox::information(this, "Ошибка получения списка активных заказов", errorMessage);
}


void CabinetViewModel::LoadClosedCarOrders(){

}

CabinetViewModel::~CabinetViewModel()
{
    delete ui;
}
