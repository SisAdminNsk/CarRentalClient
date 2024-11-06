#include "carrentalclientmainwindow.h"
#include "ui_carrentalclientmainwindow.h"
#include "clientcache.h"

#include <QMessageBox>

CarRentalClientMainWindow::CarRentalClientMainWindow(const LoginResponse& loginResponse, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CarRentalClientMainWindow)
{
    ui->setupUi(this);

    this->cabinetViewModel = new CabinetViewModel(loginResponse, this);
    this->carsViewModel = new CarsViewModel(loginResponse, this);

    ui->stackedWidget->addWidget(cabinetViewModel);
    ui->stackedWidget->addWidget(carsViewModel);
    ui->stackedWidget->setCurrentWidget(cabinetViewModel);

    this->loginResponse = loginResponse;
    getCarsharingUserRequest = new GetCarsharingUserRequest(loginResponse);

    ConnectSignals();

    getCarsharingUserRequest->SendApiRequest();
    OnGettingProfileData();
}

void CarRentalClientMainWindow::BlockAllButtons(bool flag){
    ui->aboutusButton->setEnabled(!flag);
    ui->cabinetButton->setEnabled(!flag);
    ui->carsButton->setEnabled(!flag);
    ui->contactsButton->setEnabled(!flag);
}

void CarRentalClientMainWindow::ConnectSignals(){

    QObject::connect(ui->cabinetButton, &QPushButton::clicked, this, &CarRentalClientMainWindow::OnCabinetButtonClicked);
    QObject::connect(ui->carsButton, &QPushButton::clicked, this, &CarRentalClientMainWindow::OnCarsButtonClicked);

    QObject::connect(getCarsharingUserRequest,
                     &GetCarsharingUserRequest::OnSuccessSingal,
                     this,
                     &CarRentalClientMainWindow::WhenGettingCarsharingUserWasSuccess);

    QObject::connect(getCarsharingUserRequest,
                     &GetCarsharingUserRequest::OnFailureSignal,
                     this,
                     &CarRentalClientMainWindow::WhenGettingCarsharingUserWasFailure);
}

void CarRentalClientMainWindow::OnGettingProfileData(){
    BlockAllButtons(true);

    loadingLabel = new LoadingLabel();

    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);

    loadingLabel = new LoadingLabel(this);
    loadingLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(loadingLabel);

    QLabel *description = new QLabel("Выполняется запрос на получение данных профиля, пожалуйста подождите", this);
    description->setAlignment(Qt::AlignCenter);

    layout->addWidget(description);

    page->setLayout(layout);

    ui->stackedWidget->addWidget(page);
    ui->stackedWidget->setCurrentWidget(page);

    loadingLabel->show();
}

void CarRentalClientMainWindow::OnFinishedGettingProfileData(){
    delete loadingLabel;
    BlockAllButtons(false);
    ui->stackedWidget->setCurrentWidget(cabinetViewModel);
    cabinetViewModel->SetPersonalDataScene();
}

void CarRentalClientMainWindow::WhenGettingCarsharingUserWasSuccess(const CarsharingUserDto& carsharingUser){
    OnFinishedGettingProfileData();

    isCarsharingUserExists = true;

    cabinetViewModel->FillProfileData(carsharingUser);
    cabinetViewModel->LoadOpenedCarOrders();
}

void CarRentalClientMainWindow::WhenGettingCarsharingUserWasFailure(const QList<QString>& errors){
    OnFinishedGettingProfileData();

    QString message = "";
    for (const QString &str : errors) {
        message += str + "\n";
    }

    QMessageBox::information(this, "Ошибка получения данных профиля", message);
}

void CarRentalClientMainWindow::OnCabinetButtonClicked(){
    ui->stackedWidget->setCurrentWidget(cabinetViewModel);
    cabinetViewModel->SetPersonalDataScene();
}

void CarRentalClientMainWindow::OnCarsButtonClicked(){
    ui->stackedWidget->setCurrentWidget(carsViewModel);
}

CarRentalClientMainWindow::~CarRentalClientMainWindow()
{
    delete ui;
}
