#ifndef PERSONALDATAVIEWMODEL_H
#define PERSONALDATAVIEWMODEL_H

#include <QWidget>

#include "Api/Dto/loginresponse.h"
#include "Api/Dto/carsharinguserdto.h"
#include "Api/Endpoints/CarsharingUsers/Requests/createorupdatecarsharinguserrequest.h"
#include "ViewModels/loadinglabel.h"

namespace Ui {
class PersonalDataViewModel;
}

class PersonalDataViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalDataViewModel(const LoginResponse& loginResponse,QWidget *parent = nullptr);
    ~PersonalDataViewModel();

    void WhenSwappedToView();
    void FillProfileData(const CarsharingUserDto& carsharingUser);
    CarsharingUserDto GetProfileData();
private:
    LoadingLabel *loadingLabel;
    CreateOrUpdateCarsharingUserRequest *createOrUpdateCarsharingUserRequest = nullptr;

    QString lineEditValidStyleSheet = "QLineEdit { border: 2px solid green; font-size: 16pt; }";
    QString lineEditNotValidStyleSheet = "QLineEdit { border: 2px solid red; font-size: 16pt; }";

    bool isValidAge = false;
    bool isValidName = false;
    bool isValidSurname = false;
    bool isValidPatronymic = false;
    bool isValidPhone = false;

    bool IsAllFormsValidated();

    void ConnectWithSignals();
    CarsharingUserDto lastProfileData;

    LoginResponse loginResponse;
    Ui::PersonalDataViewModel *ui;

    bool isAllDataValid = false;

    void OnSaveChangesRequestStarted();
    void OnSaveChangesRequestFinished();
private slots:

    void OnSaveChangesButtonClicked();

    void ValidateAge();
    void ValidateName();
    void ValidateSurname();
    void ValidatePatronymic();
    void ValidatePhone();

    void ValidateAllForms();

    void OnCreateOrUpdateCarsharingUserSuccess(const QString& message);
    void OnCreateOrUpdateCarsharingUserFailure(const QList<QString>& Errors);
};

#endif // PERSONALDATAVIEWMODEL_H
