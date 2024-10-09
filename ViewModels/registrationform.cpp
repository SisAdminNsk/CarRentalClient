#include "registrationform.h"
#include "ui_registrationform.h"

#include <QMessageBox>

#include "ViewModels/Validators/formvalidator.h"
#include "ViewModels/verificationform.h"

RegistrationForm::RegistrationForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);

    Setup();
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::OnRegistratePushButtonClicked(){

    if(IsAllFormsValidated()){

        auto username = ui->usernameLineEdit->text();
        auto email = ui->emailLineEdit->text();
        auto password = ui->passwordLineEdit->text();

        auto registrateDTO = RegistrateDto(username, email, password);

        registrateRequest = new RegistrateRequest(registrateDTO);

        QObject::connect(registrateRequest, &RegistrateRequest::OnFailureSignal, this, &RegistrationForm::OnRegistrationError);
        QObject::connect(registrateRequest, &RegistrateRequest::OnSuccessSingal, this, &RegistrationForm::OnRegistrationSuccess);

        registrateRequest->SendApiRequest();
        OnRegistrateRequestStarted();
    }
}

void RegistrationForm::OnRegistrateRequestStarted(){

    ui->registratePushButton->blockSignals(true);

    ui->statusbar->showMessage("Выполняется регистрация, пожалуйста подождите...");

    loadingLabel = new LoadingLabel(QSize(22, 22));

    ui->statusbar->addPermanentWidget(loadingLabel);

    loadingLabel->show();
}

void RegistrationForm::OnRegistrateRequestFinished(){
    ui->registratePushButton->blockSignals(false);
    ui->statusbar->clearMessage();

    delete loadingLabel;
}

void RegistrationForm::Setup(){

    setWindowIcon(QIcon(":/images/Media/carsharingLogo.png"));

    setFixedSize(800,500);
    setMinimumSize(800,500);
    setMaximumSize(800,500);

    auto emailIconPixmap = QPixmap(":/images/Media/email.png");
    auto usernameIconPixmap = QPixmap(":/images/Media/usernameIcon.png");
    auto passwordIconPixmap = QPixmap(":/images/Media/passwordIcon.png");

    ui->emailIcon->setPixmap(emailIconPixmap.scaled(24,24, Qt::KeepAspectRatio));
    ui->passwordIcon->setPixmap(passwordIconPixmap.scaled(24,24, Qt::KeepAspectRatio));
    ui->confirmPasswordIcon->setPixmap(passwordIconPixmap.scaled(24,24, Qt::KeepAspectRatio));
    ui->usernameIcon->setPixmap(usernameIconPixmap.scaled(24,24, Qt::KeepAspectRatio));

    ConnectiWithSignals();
    SetupCheckboxes();
    SetupInputFields();
}

void RegistrationForm::ConnectiWithSignals(){

    QObject::connect(ui->registratePushButton, &QPushButton::clicked, this,
                     &RegistrationForm::OnRegistratePushButtonClicked);

    QObject::connect(ui->emailLineEdit, &QLineEdit::textChanged, this, &RegistrationForm::ValidateEmail);
    QObject::connect(ui->usernameLineEdit, &QLineEdit::textChanged, this, &RegistrationForm::ValidateUsername);
    QObject::connect(ui->passwordLineEdit, &QLineEdit::textChanged, this, &RegistrationForm::ValidatePassword);
    QObject::connect(ui->confirmPasswordLineEdit, &QLineEdit::textChanged, this, &RegistrationForm::ValidateConfirmPassword);
}

bool RegistrationForm::IsAllFormsValidated(){

    if(ui->usernameCheckbox->isChecked() && ui->emailCheckbox->isChecked() &&
        ui->passwordCheckbox->isChecked() && ui->confirmPasswordCheckbox->isChecked()){

        return true;
    }

    return false;
}

void RegistrationForm::ShowDefaultEmailClue(){

    ui->emailClue->setText("Например: someperson@value.com");
    ui->emailClue->setStyleSheet("QLabel {font-size: 8pt;}");
}

void RegistrationForm::ShowDefaultUsernameClue(){

    ui->usernameClue->setText("[ a-Z, 0-9, _ ] длина имени от 6 до 32 символов ");
    ui->usernameClue->setStyleSheet("QLabel {font-size: 8pt;}");
}

void RegistrationForm::OnNotValidAction(QLineEdit* lineEdit, QLabel* clue, QCheckBox* checkbox){

    lineEdit->setStyleSheet(checkboxNotValidStyleSheet);
}

void RegistrationForm::OnValidAction(QLineEdit* lineEdit, QLabel* clue, QCheckBox* checkbox){

    lineEdit->setStyleSheet(checkboxValidStyleSheet);
    clue->clear();
}

void RegistrationForm::SetupCheckboxes(){

    ui->emailCheckbox->setEnabled(false);

    ui->usernameCheckbox->setEnabled(false);

    ui->passwordCheckbox->setEnabled(false);

    ui->confirmPasswordCheckbox->setEnabled(false);
}

