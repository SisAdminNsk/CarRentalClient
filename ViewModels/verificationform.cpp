#include "verificationform.h"
#include "ui_verificationform.h"

#include <QMessageBox>
#include <QTimer>
#include <QIntValidator>

VerificationForm::VerificationForm(const RegistrateDto& registrateDto, QNetworkCookieJar *parentCookies, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VerificationForm),
    registrateDto(registrateDto),
    cookieJar(parentCookies)
{
    ui->setupUi(this);

    Setup();
}

void VerificationForm::SetupSendAgainVerificationCodeRequest(){

    sendVerificationCodeAgainRequest = new GetVerificationCodeRequest(registrateDto.Email);
    sendVerificationCodeAgainRequest->SetCookies(cookieJar);

    QObject::connect(sendVerificationCodeAgainRequest, &GetVerificationCodeRequest::OnFailureSignal, this,
                     &VerificationForm::OnSendAgainVerificationCodeError);
    QObject::connect(sendVerificationCodeAgainRequest, &GetVerificationCodeRequest::OnSuccessSingal, this,
                     &VerificationForm::OnSendAgainVerificationCodeSuccess);
}

void VerificationForm::Setup(){

    setWindowIcon(QIcon(":/images/Media/carsharingLogo.png"));

    setFixedSize(450,250);
    setMinimumSize(450,250);
    setMaximumSize(450,250);

    SetupInputVerificationCode();
    SetupTimer();

    QObject::connect(ui->closeButton, &QPushButton::clicked, this, &VerificationForm::OnCloseButtonClicked);
    QObject::connect(ui->submitButton, &QPushButton::clicked, this, &VerificationForm::OnSubmitButtonClicked);
    QObject::connect(ui->sendAgainButton, &QPushButton::clicked, this, &VerificationForm::OnSendAgainButtonClicked);
}

void VerificationForm::SetupTimer(){
    sendAgainTimer = new QTimer(this);
    QObject::connect(sendAgainTimer, &QTimer::timeout, this, &VerificationForm::OnTimerTick);
    SetSendAgainButtonTimeoutInSec();
    timerTickInMs = 1000;
}

void VerificationForm::SetupInputVerificationCode(){

    auto verificationCodeIcon = QPixmap(":/images/Media/verificationIcon.png");
    ui->inputCodeIcon->setPixmap(verificationCodeIcon.scaled(24,24, Qt::KeepAspectRatio));

    ui->verificationCodeInput->setPlaceholderText("X-X-X-X-X-X");
    ui->verificationCodeInput->setMaxLength(6);

    ui->verificationCodeInput->setValidator(new QIntValidator(this));
}

VerificationForm::~VerificationForm()
{
    delete ui;
}

void VerificationForm::SetSendAgainButtonTimeoutInSec(){
    this->remainingTimeInSec = 300;
}

void VerificationForm::OnTimerTick(){

    if (remainingTimeInSec > 0) {
        ui->sendAgainButton->setText("Отправить код еще раз через: " +
                                     QString::fromStdString(std::to_string(remainingTimeInSec)) + " секунд");
        remainingTimeInSec--;
    } else {
        // упаковать в функцию onTimeout
        sendAgainTimer->stop();
        ui->sendAgainButton->setText("Отправить код еще раз");
        ui->sendAgainButton->setEnabled(true);
    }
}

void VerificationForm::OnSubmitButtonClicked(){

    auto verificationCode = ui->verificationCodeInput->text();

    SetupVerificationRequest(registrateDto, verificationCode);

    verificationRequest->SendApiRequest();
    OnVerificationRequestStarted();
}

void VerificationForm::SetupVerificationRequest(const RegistrateDto& registrateDTO, QString verificationCode){

    verificationRequest = new VerificationRequest(registrateDTO, verificationCode, this);
    verificationRequest->SetCookies(cookieJar);

    QObject::connect(verificationRequest, &VerificationRequest::OnFailureSignal, this, &VerificationForm::OnVerificationError);
    QObject::connect(verificationRequest, &VerificationRequest::OnSuccessSignal, this, &VerificationForm::OnVerificationSuccess);
}

void VerificationForm::OnSendAgainButtonClicked(){

    SetSendAgainButtonTimeoutInSec();
    ui->sendAgainButton->setDisabled(true);
    sendAgainTimer->start(timerTickInMs);

    SetupSendAgainVerificationCodeRequest();
    sendVerificationCodeAgainRequest->SendApiRequest();
}

void VerificationForm::OnSendAgainVerificationCodeError(const QString& message){
    QMessageBox::information(nullptr, "Верификация", message);
}

void VerificationForm::OnSendAgainVerificationCodeSuccess(const QString& message){
    QMessageBox::information(nullptr, "Верификация", message);
}

void VerificationForm::OnCloseButtonClicked(){
    close();
}

void VerificationForm::OnVerificationError(const QString& message){
    OnVerificationRequestFinished();

    QMessageBox::information(nullptr, "Верификация", message);
}

void VerificationForm::OnVerificationSuccess(const QString& message){
    OnVerificationRequestFinished();
    close();
}

void VerificationForm::OnVerificationRequestFinished(){
    delete loadingLabel;
    ui->statusbar->clearMessage();
}

void VerificationForm::OnVerificationRequestStarted(){

    ui->sendAgainButton->setDisabled(true);
    sendAgainTimer->start(remainingTimeInSec);

    ui->statusbar->showMessage("Выполняется верификация кода, пожалуйста подождите...");

    loadingLabel = new LoadingLabel(QSize(22, 22));

    ui->statusbar->addPermanentWidget(loadingLabel);

    loadingLabel->show();
}
