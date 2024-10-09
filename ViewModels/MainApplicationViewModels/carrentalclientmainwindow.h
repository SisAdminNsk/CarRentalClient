#ifndef CARRENTALCLIENTMAINWINDOW_H
#define CARRENTALCLIENTMAINWINDOW_H

#include <QMainWindow>

#include "Api/Dto/loginresponse.h"
#include "Api/Endpoints/CarsharingUsers/Requests/getcarsharinguserrequest.h"

#include "ViewModels/loadinglabel.h"
#include "ViewModels/MainApplicationViewModels/NestedViewModels/cabinetviewmodel.h"
#include "ViewModels/MainApplicationViewModels/NestedViewModels/carsviewmodel.h"

namespace Ui {
class CarRentalClientMainWindow;
}

class CarRentalClientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CarRentalClientMainWindow(const LoginResponse& loginResponse, QWidget *parent = nullptr);
    ~CarRentalClientMainWindow();

private:
    bool isCarsharingUserExists = false;

    LoadingLabel *loadingLabel;
    LoginResponse loginResponse;

    GetCarsharingUserRequest *getCarsharingUserRequest;

    Ui::CarRentalClientMainWindow *ui;
    CabinetViewModel *cabinetViewModel;
    CarsViewModel *carsViewModel;

    void BlockAllButtons(bool flag);
    void ConnectSignals();

private slots:
    void OnGettingProfileData();
    void OnFinishedGettingProfileData();

    void OnCabinetButtonClicked();
    void OnCarsButtonClicked();

    void WhenGettingCarsharingUserWasSuccess(const CarsharingUserDto& carsharingUser);
    void WhenGettingCarsharingUserWasFailure(const QList<QString>& errors);
};

#endif // CARRENTALCLIENTMAINWINDOW_H