void RegistrationForm::SetupInputFields(){

    ui->emailLineEdit->setPlaceholderText("Введите свою электронную почту");
    ui->usernameLineEdit->setPlaceholderText("Введите имя нового пользователя");

    ui->passwordLineEdit->setPlaceholderText("Придумайте новый пароль");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    ui->confirmPasswordLineEdit->setPlaceholderText("Введите пароль еще раз");
    ui->confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

    ui->confirmPasswordLineEdit->setEnabled(false);
}

void RegistrationForm::ValidatePassword(){

    auto password = ui->passwordLineEdit->text();
    bool isValid = FormValidator::IsValidPassword(password);
    ui->passwordCheckbox->setChecked(isValid);

    if(isValid){
        OnValidAction(ui->passwordLineEdit, ui->passwordClue, ui->passwordCheckbox);
        ui->confirmPasswordLineEdit->setEnabled(true);
    }
    else{
        OnNotValidAction(ui->passwordLineEdit, ui->passwordClue, ui->passwordCheckbox);
        ui->confirmPasswordLineEdit->setEnabled(false);
    }
}

void RegistrationForm::ValidateConfirmPassword(){

    auto password = ui->passwordLineEdit->text();
    auto confirmPassword = ui->confirmPasswordLineEdit->text();

    if(confirmPassword == password){
        ui->confirmPasswordLineEdit->setStyleSheet(checkboxValidStyleSheet);
        ui->confirmPasswordCheckbox->setChecked(true);
        ui->confirmPasswordCheckbox->setHidden(false);
    }
    else{
        ui->confirmPasswordLineEdit->setStyleSheet(checkboxNotValidStyleSheet);
        ui->confirmPasswordCheckbox->setChecked(false);
        ui->confirmPasswordCheckbox->setHidden(true);
    }
}

void RegistrationForm::ValidateEmail(){

    auto email = ui->emailLineEdit->text();

    if(this->registeredEmails.contains(email)){

        ui->emailClue->setVisible(true);
        ui->emailClue->setText("Введенная почта уже зарегистрирована");
        ui->emailClue->setStyleSheet("color: red;");
        ui->emailCheckbox->setChecked(false);
        ui->emailLineEdit->setStyleSheet(checkboxNotValidStyleSheet);

        return;
    }

    bool isValid = FormValidator::IsValidEmail(email);

    ui->emailCheckbox->setChecked(isValid);

    if(isValid){
        OnValidAction(ui->emailLineEdit, ui->emailClue, ui->emailCheckbox);
    }
    else{
        ShowDefaultEmailClue();
        OnNotValidAction(ui->emailLineEdit,ui->emailClue, ui->emailCheckbox);
    }
}

void RegistrationForm::ValidateUsername(){

    auto username = ui->usernameLineEdit->text();

    if(registeredUsernames.contains(username)){

        ui->usernameClue->setVisible(true);
        ui->usernameClue->setText("Данное имя занято");
        ui->usernameClue->setStyleSheet("color: red;");
        ui->usernameCheckbox->setChecked(false);
        ui->usernameLineEdit->setStyleSheet(checkboxNotValidStyleSheet);

        return;
    }

    bool isValid = FormValidator::IsValidUsername(username);

    ui->usernameCheckbox->setChecked(isValid);

    if(isValid){
        OnValidAction(ui->usernameLineEdit, ui->usernameClue, ui->usernameCheckbox);
    }
    else{
        ShowDefaultUsernameClue();
        OnNotValidAction(ui->usernameLineEdit, ui->usernameClue, ui->usernameCheckbox);
    }
}

void RegistrationForm::OnRegistrationSuccess(const QString& message){

    OnRegistrateRequestFinished();

    auto verificationForm = new VerificationForm(
        RegistrateDto(ui->usernameLineEdit->text(), ui->emailLineEdit->text(), ui->passwordLineEdit->text()),
        registrateRequest->GetCookies(),
        this);

    close();
    verificationForm->show();
}

void RegistrationForm::OnRegistrationError(const QMap<QString, QString>& errors){

    OnRegistrateRequestFinished();

    if(errors.contains("Server")){
        QMessageBox::information(nullptr, "Регистрация", errors["Server"]);
        return;
    }

    if(errors.contains("Email")){

        ui->emailClue->setText("Введенная почта уже зарегистрирована");
        ui->emailClue->setStyleSheet("color: red;");
        ui->emailClue->setHidden(false);
        ui->emailCheckbox->setChecked(false);
        ui->emailLineEdit->setStyleSheet(checkboxNotValidStyleSheet);

        registeredEmails.insert(ui->emailLineEdit->text());
    }

    if(errors.contains("Username")){

        ui->usernameClue->setText("Введенное имя занято");
        ui->usernameClue->setStyleSheet("color: red;");
        ui->usernameClue->setHidden(false);
        ui->usernameCheckbox->setChecked(false);
        ui->usernameLineEdit->setStyleSheet(checkboxNotValidStyleSheet);

        registeredUsernames.insert(ui->usernameLineEdit->text());
    }
}
