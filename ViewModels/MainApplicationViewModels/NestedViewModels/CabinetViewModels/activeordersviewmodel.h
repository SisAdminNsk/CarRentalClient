#ifndef ACTIVEORDERSVIEWMODEL_H
#define ACTIVEORDERSVIEWMODEL_H

#include <QWidget>

#include "Api/Dto/loginresponse.h"
#include "Api/Dto/openedcarreservationresonse.h"
#include "ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/OpenCarOrderCard/opencarordercardviewmodel.h"

namespace Ui {
class ActiveOrdersViewModel;
}

class ActiveOrdersViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit ActiveOrdersViewModel(const LoginResponse& loginResponse, QWidget *parent = nullptr);
    ~ActiveOrdersViewModel();

    void InitializeCatalog(const QList<OpenedCarReservationResonse>& openedCarReservations);
    void Update();
private:
    void Setup();
    void OnUpdateButtonClicked();

    Ui::ActiveOrdersViewModel *ui;
    LoginResponse loginResponse;
private slots:
    void OnGettingOpenCarOrdersSuccess(const QList<OpenedCarReservationResonse>& openedReservations);
    void OnGettingOpenCarOrdersFailure(const QString& errorMessage);
};

#endif // ACTIVEORDERSVIEWMODEL_H
