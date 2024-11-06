#include "personaldataviewmodel.h"
#include "ui_personaldataviewmodel.h"

#include "clientcache.h"
#include "mainwindow.h"
#include "ViewModels/Validators/personaldatavalidator.h"
#include "ViewModels/MainApplicationViewModels/NestedViewModels/cabinetviewmodel.h"

#include <QMessageBox>

PersonalDataViewModel::PersonalDataViewModel(const LoginResponse& loginResponse, QWidget *parent) :
    QWidget(parent),
    parent(parent),
    loginResponse(loginResponse),
    ui(new Ui::PersonalDataViewModel)
{
    ui->setupUi(this);
    ui->emailEdit->setEnabled(false);

    lastProfileData.Email = ClientCache::instance().GetData("userEmail");
    lastProfileData.Age = 0;

    ConnectWithSignals();
}

void PersonalDataViewModel::CloseMainWindow(){

    auto cabinetViewModel = dynamic_cast<CabinetViewModel*>(parent);

    if(cabinetViewModel != nullptr){
        cabinetViewModel->CloseMainWindow();
    }
    else{
        throw std::runtime_error("В Parent передан неверный аргумент в качестве родителя либо не передан совсем");
    }
}

void PersonalDataViewModel::OnSaveChangesRequestStarted(){

    loadingLabel = new LoadingLabel(QSize(22,22), this);
    ui->loadingMessage->setText("выполняется синхронизация данных с сервером");
    ui->loadingLayout->insertWidget(1, loadingLabel);
    ui->loadingMessage->show();
    loadingLabel->show();
}
void PersonalDataViewModel::OnSaveChangesRequestFinished(){
    delete loadingLabel;
    ui->loadingMessage->setText("");
}

void PersonalDataViewModel::WhenSwappedToView(){
    this->FillProfileData(lastProfileData);
}

bool PersonalDataViewModel::IsAllFormsValidated(){
    if(isValidAge && isValidName && isValidSurname && isValidPatronymic && isValidPhone){

        auto validCarhsaringUserData = CarsharingUserDto();

        validCarhsaringUserData.Id = loginResponse.UserId;
        validCarhsaringUserData.Name = ui->nameEdit->text();
        validCarhsaringUserData.Surname = ui->surnameEdit->text();
        validCarhsaringUserData.Email = ui->emailEdit->text();
        validCarhsaringUserData.Patronymic = ui->patronymicEdit->text();
        validCarhsaringUserData.Age = ui->ageEdit->text().toInt();
        validCarhsaringUserData.Phone = ui->phoneEdit->text();

        lastProfileData = validCarhsaringUserData;

        isAllDataValid = true;
        return true;
    }

    isAllDataValid = false;
    return false;
}

void PersonalDataViewModel::ConnectWithSignals(){

    QObject::connect(ui->saveChangesButton, &QPushButton::clicked, this, &PersonalDataViewModel::OnSaveChangesButtonClicked);

    QObject::connect(ui->ageEdit, &QLineEdit::textChanged, this, &PersonalDataViewModel::ValidateAge);
    QObject::connect(ui->phoneEdit, &QLineEdit::textChanged, this, &PersonalDataViewModel::ValidatePhone);
    QObject::connect(ui->nameEdit, &QLineEdit::textChanged, this, &PersonalDataViewModel::ValidateName);
    QObject::connect(ui->surnameEdit, &QLineEdit::textChanged, this, &PersonalDataViewModel::ValidateSurname);
    QObject::connect(ui->patronymicEdit, &QLineEdit::textChanged, this, &PersonalDataViewModel::ValidatePatronymic);
}

void PersonalDataViewModel::OnSaveChangesButtonClicked(){
    if(IsAllFormsValidated()){

        createOrUpdateCarsharingUserRequest = new CreateOrUpdateCarsharingUserRequest(loginResponse, lastProfileData);

        QObject::connect(createOrUpdateCarsharingUserRequest,&CreateOrUpdateCarsharingUserRequest::OnSuccessSingal,
                         this,&PersonalDataViewModel::OnCreateOrUpdateCarsharingUserSuccess);

        QObject::connect(createOrUpdateCarsharingUserRequest,&CreateOrUpdateCarsharingUserRequest::OnFailureSignal,
                         this,&PersonalDataViewModel::OnCreateOrUpdateCarsharingUserFailure);

        createOrUpdateCarsharingUserRequest->SendApiRequest();
        OnSaveChangesRequestStarted();
        // показать что выпонляется синхронизация данных с сервером
    }
}

