#ifndef CABINETVIEWMODEL_H
#define CABINETVIEWMODEL_H

#include <QWidget>

#include "Api/Dto/loginresponse.h"
#include "Api/Dto/carsharinguserdto.h"
#include "Api/Dto/openedcarreservationresonse.h"

#include "ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/activeordersviewmodel.h"
#include "ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/closedordersviewmodel.h"
#include "ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/personaldataviewmodel.h"

namespace Ui {
class CabinetViewModel;
}

class CabinetViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit CabinetViewModel(const LoginResponse& loginResponse, QWidget *parent = nullptr);
    ~CabinetViewModel();

    void SetPersonalDataScene();
    void FillProfileData(const CarsharingUserDto& carsharingUser);
    void LoadOpenedCarOrders();
    void LoadClosedCarOrders();

private:
    Ui::CabinetViewModel *ui;

    PersonalDataViewModel *personalViewModel;
    ActiveOrdersViewModel *activeOrdersViewModel;
    ClosedOrdersViewModel *closedOrdersViewModel;

    LoginResponse loginResponse;
private slots:
    void OnPersonalDataButtonClicked();
    void OnActiveOrdersButtonClicked();
    void OnClosedOrdersButtonClicked();

    void OnGettingOpenedCarOrdersSuccess(const QList<OpenedCarReservationResonse>& openedCarReservations);
    void OnGettingOpenedCarOrdersFailure(const QString& errorMessage);
};

#endif // CABINETVIEWMODEL_H
