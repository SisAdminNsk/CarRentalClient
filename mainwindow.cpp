#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "Api/Dto/createcarorderdto.h"
#include "Api/Endpoints/CarOrders/Requests/createcarorderrequest.h"
#include "Api/Endpoints/Users/Requests/loginrequest.h"

#include "clientcache.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Setup();

    CreateCarOrderDto createCarOrderDto;
    createCarOrderDto.ApproximatePrice = 100;
    createCarOrderDto.Comment = "f;ajkgjak";
    createCarOrderDto.CarId = "d21a8278-af57-4507-b9d3-75b13a6bdc6c";
    createCarOrderDto.CarsharingUserId = "f9c4956a-d8ba-4e57-85b0-3c9963f2c248";
    createCarOrderDto.StartOfLease = "2024-10-07T10:11:01.204Z";
    createCarOrderDto.EndOfLease = "2024-10-07T10:12:01.204Z";

    auto createCarOrderRequest = new CreateCarOrderRequest("", createCarOrderDto);
    createCarOrderRequest->SendApiRequest();
}

void MainWindow::Setup(){

    setFixedSize(500,320);
    setMinimumSize(500,320);
    setMaximumSize(500,320);

    QObject::connect(ui->loginPushButton, &QPushButton::clicked, this, &MainWindow::OnLoginPushButtonClicked);
    QObject::connect(ui->newUserPushButton, &QPushButton::clicked, this, &MainWindow::OnRegistratePushButtonClicked);

    auto authenticationIconPixmap = QPixmap(":/media/Media/loginIcon.png");
    auto usernameIconPixmap = QPixmap(":/media/Media/usernameIcon.png");
    auto passwordIconPixmap = QPixmap(":/media/Media/passwordIcon.png");

    setWindowIcon(QIcon(":/media/Media/carsharingLogo.png"));

    ui->loginIcon->setPixmap(authenticationIconPixmap.scaled(37,37, Qt::KeepAspectRatio));
    ui->passwordIcon->setPixmap(passwordIconPixmap.scaled(24,24,Qt::KeepAspectRatio));
    ui->usernameIcon->setPixmap(usernameIconPixmap.scaled(24,24,Qt::KeepAspectRatio));

    ui->usernameLineEdit->setPlaceholderText("Введите вашу почту");
    ui->passwordLineEdit->setPlaceholderText("Введите ваш пароль");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

void MainWindow::OnLoginPushButtonClicked(){

    auto userLogin = ui->usernameLineEdit->text();
    auto userPassword = ui->passwordLineEdit->text();

    auto loginUserRequest = new LoginRequest(LoginDto(userLogin, userPassword), this);

    QObject::connect(loginUserRequest, &LoginRequest::OnFailureSignal, this, &MainWindow::OnLoginError);
    QObject::connect(loginUserRequest, &LoginRequest::OnSuccessSignal, this, &MainWindow::OnLoginSuccess);

    loginUserRequest->SendApiRequest();

    OnLoginRequestStarted();
}

void MainWindow::OnLoginRequestStarted(){

    ui->loginPushButton->blockSignals(true);
    ui->newUserPushButton->blockSignals(true);

    ui->statusBar->showMessage("Выполняется аутентификация, пожалуйста подождите...");

    loadingLabel = new LoadingLabel(QSize(22, 22));

    this->ui->statusBar->addPermanentWidget(loadingLabel);

    loadingLabel->show();
}

void MainWindow::OnLoginRequestFinished(){

    this->ui->statusBar->clearMessage();
    this->ui->loginPushButton->blockSignals(false);
    this->ui->newUserPushButton->blockSignals(false);

    delete loadingLabel;
}

void MainWindow::OnLoginSuccess(const LoginResponse& loginResponse){

    this->OnLoginRequestFinished();

    auto email = ui->usernameLineEdit->text();

    ClientCache::instance().SetData("userEmail", ui->usernameLineEdit->text());
    ClientCache::instance().SaveLoginCredentials(loginResponse);

    //auto carRentalClientMainWindow = new CarRentalClientMainWindow(loginResponse);
    //carRentalClientMainWindow->show();

    this->close();
}

void MainWindow::OnGetCarsSuccess(const QList<CarDto>& cars){
    for(size_t i=0;i<cars.size();i++){
        auto car = cars[i];
    }
}
void MainWindow::OnGetCarsFailure(const QString& message){
    QMessageBox::information(nullptr, "Получение авто", message);
}

void MainWindow::OnLoginError(const QString &message){

    this->OnLoginRequestFinished();

    QMessageBox::information(nullptr, "Аутентификация", message);
}

void MainWindow::OnRegistratePushButtonClicked(){

    registrationForm = new RegistrationForm();
    registrationForm->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete registrationForm;
}