void PersonalDataViewModel::OnCreateOrUpdateCarsharingUserSuccess(const QString& message){
    OnSaveChangesRequestFinished();
    ClientCache::instance().SaveCarhsaringUserProfile(lastProfileData);
}

void PersonalDataViewModel::OnCreateOrUpdateCarsharingUserFailure(const QList<QString>& errors){

    OnSaveChangesRequestFinished();

    QString message = "";
    for (const QString &str : errors) {
        message += str + "\n";
    }

    QMessageBox::information(this, "Ошибка обновления профиля", message);
}

void PersonalDataViewModel::ValidateAge(){

    auto age = ui->ageEdit->text();

    bool isValid = PersonalDataValidator::IsValidAge(age);

    if(isValid){
        isValidAge = true;
        ui->ageEdit->setStyleSheet(lineEditValidStyleSheet);
    }
    else{
        isValidAge = false;
        ui->ageEdit->setStyleSheet(lineEditNotValidStyleSheet);
    }
}

void PersonalDataViewModel::ValidatePhone(){

    auto phone = ui->phoneEdit->text();

    bool isValid = PersonalDataValidator::IsValidPhone(phone);

    if(isValid){
        isValidPhone = true;
        ui->phoneEdit->setStyleSheet(lineEditValidStyleSheet);
    }
    else{
        isValidPhone = false;
        ui->phoneEdit->setStyleSheet(lineEditNotValidStyleSheet);
    }
}

void PersonalDataViewModel::ValidateName(){

    auto name = ui->nameEdit->text();

    bool isValid = PersonalDataValidator::IsValidInitials(name);

    if(isValid){
        isValidName = true;
        ui->nameEdit->setStyleSheet(lineEditValidStyleSheet);
    }
    else{
        isValidName = false;
        ui->nameEdit->setStyleSheet(lineEditNotValidStyleSheet);
    }
}

void PersonalDataViewModel::ValidateSurname(){

    auto surname = ui->surnameEdit->text();

    bool isValid = PersonalDataValidator::IsValidInitials(surname);

    if(isValid){
        isValidSurname = true;
        ui->surnameEdit->setStyleSheet(lineEditValidStyleSheet);
    }
    else{
        isValidSurname = false;
        ui->surnameEdit->setStyleSheet(lineEditNotValidStyleSheet);
    }
}

void PersonalDataViewModel::ValidatePatronymic(){

    auto patronymic = ui->patronymicEdit->text();

    bool isValid = PersonalDataValidator::IsValidInitials(patronymic);

    if(isValid){
        isValidPatronymic = true;
        ui->patronymicEdit->setStyleSheet(lineEditValidStyleSheet);
    }
    else{
        isValidPatronymic = false;
        ui->patronymicEdit->setStyleSheet(lineEditNotValidStyleSheet);
    }
}

void PersonalDataViewModel::FillProfileData(const CarsharingUserDto& carsharingUser){

    ui->ageEdit->setText(QString::fromStdString(std::to_string(carsharingUser.Age)));
    ui->emailEdit->setText(carsharingUser.Email);
    ui->phoneEdit->setText(carsharingUser.Phone);
    ui->nameEdit->setText(carsharingUser.Name);
    ui->surnameEdit->setText(carsharingUser.Surname);
    ui->patronymicEdit->setText(carsharingUser.Patronymic);

    ValidateAllForms();

    this->lastProfileData = carsharingUser;
    ClientCache::instance().SaveCarhsaringUserProfile(carsharingUser);
}

void PersonalDataViewModel::ValidateAllForms(){
    ValidateAge();
    ValidateName();
    ValidateSurname();
    ValidatePatronymic();
    ValidatePhone();
}

CarsharingUserDto PersonalDataViewModel::GetProfileData(){
    return this->lastProfileData;
}

PersonalDataViewModel::~PersonalDataViewModel()
{
    delete ui;
}

void PersonalDataViewModel::on_pushButton_clicked()
{
    CloseMainWindow();

    auto loginForm = new MainWindow();
    loginForm->show();
}

