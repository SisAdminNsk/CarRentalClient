#include "cabinetviewmodel.h"
#include "ui_cabinetviewmodel.h"

CabinetViewModel::CabinetViewModel(const LoginResponse& loginResponse, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CabinetViewModel)
{
    ui->setupUi(this);

    this->personalViewModel = new PersonalDataViewModel(loginResponse);
    this->ui->stackedWidget->setCurrentWidget(personalViewModel);
    this->activeOrdersViewModel = new ActiveOrdersViewModel();
    this->closedOrdersViewModel = new ClosedOrdersViewModel();

    ui->stackedWidget->addWidget(personalViewModel);
    ui->stackedWidget->addWidget(activeOrdersViewModel);
    ui->stackedWidget->addWidget(closedOrdersViewModel);

    QObject::connect(ui->profileDataButton, &QPushButton::clicked, this, &CabinetViewModel::OnPersonalDataButtonClicked);
    QObject::connect(ui->activeOrdersButton, &QPushButton::clicked, this, &CabinetViewModel::OnActiveOrdersButtonClicked);
    QObject::connect(ui->closedOrdersButton, &QPushButton::clicked, this, &CabinetViewModel::OnClosedOrdersButtonClicked);
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
}

void CabinetViewModel::OnClosedOrdersButtonClicked(){
    ui->stackedWidget->setCurrentWidget(closedOrdersViewModel);
}

CabinetViewModel::~CabinetViewModel()
{
    delete ui;
}
